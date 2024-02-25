/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "FileLogger.h"

#include "..\macros.h"

#include <fstream>
#include <iomanip>
#include <time.h>

namespace ige
{
	ige::FileLogger menyooLogObject("menyooLog.txt");
	std::ofstream& myLog = menyooLogObject.myFile;

	FileLogger::FileLogger(std::string fname)
	{
		myFile.open(fname.c_str());

		if (myFile.is_open())
		{
			time_t now = time(0);
			tm t;
			localtime_s(&t, &now);

			myFile << "Menyoo " << MENYOO_CURRENT_VER_ << std::endl;
			myFile << "Log file created " << std::setfill('0') << std::setw(2) << t.tm_mday << "/" << std::setfill('0') << std::setw(2) << (t.tm_mon + 1) << "/" << t.tm_year + 1900 << std::endl << std::endl << std::endl;
		}

	}

	FileLogger::~FileLogger()
	{
		if (myFile.is_open())
		{
			myFile << std::endl << std::endl;

			myFile.close();
		}

	}

	void addlog(int loglevel, ige::LogType logType, std::string message)
	{
		if (static_cast<int>(logType) <= loglevel)
		{
			ige::myLog << logType << message << std::endl;
		}
	}
}

std::ofstream& operator<<(std::ofstream& stream, ige::LogType logType)
{
	time_t now = time(0);
	tm t;
	localtime_s(&t, &now);

	switch (logType)
	{
	case ige::LogType::LOG_INIT: stream << "INIT: "; break;
	case ige::LogType::LOG_ERROR: stream << "ERROR: "; break;
	case ige::LogType::LOG_WARNING: stream << "WARNING: "; break;
	case ige::LogType::LOG_INFO: stream << "INFO: "; break;
	case ige::LogType::LOG_DEBUG: stream << "DEBUG: "; break;
	case ige::LogType::LOG_TRACE: stream << "TRACE: "; break;
	}

	stream << "[" << std::setfill('0') << std::setw(2) << t.tm_hour << ":" << std::setfill('0') << std::setw(2) << t.tm_min << ":" << std::setfill('0') << std::setw(2) << t.tm_sec << "] ";

	return stream;
}

