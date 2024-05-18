
#pragma once

#include <string>

struct ServerSettings
{
	std::string port;
	std::string password;

	ServerSettings(std::string port, std::string password) : port(port), password(password) {}
};
