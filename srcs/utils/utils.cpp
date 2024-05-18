#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"

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

// Ports
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

// Passwords
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

// // Nicknames
// bool	does_nickname_have_channel_prefix(std::string const & nickname)
// {
// 	if (
// 		nickname[0] == '#' ||
// 		nickname[0] == '&' ||
// 		nickname[0] == '~' ||
// 		nickname[0] == '@' ||
// 		nickname[0] == '%' ||
// 		nickname[0] == ':'
// 		)
// 			return true;

// 	if (nickname[0] == '+' && nickname[1])
// 	{
// 		if (
// 			nickname[1] == 'q' ||
// 			nickname[1] == 'a' ||
// 			nickname[1] == 'o' ||
// 			nickname[1] == 'h' ||
// 			nickname[1] == 'v'
// 			)
// 			return true;
// 	}

// 	return false;
// }

// bool	does_nickname_already_exist(std::string const & nickname, UserManager & _user_manager)
// {
// 	if (_user_manager.user_exists(nickname) == true)
// 		return true;
// 	return false;
// }

// bool	is_nickname_valid(std::string const & nickname, UserManager & _user_manager, User & user, Client &client)
// {
// 	(void)user;
	
// 	if (nickname.empty())
// 	{
// 		if (DEBUG)
// 			std::cout << BRED << ERR_NONICKNAMEGIVEN(SERVER_NAME) << PRINT_END;
// 		client.write(ERR_NONICKNAMEGIVEN(SERVER_NAME));
// 		return false;
// 	}

// 	std::string	invalid = " ,*?!@.$:";
// 	if (does_nickname_have_channel_prefix(nickname) == true || nickname.find_first_of(invalid) != std::string::npos)
// 	{
// 		if (DEBUG)
// 			std::cout << BRED << ERR_ERRONEUSNICKNAME(SERVER_NAME, nickname) << PRINT_END;
// 		client.write(ERR_ERRONEUSNICKNAME(SERVER_NAME, nickname));
// 		return false;
// 	}

// 	if (does_nickname_already_exist(nickname, _user_manager) == true)
// 	{
// 		if (DEBUG)
// 			std::cout << BRED << ERR_NICKNAMEINUSE(SERVER_NAME, nickname) << PRINT_END;
// 		client.write(ERR_NICKNAMEINUSE(SERVER_NAME, nickname));
// 		return false;
// 	}

// 	return true;
// }

// Channels
bool	is_valid_channel_prefix(char c)
{
	if (c == '#' || c == '&' || c == '+' || c == '!')
		return true;
	return false;
}

bool	is_channel_valid(std::string const & channel)
{
	if (channel.empty())
	{
		if (DEBUG)
			std::cout << BRED "Empty Channel Name" << PRINT_END;
		return false;
	}

	std::string	invalid = " \x07,";
	if (
		(is_valid_channel_prefix(channel[0]) == false) ||
		(channel.length() > 50) ||
		(channel.find_first_of(invalid) != std::string::npos)
		)
	{
		if (DEBUG)
			std::cout << BRED "Invalid channel name" PRINT_END;
		return false;
	}

	return true;
}