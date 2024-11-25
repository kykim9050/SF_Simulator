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
	if (nullptr == TCPClientSocket)
	{
		UE_LOG(LogType, Error, TEXT("No valid socket"));
		UGlobalFunctonLibrary::LoggingInWidget(TEXT("No valid socket, Cant Send Data"), GetWorld());
		return;
	}

	UE_LOG(LogType, Log, TEXT("BeginSend"));


	// 시리얼라이즈 (데이터 직렬화)
	FTCHARToUTF8 Convert(*_Data);
	FArrayWriter WriterArray;
	WriterArray.Serialize((UTF8CHAR*)Convert.Get(), Convert.Length());
	
	// 패킷에 시리얼라이즈된 정보를 대입
	TSharedPtr<FBufferArchive> Packet = MakeShareable(new FBufferArchive());
	(*Packet) << WriterArray;

	// Blocking 현상 해결을 위한 AsyncTask 사용
	AsyncTask(ENamedThreads::AnyThread, [this, Packet]()
		{
			if (nullptr == TCPClientSocket || nullptr == this)
			{
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
						// 성공 시 Recv 상태로 돌아가기. 대신 대기는 BackGround에서
						int a = 0;
					}
					else
					{
						// Send 실패시 Action
						int a = 0;
					}
				});

		});
}
