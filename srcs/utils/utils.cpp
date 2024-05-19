#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/ChannelManager.hpp"
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

// Channels
bool	is_check_all_channel_valid(std::string const & channel_name, std::string const & password, Client &client, ChannelManager & _channel_manager)
{
	if (is_channel_name_valid(channel_name) == false)
		return false;

	if (_channel_manager.channel_exists(channel_name) == true)
	{
		Channel channel = _channel_manager.get_channel(channel_name);
		if (is_channel_invite_only(channel, client, channel_name) == false)
			return false;

		if (is_channel_key_protected(channel, client, channel_name, password) == false)
			return false;
	}

	return true;
}

bool	is_valid_channel_prefix(char c)
{
	if (c == '#' || c == '&' || c == '+' || c == '!')
		return true;
	return false;
}

bool	is_channel_name_valid(std::string const & channel)
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

bool is_channel_invite_only(Channel & channel, Client &client, std::string const & channel_name)
{
	if (channel.is_invite_only == true)
	{
		client.write(ERR_INVITEONLYCHAN(SERVER_NAME, channel_name));
		return false;
	}
	return true;
}

bool	is_channel_key_protected(Channel & channel, Client &client, std::string const & channel_name, std::string const & password)
{
	if (channel.is_key_needed == true && channel.password != password)
	{
		client.write(ERR_BADCHANNELKEY(SERVER_NAME, channel_name));
		return false;
	}
	return true;
}
