#pragma once
#include <string>

struct ServerSettings
{
	const std::string password;
	const std::string port;
	ServerSettings(const std::string& password, const std::string& port)
		: password(password), port(port) {}
};
