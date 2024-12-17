#include "ServerSerializer.h"
#include <assert.h>
#include <string>
#include <Windows.h>

ServerSerializer::ServerSerializer()
{
}

ServerSerializer::~ServerSerializer()
{
}

void ServerSerializer::Paste(int _Offset, const void* _Data, size_t _Size)
{
	if (_Offset + _Size > Data.size())
	{
		std::string ErrorText = std::string("버퍼 범위를 넘어갔습니다.");
		MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK);
		assert(false);
		return;
	}

	memcpy_s(&Data[_Offset], _Size, _Data, _Size);
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

void ServerSerializer::operator<<(const double& _Data)
{
	Write(&_Data, sizeof(double));
}

void ServerSerializer::operator<<(const std::vector<int>& _Data)
{
	for (size_t i = 0; i < _Data.size(); ++i)
	{
		Write(&_Data[i], sizeof(int));
	}
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

void ServerSerializer::operator>>(double& _Data)
{
	Read(&_Data, sizeof(double));
}

