#include "LogFIle.h"


LogFIle::LogFIle()
{
	Logfile.open(&GlobalFilePath::LogFilePath[0], std::ios::out | std::ios::trunc);
	if (!Logfile.is_open())
	{
		std::cerr << "Error: Unable to open log file!" << std::endl;
		return;
	}
}

LogFIle::~LogFIle()
{
	if (Logfile.is_open())
	{
		Logfile.close();
	}
}

void LogFIle::Logging(const std::string& _Msg)
{
	if (Logfile.is_open())
	{
		Logfile << _Msg << std::endl;
	}
	else
	{
		std::cerr << "Error: Log file is not open!" << std::endl;
	}
}

