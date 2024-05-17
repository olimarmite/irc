
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <string>

static std::string get_nickname(std::string const &args)
{
	std::string nickname;
	int i = 0;
	while (args[i] != ' ')
		i++;
	i++;
	while (args[i] != ' ')
	{
		nickname += args[i];
		i++;
	}
	return nickname;
}


void	command_kick(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	std::string channel_name = args.substr(0, args.find(" "));
	std::string nickname = get_nickname(args);
	std::string reason = args.substr(args.find(":") + 1);

	if (DEBUG)
	{
		std::cout <<BCYN <<"CHANNEL: //" << channel_name + "//" << PRINT_END;
		std::cout <<BCYN <<"NICKNAME: //" << nickname + "//"<< PRINT_END;
		std::cout <<BCYN <<"REASON: //" << reason + "//" << PRINT_END;
	}

	//check if user is in channel
	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == true) //if user is in channel
	{
		if (DEBUG)
			std::cout <<BBLU <<"User to be kicked is in channel" <<PRINT_END;

		User kicked_user = _user_manager.get_user_by_name(nickname);
		Client kicked_client = _channel_manager.get_client_manager().get_client(kicked_user.get_fd());
		if (kicked_user.get_is_operator() == false) //check if user is channel perator
		{
			_channel_manager.leave_channel(kicked_client.get_fd(), channel_name);
			if (DEBUG)
			{
				std::cout <<BBLU <<"User to be kicked is not the channel operator" <<PRINT_END;
				std::cout <<BBLU <<"User has been kicked" <<PRINT_END;
				std::cout <<BBLU <<"List of clients in channel " <<channel_name <<PRINT_END;
				_channel_manager.print_all_clients(channel_name);
			}

			User user = _user_manager.get_user(client.get_fd());
			client.write(RPL_KICK(user.get_nickname(), user.get_username(), channel_name, nickname)); //+ reason?
		}
		else
		{
			//TODO : RPL error message : cannot kick channel operator
			if (DEBUG)
				std::cout <<BRED <<"Cannot kick channel operator" <<PRINT_END;
		}
	}
	else
	{
		//error message : user not in channel
		if (DEBUG)
			std::cout <<BRED <<"User to be kicked is not in channel" <<PRINT_END;
	}
	
	return ;
}
