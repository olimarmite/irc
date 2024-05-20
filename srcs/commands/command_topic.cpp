
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include "IrcReplies.hpp"
#include <iostream>
#include <string>


void	command_topic(
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

	(void)client;

	std::string channel_name = args.substr(0, args.find(" "));
	std::string topic = args.substr(args.find(":") + 1);

	std::cout <<BCYN <<"INSIDE COMMAND TOPIC" <<PRINT_END;

	if (DEBUG)
	{
		std::cout <<BCYN <<"channel name : //" + channel_name + "//" <<PRINT_END;
		std::cout <<BCYN <<"topic : //" + topic + "//" <<PRINT_END;
	}

	Channel channel = _channel_manager.get_channel(channel_name);

	User& user = _user_manager.get_user(client.get_fd());
	if (args.empty() == true)
	{
		std::cout <<BRED <<"Empty args : //" + args + "//" <<PRINT_END;
		if (channel.topic.empty() == true)
		{
			std::cout <<BBLU <<"Empty topic : //" + topic + "//" <<PRINT_END;
			client.write(RPL_NOTOPIC(user.get_nickname(), channel_name));
		}
		else
		{
			std::cout <<BBLU <<"topic : //" + topic + "//" <<PRINT_END;
			client.write(RPL_TOPIC2(user.get_nickname(), user.get_username(), channel_name, channel.topic, "TOPIC"));
		}
	}
	else
	{
		std::cout <<BRED <<"Args : //" + args + "//" <<PRINT_END;
		std::cout <<BBLU <<"topic changed to : //" + topic + "//" <<PRINT_END;
		_channel_manager.set_channel_topic(channel_name, topic);
		// client.write(RPL_TOPIC(user.get_nickname(), channel_name, channel.topic));
		client.write(RPL_TOPIC2(user.get_nickname(), user.get_username(), channel_name, channel.topic, "TOPIC"));
	}

	return ;
}
