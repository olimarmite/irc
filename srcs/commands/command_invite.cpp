
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
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
	const ServerSettings &_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;
	(void)_client_manager;
	(void)_settings;


	std::string	channel_name, nickname;

	std::istringstream iss(args);

	if (!(iss >> channel_name >> nickname) || channel_name.empty() || nickname.empty())
	{
		client.write("Invalid arguments\n");
		return ;
	}

	if (_channel_manager.channel_exists(channel_name) == false)
	{
		client.write("Channel " + channel_name + " does not exist.\n");
		return ;
	}




	int	user_fd = 0;

	Channel &channel = _channel_manager.get_channel(channel_name);
	User &user_to_invite = _user_manager.get_user(user_fd);

	nickname = user_to_invite.get_nickname();

	channel.clients_fd.insert(user_to_invite.get_fd());
	client.write(nickname + " has been invited to channel " + channel_name + "\n"); // check dalnet

	//TODO ? or not ?
	//RFC --> <client><nick><channel>

	return ;
}


