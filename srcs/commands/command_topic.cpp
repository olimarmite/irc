
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
	Client &client,
	std::string const &args
	)
{
	std::string channel_name = args.substr(0, args.find(" "));
	std::string topic = args.substr(args.find(":") + 1);

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
	}
	else
	{
		if (DEBUG)
			std::cout <<BBLU <<"topic changed to : //" + topic + "//" <<PRINT_END;
		_channel_manager.set_channel_topic(channel_name, topic);
		
		std::set<int> clients_in_channel = _channel_manager.get_channel(channel_name).clients_fd;
		for (std::set<int>::iterator it = clients_in_channel.begin(); it != clients_in_channel.end(); it++)
		{
			Client curr_client = _channel_manager.get_client_manager().get_client(*it); //TODO : changer cette ligne avec push olivier qui eviter le getteur
			curr_client.write(RPL_TOPIC(user.get_nickname(), user.get_username(), channel_name, topic, "TOPIC"));
		}
	}

	return ;
}
