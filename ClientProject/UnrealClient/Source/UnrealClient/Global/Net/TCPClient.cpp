// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Net/TCPClient.h"
#include "Global/Net/ClientPacketManager.h"

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
	// ��Ŷ ����
	TSharedPtr<FBufferArchive> Packet = UClientPacketManager::CreatePacket<FRequestNPacket>(_Data);

	SendData(*Packet.Get());
}

void ATCPClient::SendData(const FBufferArchive& _PacketData)
{
	UE_LOG(LogType, Log, TEXT("BeginSend"));

	// Blocking ���� �ذ��� ���� AsyncTask ���
	AsyncTask(ENamedThreads::AnyThread, [this, _PacketData]()
		{
			if (nullptr == TCPClientSocket || nullptr == this)
			{
				UGlobalFunctonLibrary::LoggingInWidget(TEXT("No valid socket, Cant Send Data"), GetWorld());
				return;
			}

			// ��Ŷ�� ���� ���� Send
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
			// Queue�� �������� �����Ͱ� �ִ��� ���� Ȯ��
			if (TCPClientSocket->HasPendingData(PendingDataSize))
			{
				// �о�� ����
				TArray<uint8> Buffer;
				Buffer.SetNumUninitialized(PendingDataSize);
				int32 NumRead = 0;
				bool bSuccessRecv = false;

				// Recv�� �������� ������ �ޱ� (���� �����Ͱ� Buffer�� �޾ƿ�����)
				bSuccessRecv = TCPClientSocket->Recv(Buffer.GetData(), Buffer.Num(), NumRead, ESocketReceiveFlags::Type::WaitAll);

				AsyncTask(ENamedThreads::GameThread, [this, Buffer, bSuccessRecv]()
					{
						if (TCPClientSocket == nullptr || this == nullptr)
						{
							return;
						}

						// ���������� �����ߴٸ�
						if (bSuccessRecv)
						{
							// ���Ź��� Buffer �����͸� FMemoryReader Ŭ������ �޾Ƽ� �ؼ�
							// �𸮾󿡼� Serialize�� Read, Write�� ��� << �����ڷ� ���
							FMemoryReader Reader(Buffer);
							FClientProtocol RecvData;
							Reader << RecvData;

							// ���� ��Ŷ�� � Ÿ������ Ȯ��
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
						else // ���������� ���� ���ߴٸ�
						{
							UE_LOG(LogType, Error, TEXT("Recv Payload Failed."));
							UE_LOG(LogType, Log, TEXT("End Recv Phase"));
						}
					});
			}
		});

}
