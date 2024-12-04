#include "Interpreter.h"

Interpreter::Interpreter()
{
}

Interpreter::~Interpreter()
{
}

std::shared_ptr<ServerProtocol> Interpreter::ConvertProtocol(int _Type, ServerSerializer& _Ser)
{
    if (false == ConvertPacketHandlers.contains(_Type))
    {
        std::string ErrorText = std::string("처리방법이 지정되지 않은 패킷입니다.");
        MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK);
        assert(false);
        return nullptr;
    }

    return ConvertPacketHandlers[_Type](_Ser);
}

void Interpreter::ProcessPacket(std::shared_ptr<ServerProtocol> _Packet)
{
    if (false == ConvertPacketHandlers.contains(_Packet->GetPacketType()))
    {
        std::string ErrorText = std::string("처리방법이 지정되지 않은 패킷입니다.");
        MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK);
        assert(false);
        return;
    }

    return PacketHandlers[_Packet->GetPacketType()](_Packet);
}