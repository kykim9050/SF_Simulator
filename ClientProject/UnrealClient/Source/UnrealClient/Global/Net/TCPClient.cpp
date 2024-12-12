// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Net/TCPClient.h"
#include "Global/Net/ClientPacketManager.h"

ATCPClient::ATCPClient()
	:TCPClientSocket(nullptr)
{

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
	return true;
}

void ATCPClient::SendData(const FString& _Data)
{
	// 패킷 생성
	TSharedPtr<FBufferArchive> Packet = UClientPacketManager::CreatePacket<FRequestNPacket>(_Data);

	SendData(*Packet.Get());
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
						UE_LOG(LogType, Log, TEXT("End Send Phase"));
						RecvData();
					}
					else
					{
						UE_LOG(LogType, Log, TEXT("Send Error"));
						UE_LOG(LogType, Log, TEXT("End Send Phase"));
						RecvData();
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
			// Queue에 보류중인 데이터가 있는지 먼저 확인
			if (TCPClientSocket->HasPendingData(PendingDataSize))
			{
				// 읽어올 버퍼
				TArray<uint8> Buffer;
				Buffer.SetNumUninitialized(PendingDataSize);
				int32 NumRead = 0;
				bool bSuccessRecv = false;

				// Recv로 서버에서 데이터 받기 (실제 데이터가 Buffer에 받아와진다)
				bSuccessRecv = TCPClientSocket->Recv(Buffer.GetData(), Buffer.Num(), NumRead, ESocketReceiveFlags::Type::WaitAll);

				AsyncTask(ENamedThreads::GameThread, [this, Buffer, bSuccessRecv]()
					{
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
							FClientProtocol RecvData;
							Reader << RecvData;

							// 받은 패킷이 어떤 타입인지 확인
							switch (RecvData.Type)
							{
							case static_cast<int>(EPacketType::NValuePacket):
							{
								FString Data(Buffer.Num(), (char*)Buffer.GetData());
								UE_LOG(LogType, Log, TEXT("OnRecvCompleted  recv data success.  data : %s  Payload : %d  size : %d"), *Data, Buffer.Num(), Data.Len());
								UGlobalFunctonLibrary::LoggingInWidget(Data, GetWorld());
								break;
							}
							default:
							{
								UE_LOG(LogType, Fatal, TEXT("Not Exist PacketType"));
								break;
							}
							}

							UE_LOG(LogType, Log, TEXT("End Recv Phase"));
						}
						else // 성공적으로 수신 못했다면
						{
							UE_LOG(LogType, Error, TEXT("Recv Payload Failed."));
							UE_LOG(LogType, Log, TEXT("End Recv Phase"));
						}
					});
			}
		});

}
