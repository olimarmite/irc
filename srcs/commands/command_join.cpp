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
	Client &client,
	std::string const &args
	)
{
	std::string const & channel_name = args;
	std::string const & password = "";

	if (is_channel_valid(channel_name) == false)
		return ;

	User user = _user_manager.get_user(client.get_fd());

	if (_channel_manager.channel_exists(channel_name) == false)
	{
		_channel_manager.create_channel(channel_name, password);
		user.set_is_operator(true);
	}

	if (DEBUG)
		_channel_manager.print_all_channels();

	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
	{
		_channel_manager.join_channel(client.get_fd(), channel_name);
		
		Channel channel = _channel_manager.get_channel(channel_name);

		client.write(RPL_TOPIC2(user.get_nickname(), user.get_username(), channel_name, channel.topic));
		client.write(JOINED_CHANNEL(user.get_nickname(), user.get_username(), channel_name));
	}

	return ;
}
