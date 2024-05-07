#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"

bool	is_valid_port(std::string const & port)
{
	if (port.empty())
		return false;

	for (std::string::const_iterator it = port.begin(); it != port.end(); it++)
	{
		char	to_check = *it;
		if (std::isdigit(to_check) == false)
			return false;
	}

	if (atoi(port.c_str()) < 1024 || atoi(port.c_str()) > 49151)
		return false;
	return true;
}

bool is_valid_password(std::string const & password)
{
	if (password.empty())
		return false;

	for (std::string::const_iterator it = password.begin(); it != password.end(); ++it) {
		char to_check = *it;
		if (std::isspace(to_check))
			return false;
	}
	return true;
}

bool	is_arg_valid(int argc, char **argv)
{
	if (argc != EXPECTED_ARGC)
	{
		std::cout << ERROR_ARG;
		return false;
	}

	if (is_valid_port(argv[1]) == false)
	{
		std::cout << ERROR_PORT;
		return false;
	}

	if (is_valid_password(argv[2]) == false)
	{
		std::cout << ERROR_PASS;
		return false;
	}
	return true;
}