#pragma once

#include <string>
#include <map>

class Config {

protected:

	std::map<std::string, std::string> entries;

public:
	void initialize(char const* filename);
	std::string getString(std::string n);
	int getInteger(std::string n);


};