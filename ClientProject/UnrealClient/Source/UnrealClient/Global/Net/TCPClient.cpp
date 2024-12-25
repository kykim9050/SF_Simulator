// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Net/TCPClient.h"
#include "Global/Net/ClientPacketManager.h"
#include "Playlevel/SimulatorManager.h"
#include "Playlevel/ClientPlayGameMode.h"
#include "Playlevel/Actor/Mover.h"


ATCPClient::ATCPClient()
	:TCPClientSocket(nullptr)
{
	Interpret = CreateDefaultSubobject<UClientInterpreter>(TEXT("ClientInterpreter"));
}

ATCPClient::~ATCPClient()
{
	// 소켓이 활성화 되어 있다면
	if (nullptr != TCPClientSocket)
	{
		// 소켓 반환
		TCPClientSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(TCPClientSocket);
	}
}

bool ATCPClient::ConnectToServer(const FString& _IPAddress, int32 _Port)
{
	// 통신을 위한 소켓서브 시스템
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (nullptr == SocketSubsystem)
	{
		UE_LOG(LogType, Error, TEXT("if (nullptr == SocketSubsystem)"));
		return false;
	}

	// FIPv4Address 구조체에 문자열로 주어진 IP주소를 실제 정보로써 매칭
	FIPv4Address IP = FIPv4Address();
	if (false == FIPv4Address::Parse(_IPAddress, IP))
	{
		UE_LOG(LogType, Error, TEXT("if (false == FIPv4Address::Parse(_IPAddress, IP))"));
		return false;
	}

	// TCP 소켓으로 생성
	TCPClientSocket = SocketSubsystem->CreateSocket(FName(TEXT("Stream")), TEXT("TCP Client Socket"));

	// Server에 연결하기 위해 IP와 포트 정보를 FInternetAddr에 대입
	TSharedRef<FInternetAddr> ServerAddress = SocketSubsystem->CreateInternetAddr();
	ServerAddress->SetIp(IP.Value);
	ServerAddress->SetPort(_Port);

	// 소켓을 통해 Connect 실행
	if (false == TCPClientSocket->Connect(*ServerAddress))
	{
		// 연결 실패
		UE_LOG(LogType, Error, TEXT("Failed connect to Server"));
		UGlobalFunctonLibrary::LoggingInWidget(TEXT("Failed connect to Server"), GetWorld());
		return false;
	}

	// 연결 성공
	UE_LOG(LogType, Log, TEXT("Connected to server at %s:%d"), *_IPAddress, _Port);
	UGlobalFunctonLibrary::LoggingInWidget(FString::Printf(TEXT("Connected to server at %s:%d"), *_IPAddress, _Port), GetWorld());

	// 연결 성공시 패킷 해석정보 초기화
	ClientPacketInit(Interpret);

	return true;
}


void ATCPClient::SendData(const FBufferArchive& _PacketData)
{
	UE_LOG(LogType, Log, TEXT("BeginSend"));

	// Blocking 현상 해결을 위한 AsyncTask 사용
	AsyncTask(ENamedThreads::AnyThread, [this, _PacketData]()
		{
			if (nullptr == TCPClientSocket || nullptr == this)
			{
				UGlobalFunctonLibrary::LoggingInWidget(TEXT("No valid socket, Cant Send Data"), GetWorld());
				return;
			}

			// 패킷에 담은 정보 Send
			int32 NumSend;
			bool bSuccess = TCPClientSocket->Send(_PacketData.GetData(), _PacketData.Num(), NumSend);

			AsyncTask(ENamedThreads::GameThread, [this, bSuccess]
				{
					if (nullptr == TCPClientSocket || nullptr == this)
					{
						return;
					}

					if (true == bSuccess)
					{
						UE_LOG(LogType, Log, TEXT("Send Completed"));
						RecvData();
					}
					else
					{
						UE_LOG(LogType, Log, TEXT("Send Error"));
					}
				});

		});
}

