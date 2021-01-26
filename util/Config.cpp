#include "Config.h"

#include <string>
#include <iostream>
#include <fstream>
#include <raylib.h>


void Config::initialize(char const* filename)
{
	std::string line;
	std::ifstream file(filename);
	if (file.is_open())
	{
		while(std::getline(file, line))
		{			
			size_t pos = line.find('=');
			if (pos != std::string::npos) {
				entries[line.substr(0, pos)] = line.substr(pos + 1);
			}
		}
		file.close();
	}
}

std::string Config::getString(std::string n)
{
	if (entries.find(n) == entries.end()) {
		TraceLog(LOG_WARNING, ("item <"+n + "> not found in config").c_str());
		return "";
	}
	return entries[n];
}

int Config::getInteger(std::string n)
{
	if (entries.find(n) == entries.end()) {
		TraceLog(LOG_WARNING, ("item <" + n + "> not found in config").c_str());
		return 0;
	}
	return std::stoi(entries[n]);
}
