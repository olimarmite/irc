#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/ChannelManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"

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
//void	handle_priave_message(UserManager &_user_manager, ClientManager &_client_manager, Client &client, std::string args)
//void	handle_channel_message(ChannelManager &_channel_manager, UserManager &_user_manager, ClientManager &_client_manager, const ServerSettings &_server_settings, Client &client, std::string args)