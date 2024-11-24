// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Net/TCPClient.h"

UTCPClient::UTCPClient()
{

}

UTCPClient::~UTCPClient()
{
	// ������ Ȱ��ȭ �Ǿ� �ִٸ�
	if (nullptr != ClientSocket)
	{
		// ���� ��ȯ
		ClientSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
	}
}

bool UTCPClient::ConnectToServer(const FString& _IPAddress, int32 _Port)
{
	// ����� ���� ���ϼ��� �ý���
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (nullptr == SocketSubsystem)
	{
		UE_LOG(LogType, Error, TEXT("if (nullptr == SocketSubsystem)"));
		return false;
	}

	return true;
}
