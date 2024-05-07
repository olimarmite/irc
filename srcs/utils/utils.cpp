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

bool	does_nickname_have_channel_prefix(std::string const & nickname)
{
	if (
		nickname[0] == '#' ||
		nickname[0] == '&' ||
		nickname[0] == '~' ||
		nickname[0] == '@' ||
		nickname[0] == '%'
		)
			return true;

	if (nickname[0] == '+' && nickname[1])
	{
		if (
			nickname[1] == 'q' ||
			nickname[1] == 'a' ||
			nickname[1] == 'o' ||
			nickname[1] == 'h' ||
			nickname[1] == 'v'
			)
			return true;
	}

	return false;
}

bool	is_nickname_valid(std::string const & nickname)
{
	if (nickname.empty())
	{
		std::cout << BRED "Empty nickname" PRINT_END;
		return false;
	}

	if (does_nickname_have_channel_prefix(nickname) == true)
	{
		std::cout << BRED "Nickname cannot have a channel prefix" PRINT_END;
		return false;
	}

	std::string	invalid = " ,*?!@.$:";
	if (nickname.find_first_of(invalid) != std::string::npos)
	{
		std::cout << BRED "Invalid characters within nickname" PRINT_END;
		return false;
	}

	return true;
}

bool	is_channel_valid(std::string const & channel)
{
	if (channel.empty())
	{
		std::cout << BRED "Empty channel name" PRINT_END;
		return false;
	}
	
	std::string	invalid = " ,\x07";
	if ((channel[0] != '#' && channel[0] != '&') || (channel.find_first_of(invalid) != std::string::npos))
	{
		std::cout << BRED "Invalid characters within channel name" PRINT_END;
		return false;
	}

	return true;
}