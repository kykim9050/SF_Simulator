// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Net/TCPClient.h"
#include "Global/Net/ClientPacketManager.h"
#include "Playlevel/SimulatorManager.h"
#include "Playlevel/ClientPlayGameMode.h"


ATCPClient::ATCPClient()
	:TCPClientSocket(nullptr)
{
	Interpret = CreateDefaultSubobject<UClientInterpreter>(TEXT("ClientInterpreter"));
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
	
	// ���� ������ ��Ŷ �ؼ����� �ʱ�ȭ
	ClientPacketInit(Interpret);

	return true;
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
							FMessageHeader RecvData;
							Reader << RecvData;

							TSharedPtr<FRecvBaseProtocol> NewProtocol = Interpret->ConvertProtocol(RecvData.Type, Reader);
							Interpret->ProcessPacket(NewProtocol);

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

void ATCPClient::ClientPacketInit(TObjectPtr<UClientInterpreter> _Interpret)
{
	_Interpret->AddHandler<FRecvNPacket>([this](TSharedPtr<FRecvNPacket> _Packet)
		{
			// N���� Client�� ���� �����ҿ� �����ϱ�
			UMainGameInstance* Inst = UGlobalFunctonLibrary::GetMainGameInstance(GetWorld());

			if (Inst)
			{
				// �����κ��� ���� N �� ����
				Inst->SetN(_Packet.Get()->N);
			}

			AClientPlayGameMode* CurGameMode = UGlobalFunctonLibrary::GetClientPlayGameMode(GetWorld());
			if (CurGameMode)
			{
				ASimulatorManager* SM = CurGameMode->GetMainSimulator().Get();
				if (SM)
				{
					// Grid ����
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

			int a = 0;
		});
}
