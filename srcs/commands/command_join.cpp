#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <string>

#include "IrcReplies.hpp"


void	command_join(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_user_manager;
	(void)_client_manager;
	(void)_settings;


	std::string const & channel_name = args;
	std::string const & password = "";

	if (_channel_manager.channel_exists(channel_name) == false)
		_channel_manager.create_channel(channel_name, password);

	_channel_manager.print_all_channels();

	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
	{
		_channel_manager.join_channel(client.get_fd(), channel_name);

		// std::string const & message = "User has joined " + channel_name;
		// _channel_manager.send_message_to_channel(client.get_fd(), channel_name, message);

		//HERE : remplacer les deux lignes mises en commentaire au dessus par
		//message tel que dans dalnetFirstToJoin.log et dalnetSecondToJoin.log
	}



}
