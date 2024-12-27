#pragma once
#include <fstream>
#include <iostream>
#include "GlobalValue.h"

// 설명 : 로깅 파일 관련 클래스
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
	/// 파일에 로그 정보를 저장
	/// </summary>
	/// <param name="_Msg"></param>
	void Logging(const std::string& _Msg);

protected:

private:
	/// <summary>
	/// 로그 파일
	/// </summary>
	std::ofstream Logfile;
};

