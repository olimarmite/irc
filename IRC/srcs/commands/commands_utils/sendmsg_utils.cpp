#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/ChannelManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"

std::string	parse_channel_name(std::string args)
{
	std::istringstream	ss(args);
	std::string			channel_name;
	std::getline(ss, channel_name, ' ');

	return channel_name;
}

std::string parse_nickname(std::string args)
{
	std::istringstream	ss(args);
	std::string			nickname;
	std::getline(ss, nickname, ' ');

	return nickname;
}

std::string parse_message(std::string args)
{
	std::istringstream	ss(args);
	std::string			to_throw, message;
	std::getline(ss, to_throw, ' ');
	std::getline(ss, to_throw, ':');
	std::getline(ss, message);

	return message;
}

bool	is_it_private_message(std::string args)
{
	if (args[0] != '#')
		return true;
	return false;
}