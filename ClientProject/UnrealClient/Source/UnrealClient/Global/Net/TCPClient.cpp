// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Net/TCPClient.h"

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
	UE_LOG(LogType, Log, TEXT("BeginSend"));
	
	// 패킷 생성
	TSharedPtr<FBufferArchive> Packet = CreatePacket(0, TEXT("Start Packet"));

	// Blocking 현상 해결을 위한 AsyncTask 사용
	AsyncTask(ENamedThreads::AnyThread, [this, Packet]()
		{
			if (nullptr == TCPClientSocket || nullptr == this)
			{
				UGlobalFunctonLibrary::LoggingInWidget(TEXT("No valid socket, Cant Send Data"), GetWorld());
				return;
			}

			// 패킷에 담은 정보 Send
			int32 NumSend;
			bool bSuccess = TCPClientSocket->Send(Packet->GetData(), Packet->Num(), NumSend);

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
			if (TCPClientSocket->HasPendingData(PendingDataSize))
			{
				// 읽어올 버퍼
				TArray<uint8> Buffer;
				Buffer.SetNumUninitialized(PendingDataSize);
				int32 NumRead = 0;
				bool bSuccessRecv = false;

				// Recv로 서버에서 데이터 받기
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
							TArray<uint8> Payload;
							Payload.Append(Buffer);
							FString Data(Payload.Num(), (char*)Payload.GetData());
							UE_LOG(LogTemp, Log, TEXT("OnRecvCompleted  recv data success.  data : %s  Payload : %d  size : %d"), *Data, Payload.Num(), Data.Len());
							UGlobalFunctonLibrary::LoggingInWidget(Data, GetWorld());
							UE_LOG(LogTemp, Log, TEXT("End Recv Phase"));
						}
						else // 성공적으로 수신 못했다면
						{
							UE_LOG(LogTemp, Error, TEXT("Recv Payload Failed."));
							UE_LOG(LogTemp, Log, TEXT("End Recv Phase"));
						}
					});
			}
		});

}

TSharedPtr<FBufferArchive> ATCPClient::CreatePacket(uint32 _InType, const uint8* _InPayload, int32 _InPayloadSize)
{
	FClientProtocol Header(_InType, _InPayloadSize);
	constexpr static int32 HeaderSize = sizeof(FClientProtocol);

	TSharedPtr<FBufferArchive> Packet = MakeShareable(new FBufferArchive());

	(*Packet) << Header;

	Packet->Append(_InPayload, _InPayloadSize);

	return Packet;
}

TSharedPtr<FBufferArchive> ATCPClient::CreatePacket(uint32 _InType, const FString& _Data)
{
	FTCHARToUTF8 Convert(*_Data);
	FArrayWriter WriteArray = FArrayWriter();

	WriteArray.Serialize((UTF8CHAR*)Convert.Get(), Convert.Length());
	TSharedPtr<FBufferArchive> Packet = CreatePacket(_InType, WriteArray.GetData(), WriteArray.Num());
	
	return Packet;
}
