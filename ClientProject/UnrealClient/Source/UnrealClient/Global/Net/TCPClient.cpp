// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Net/TCPClient.h"

ATCPClient::ATCPClient()
	:TCPClientSocket(nullptr)
{

}

ATCPClient::~ATCPClient()
{
	// ������ Ȱ��ȭ �Ǿ� �ִٸ�
	if (nullptr != TCPClientSocket)
	{
		// ���� ��ȯ
		TCPClientSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(TCPClientSocket);
	}
}

bool ATCPClient::ConnectToServer(const FString& _IPAddress, int32 _Port)
{
	// ����� ���� ���ϼ��� �ý���
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (nullptr == SocketSubsystem)
	{
		UE_LOG(LogType, Error, TEXT("if (nullptr == SocketSubsystem)"));
		return false;
	}

	// FIPv4Address ����ü�� ���ڿ��� �־��� IP�ּҸ� ���� �����ν� ��Ī
	FIPv4Address IP = FIPv4Address();
	if (false == FIPv4Address::Parse(_IPAddress, IP))
	{
		UE_LOG(LogType, Error, TEXT("if (false == FIPv4Address::Parse(_IPAddress, IP))"));
		return false;
	}

	// TCP �������� ����
	TCPClientSocket = SocketSubsystem->CreateSocket(FName(TEXT("Stream")), TEXT("TCP Client Socket"));
	
	// Server�� �����ϱ� ���� IP�� ��Ʈ ������ FInternetAddr�� ����
	TSharedRef<FInternetAddr> ServerAddress = SocketSubsystem->CreateInternetAddr();
	ServerAddress->SetIp(IP.Value);
	ServerAddress->SetPort(_Port);

	// ������ ���� Connect ����
	if (false == TCPClientSocket->Connect(*ServerAddress))
	{
		// ���� ����
		UE_LOG(LogType, Error, TEXT("Failed connect to Server"));
		UGlobalFunctonLibrary::LoggingInWidget(TEXT("Failed connect to Server"), GetWorld());
		return false;
	}

	// ���� ����
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


	// �ø�������� (������ ����ȭ)
	FTCHARToUTF8 Convert(*_Data);
	FArrayWriter WriterArray;
	WriterArray.Serialize((UTF8CHAR*)Convert.Get(), Convert.Length());
	
	// ��Ŷ�� �ø��������� ������ ����
	TSharedPtr<FBufferArchive> Packet = MakeShareable(new FBufferArchive());
	(*Packet) << WriterArray;

	// Blocking ���� �ذ��� ���� AsyncTask ���
	AsyncTask(ENamedThreads::AnyThread, [this, Packet]()
		{
			if (nullptr == TCPClientSocket || nullptr == this)
			{
				return;
			}

			// ��Ŷ�� ���� ���� Send
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
						// ���� �� Recv ���·� ���ư���. ��� ���� BackGround����
						int a = 0;
					}
					else
					{
						// Send ���н� Action
						int a = 0;
					}
				});

		});
}
