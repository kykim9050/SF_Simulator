// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/Net/ClientInterpreter.h"

TSharedPtr<FRecvBaseProtocol> UClientInterpreter::ConvertProtocol(int32 _Type, FMemoryArchive& _ReadMem)
{
	if (false == ConvertPacketHandlers.Handlers.Contains(_Type))
	{
		UE_LOG(LogType, Fatal, TEXT("This is a packet with no processing method specified."));
		return nullptr;
	}

	return ConvertPacketHandlers.Handlers[_Type].Execute(_ReadMem);
}

void UClientInterpreter::ProcessPacket(TSharedPtr<FRecvBaseProtocol> _Packet)
{
	if (false == ConvertPacketHandlers.Handlers.Contains(_Packet->GetType()))
	{
		// ���� Fatal�� ���� �ʿ�
		UE_LOG(LogType, Fatal, TEXT("This is a packet with no processing method specified."));
		return;
	}

	return PacketHandlers.Handlers[_Packet->GetType()].Execute(_Packet);
}
