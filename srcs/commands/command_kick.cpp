
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include "IrcReplies.hpp"
#include <iostream>
#include <string>

void	command_kick(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	std::istringstream ss(args);
	std::string channel_name, nickname;

	if (!(ss >> channel_name >> nickname) || channel_name.empty() || nickname.empty())
	{
		client.write(ERR_NEEDMOREPARAMS(SERVER_NAME, "KICK"));
		return ;
	}

	if (is_kick_valid(_channel_manager, _user_manager, client, channel_name, nickname) == false)
		return ;

	if (DEBUG)
	{
		std::cout <<BCYN <<"CHANNEL: //" << channel_name + "//" << PRINT_END;
		std::cout <<BCYN <<"NICKNAME: //" << nickname + "//"<< PRINT_END;
	}

	handle_kick_command(_channel_manager, _user_manager, client, channel_name, nickname);

	// TODO : CODE INITIAL CARO
  /*if (DEBUG)
	{
		std::cout <<"----------------" <<std::endl;
		std::cout <<BRED <<"List of operators in channel " <<channel_name <<PRINT_END;
		_channel_manager.print_operators(channel_name, _user_manager);
		std::cout <<"----------------" <<std::endl;
	}

	if (_channel_manager.is_operator(kicked_user.get_fd(), channel_name) == false)
	{
		_channel_manager.leave_channel(kicked_user.get_fd(), channel_name);
		if (DEBUG)
		{
			std::cout <<BBLU <<"User to be kicked is not the channel operator" <<PRINT_END;
			std::cout <<BBLU <<"User has been kicked" <<PRINT_END;
			std::cout <<BBLU <<"List of clients in channel " <<channel_name <<PRINT_END;
			_channel_manager.print_all_clients(channel_name);
		}

		User user = _user_manager.get_user(client.get_fd());
		client.write(RPL_KICK(user.get_nickname(), user.get_username(), channel_name, nickname, "KICK")); //+ reason?

		//TODO karl : envoyer au kicked_user qu'il s'est fait viré
	}
	else
	{
		//TODO : RPL error message : cannot kick channel operator
		if (DEBUG)
			std::cout <<BRED <<"Cannot kick channel operator" <<PRINT_END;
	}
	*/
	return ;
}
