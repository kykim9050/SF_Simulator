#pragma once
#include <memory>
#include "ServerSerializer.h"


// ���� : Server �� �������� Ŭ����
class ServerProtocol : public std::enable_shared_from_this<ServerProtocol>, public SerializeObject
{
public:

	ServerProtocol()
		:Type(0)
		,Size(0)
	{

	}

	ServerProtocol(int _Size)
		:Type(0)
		, Size(_Size)
	{

	}

	ServerProtocol(int _Type, int _Size)
		:Type(_Type)
		, Size(_Size)
	{

	}

	// delete Function
	ServerProtocol(const ServerProtocol& _Other) = delete;
	ServerProtocol(ServerProtocol&& _Other) noexcept = delete;
	ServerProtocol& operator=(const ServerProtocol& _Other) = delete;
	ServerProtocol& operator=(ServerProtocol&& _Other) noexcept = delete;

	void Serialize(ServerSerializer& _Ser) override
	{
		_Ser << Type;
		_Ser << Size;
	}

	void DeSerialize(ServerSerializer& _Ser) override
	{
		_Ser >> Type;
		_Ser >> Size;
	}

	int GetPacketType() const
	{
		return Type;
	}

	ServerSerializer GetSerialize()
	{
		ServerSerializer Ser;
		Serialize(Ser);
		Size = Ser.GetWriteOffset() - GetHeaderSize();
		Ser.Paste(sizeof(int), &Size, sizeof(Size));

		return Ser;
	}

protected:
	int Type = 0;
	int Size = 0;

	template<typename PType>
	void SetType(PType _Type)
	{
		Type = static_cast<int>(_Type);
	}

private:
	int GetHeaderSize() const
	{
		return sizeof(Type) + sizeof(Size);
	}
};