void ATCPClient::RecvData()
{
	AsyncTask(ENamedThreads::AnyThread, [this]()
		{
			if (TCPClientSocket == nullptr || this == nullptr)
			{
				return;
			}

			uint32 PendingDataSize = 0;
			const float SleepDuration = 0.01f;
			const int32 MaxRetries = 100;
			int32 RetryCount = 0;

			// 버퍼에 데이터가 있을 때까지 대기
			// 가끔 버퍼에 데이터가 없어서 false가 뜰 때, 재시도 없이 진행해버리면 데이터 수신이 밀려서 실행되는 현상 발생
			while (!TCPClientSocket->HasPendingData(PendingDataSize))
			{
				// 일정 카운트 기회를 주어서 넘어가면 문제가 있는 상황
				if (++RetryCount > MaxRetries)
				{
					UE_LOG(LogType, Fatal, TEXT("No data available after waiting."));
					return;
				}

				FPlatformProcess::Sleep(SleepDuration);
			}

			// 보류중인 데이터가 있는지 먼저 확인
			// 헤더의 사이즈만큼 먼저 읽음
			if (8 <= PendingDataSize)
			{
				AsyncTask(ENamedThreads::GameThread, [this, PendingDataSize]()
					{
						// 필요한 만큼 데이터를 읽기위한 헤더 버퍼
						TArray<uint8> HeaderBuffer;
						HeaderBuffer.SetNumUninitialized(8);
						int32 NumRead = 0;

						if (TCPClientSocket->Recv(HeaderBuffer.GetData(), 8, NumRead, ESocketReceiveFlags::Type::WaitAll))
						{
							// 헤더 정보 추출
							FMemoryReader HeaderReader(HeaderBuffer);
							FMessageHeader HeaderRecvData;
							HeaderReader << HeaderRecvData;

							int32 DataSize = HeaderRecvData.Size;

							if (static_cast<int32>(PendingDataSize) >= DataSize + 8)
							{
								TArray<uint8> Buffer;
								Buffer.SetNumUninitialized(DataSize);

								bool bSuccessRecv = false;

								// Recv로 서버에서 데이터 받기 (실제 데이터가 Buffer에 받아와진다)
								bSuccessRecv = TCPClientSocket->Recv(Buffer.GetData(), Buffer.Num(), NumRead, ESocketReceiveFlags::Type::WaitAll);

								if (TCPClientSocket == nullptr || this == nullptr)
								{
									return;
								}

								// 성공적으로 수신했다면
								if (bSuccessRecv)
								{
									// 수신받은 Buffer 데이터를 FMemoryReader 클래스로 받아서 해석
									// 언리얼에서 Serialize의 Read, Write는 모두 << 연산자로 취급
									FMemoryReader Reader(Buffer);

									TSharedPtr<FRecvBaseProtocol> NewProtocol = Interpret->ConvertProtocol(HeaderRecvData.Type, Reader);
									Interpret->ProcessPacket(NewProtocol);

									UE_LOG(LogType, Log, TEXT("Recv Completed"));
								}
								else // 성공적으로 수신 못했다면
								{
									UE_LOG(LogType, Error, TEXT("Recv Payload Failed."));
								}

							}
						}
					});
			}
		});

}

void ATCPClient::ClientPacketInit(TObjectPtr<UClientInterpreter> _Interpret)
{
	_Interpret->AddHandler<FRecvNPacket>([this](TSharedPtr<FRecvNPacket> _Packet)
		{
			// N값을 Client의 변수 보관소에 저장하기
			UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());

			if (Inst)
			{
				// 서버로부터 받은 N 값 세팅
				Inst->SetN(_Packet.Get()->N);
			}

			AClientPlayGameMode* CurGameMode = UGlobalFunctonLibrary::GetClientPlayGameMode(GetWorld());
			if (CurGameMode)
			{
				ASimulatorManager* SM = CurGameMode->GetMainSimulator().Get();
				if (SM)
				{
					// Grid 생성
					SM->GridInit(Inst->GetN());
				}
			}

			UE_LOG(LogType, Log, TEXT("NValue recv data success.  N : %d"), _Packet.Get()->N);
			UGlobalFunctonLibrary::LoggingInWidget(FString::Printf(TEXT("NValue recv data success.  N : %d"), _Packet.Get()->N), GetWorld());
		});

	_Interpret->AddHandler<FRecvPathPacket>([this](TSharedPtr<FRecvPathPacket> _Packet)
		{
			int32 MoverID = _Packet->ID;
			int32 PathInfoSize = _Packet->PathInfoSize;
			TArray<int32>& PathInfo = _Packet->PathInfo;

			UE_LOG(LogType, Log, TEXT("[MoverID : %d] RecvData"), MoverID);

			// Path정보 변환 (FVector2D)
			int32 ConvertPathSize = PathInfoSize >> 1;
			TArray<FVector2D> ConvertPathInfo;
			ConvertPathInfo.Reserve(ConvertPathSize);
			for (int32 i = 0; i < ConvertPathSize; ++i)
			{
				ConvertPathInfo.Add(FVector2D{ StaticCast<double>(PathInfo[2 * i]), StaticCast<double>(PathInfo[2 * i + 1]) });
			}

			AClientPlayGameMode* CurGameMode = UGlobalFunctonLibrary::GetClientPlayGameMode(GetWorld());
			if (CurGameMode)
			{
				ASimulatorManager* SM = CurGameMode->GetMainSimulator().Get();
				if (SM)
				{
					// 경로를 Mover에 보내기전에 경로를 요약한다. (꺾이는 부분이 어딘지를 기준으로, 실제 좌표로)
					TArray<FVector2D> ModyfiedPathInfo = SM->PathModify(ConvertPathInfo);

					// SimulatorManager의 Mover에 해당되는 ID의 로봇에 Path 정보 세팅
					SM->FindMover(MoverID)->SetWayPoints(ModyfiedPathInfo);

					// SimulatorManager의 Mover에 해당되는 ID의 로봇에게 현재 상태 바꾸기 (대기 상태 테스크 노드 추가 필요)
					SM->FindMover(MoverID)->SetIsPathRecv();
				}
			}

			UGlobalFunctonLibrary::LoggingInWidget(FString::Printf(TEXT("[MoverID : %d] Get path information sucessfully!"), MoverID), GetWorld());
		});
}
