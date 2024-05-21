#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "IrcReplies.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <sstream>
#include <string>

void	command_invite(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;
	(void)_client_manager;
	(void)_server_settings;


	//TODO Olivier - regarder invite, RFC et log irssi

	std::istringstream iss(args);
	std::string	nickname, channel_name;

	if (!(iss >> nickname >> channel_name) || channel_name.empty() || nickname.empty())
	{
		client.write(ERR_NEEDMOREPARAMS(SERVER_NAME, "invite"));
		return ;
	}

	if (is_valid_invite(channel_name, nickname, _user_manager, _channel_manager, client) == false)
		return ;

	int	user_fd = 0;

	Channel &channel = _channel_manager.get_channel(channel_name);
	User &user_to_invite = _user_manager.get_user(user_fd);

	nickname = user_to_invite.get_nickname();
	channel.clients_fd.insert(user_to_invite.get_fd());
	client.write(RPL_INVITING(SERVER_NAME, channel_name, nickname));

	return ;
}


