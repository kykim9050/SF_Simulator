#pragma once
#include <map>
#include <functional>
#include <memory>
#include <string>
#include <assert.h>
#include <Windows.h>
#include "ServerProtocol.h"


// 설명 : 패킷을 해석하는 방법과 관련된 클래스
class Interpreter
{
public:
	// constrcuter destructer
	Interpreter();
	~Interpreter();

	// delete Function
	Interpreter(const Interpreter& _Other) = delete;
	Interpreter(Interpreter&& _Other) noexcept = delete;
	Interpreter& operator=(const Interpreter& _Other) = delete;
	Interpreter& operator=(Interpreter&& _Other) noexcept = delete;

	template<typename PacketType>
	void AddHandler(std::function<void(std::shared_ptr<PacketType>)> _CallBack)
	{
		PacketType PacketInstance;
		int Type = static_cast<int>(PacketInstance.GetPacketType());
		AddHandler(Type, _CallBack);
	}

	template<typename PacketType>
	void AddHandler(int _Type, std::function<void(std::shared_ptr<PacketType>)> _CallBack)
	{
		if (true == PacketHandlers.contains(_Type))
		{
			std::string ErrorText = std::string("이미 등록된 핸들러를 또 등록시킬수는 없습니다.");
			MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK);
			assert(false);
			return;
		}

		// 해당 패킷의 Deserialize 함수를 실행한 결과를 담고 있음
		ConvertPacketHandlers[_Type] = [=](ServerSerializer& _Ser) {
			std::shared_ptr<PacketType> NewPacket = std::make_shared<PacketType>();
			NewPacket->DeSerialize(_Ser);
			return NewPacket;
			};

		// 특정 패킷관련 콜백함수 실행
		PacketHandlers[_Type] = [=](std::shared_ptr<ServerProtocol> _Packet) {
			std::shared_ptr<PacketType> ConvertPacket = std::dynamic_pointer_cast<PacketType>(_Packet);
			if (nullptr == ConvertPacket)
			{
				std::string ErrorText = std::string("타입이 일치하지 않는 패킷입니다.");
				MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK);
				assert(false);
				return;
			}

			_CallBack(ConvertPacket);
			};
	}

	std::shared_ptr<ServerProtocol> ConvertProtocol(int _Type, ServerSerializer& _Ser);

	void ProcessPacket(std::shared_ptr<ServerProtocol> _Packet);

protected:

private:

	std::map<int, std::function<std::shared_ptr<ServerProtocol>(ServerSerializer& _Ser)>> ConvertPacketHandlers;

	std::map<int, std::function<void(std::shared_ptr<ServerProtocol>)>> PacketHandlers;
};

