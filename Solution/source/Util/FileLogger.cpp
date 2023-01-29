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
#include <time.h>

namespace ige
{
	ige::FileLogger menyooLogObject("menyooLog.txt");
	std::ofstream& myLog = menyooLogObject.myFile;

	FileLogger::FileLogger(const char* fname)
	{
		myFile.open(fname);

		if (myFile.is_open())
		{
			time_t now = time(0);
			tm t;
			localtime_s(&t, &now);

			myFile << "Menyoo " << MENYOO_CURRENT_VER_ << std::endl;
			myFile << "Log file created " << t.tm_mday << "/" << t.tm_mon + 1 << "/" << t.tm_year + 1900 << std::endl << std::endl << std::endl;
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

	std::ofstream& operator<<(std::ofstream& stream, ige::LogType logType)
	{
		time_t now = time(0);
		tm t;
		localtime_s(&t, &now);

		stream << std::endl;

		switch (logType)
		{
		case ige::LogType::LOG_ERROR: stream << "ERROR: "; break;
		case ige::LogType::LOG_WARNING: stream << "WARNING: "; break;
		case ige::LogType::LOG_INFO: stream << "INFO: "; break;
		}

		stream << "[" << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "] ";

		return stream;
	}
}

