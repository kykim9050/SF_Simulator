#pragma once
#include <fstream>
#include <iostream>
#include "GlobalValue.h"

// ���� : �α� ���� ���� Ŭ����
class LogFIle
{
public:
	// constrcuter destructer
	LogFIle();
	~LogFIle();

	// delete Function
	LogFIle(const LogFIle& _Other) = delete;
	LogFIle(LogFIle&& _Other) noexcept = delete;
	LogFIle& operator=(const LogFIle& _Other) = delete;
	LogFIle& operator=(LogFIle&& _Other) noexcept = delete;

	/// <summary>
	/// ���Ͽ� �α� ������ ����
	/// </summary>
	/// <param name="_Msg"></param>
	void Logging(const std::string& _Msg);

protected:

private:
	/// <summary>
	/// �α� ����
	/// </summary>
	std::ofstream Logfile;
};

