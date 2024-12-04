#include "ServerSerializer.h"

ServerSerializer::ServerSerializer()
{
}

ServerSerializer::~ServerSerializer()
{
}

void ServerSerializer::Write(const void* _Data, size_t _Size)
{
	if (WriteOffset + _Size >= Data.size())
	{
		Data.resize(Data.capacity() * 2 + _Size);
	}

	memcpy_s(&Data[WriteOffset], _Size, _Data, _Size);
	WriteOffset += static_cast<int>(_Size);
}

void ServerSerializer::operator<<(const int& _Data)
{
	Write(&_Data, sizeof(int));
}

void ServerSerializer::operator<<(const unsigned int& _Data)
{
	Write(&_Data, sizeof(unsigned int));
}

void ServerSerializer::Read(void* _Data, size_t _Size)
{
	if (ReadOffset > WriteOffset)
	{
		return;
	}

	memcpy_s(_Data, _Size, &Data[ReadOffset], _Size);
	ReadOffset += static_cast<int>(_Size);
}

void ServerSerializer::operator>>(int& _Data)
{
	Read(&_Data, sizeof(int));
;}

void ServerSerializer::operator>>(unsigned int& _Data)
{
	Read(&_Data, sizeof(unsigned int));
}

