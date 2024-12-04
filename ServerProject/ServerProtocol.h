#pragma once
#include <memory>


// 설명 : Server 측 프로토콜 클래스
class ServerProtocol : public std::enable_shared_from_this<ServerProtocol>
{
public:

	ServerProtocol()
		:Type(0)
		,Size(0)
	{

	}

	ServerProtocol(unsigned int _Type, unsigned int _Size)
		:Type(_Type)
		, Size(_Size)
	{

	}

	// delete Function
	ServerProtocol(const ServerProtocol& _Other) = delete;
	ServerProtocol(ServerProtocol&& _Other) noexcept = delete;
	ServerProtocol& operator=(const ServerProtocol& _Other) = delete;
	ServerProtocol& operator=(ServerProtocol&& _Other) noexcept = delete;

protected:
	unsigned int Type = 0;
	unsigned int Size = 0;

private:

};

