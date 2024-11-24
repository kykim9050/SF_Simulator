// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Net/TCPClient.h"

UTCPClient::UTCPClient()
{

}

UTCPClient::~UTCPClient()
{
	// 소켓이 활성화 되어 있다면
	if (nullptr != ClientSocket)
	{
		// 소켓 반환
		ClientSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
	}
}

bool UTCPClient::ConnectToServer(const FString& _IPAddress, int32 _Port)
{
	// 통신을 위한 소켓서브 시스템
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (nullptr == SocketSubsystem)
	{
		UE_LOG(LogType, Error, TEXT("if (nullptr == SocketSubsystem)"));
		return false;
	}

	return true;
}
