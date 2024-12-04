#pragma once
#include <map>
#include <functional>
#include <memory>
#include <string>
#include <assert.h>
#include <Windows.h>
#include "ServerProtocol.h"


// ���� : ��Ŷ�� �ؼ��ϴ� ����� ���õ� Ŭ����
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
			std::string ErrorText = std::string("�̹� ��ϵ� �ڵ鷯�� �� ��Ͻ�ų���� �����ϴ�.");
			MessageBoxA(nullptr, ErrorText.c_str(), "ġ���� ����", MB_OK);
			assert(false);
			return;
		}

		// �ش� ��Ŷ�� Deserialize �Լ��� ������ ����� ��� ����
		ConvertPacketHandlers[_Type] = [=](ServerSerializer& _Ser) {
			std::shared_ptr<PacketType> NewPacket = std::make_shared<PacketType>();
			NewPacket->DeSerialize(_Ser);
			return NewPacket;
			};

		// Ư�� ��Ŷ���� �ݹ��Լ� ����
		PacketHandlers[_Type] = [=](std::shared_ptr<ServerProtocol> _Packet) {
			std::shared_ptr<PacketType> ConvertPacket = std::dynamic_pointer_cast<PacketType>(_Packet);
			if (nullptr == ConvertPacket)
			{
				std::string ErrorText = std::string("Ÿ���� ��ġ���� �ʴ� ��Ŷ�Դϴ�.");
				MessageBoxA(nullptr, ErrorText.c_str(), "ġ���� ����", MB_OK);
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

