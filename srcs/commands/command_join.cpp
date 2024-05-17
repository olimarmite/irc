#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <string>




void	command_join(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	std::string const & channel_name = args;
	std::string const & password = "";

	if (_channel_manager.channel_exists(channel_name) == false)
		_channel_manager.create_channel(channel_name, password);

	_channel_manager.print_all_channels();

	if (_channel_manager.is_user_in_channel(client.get_fd(), channel_name) == false)
	{
		_channel_manager.join_channel(client.get_fd(), channel_name);

		User user = _user_manager.get_user(client.get_fd());
		client.write(JOINED_CHANNEL(user.get_nickname(), user.get_username(), channel_name));

		//_channel_manager.send_message_to_channel(client.get_fd(), channel_name, message); //HERE

//messages en dessosu pas necessaires
/* 		std::string nicknames;
		User users_it;
		std::set<int>	clients_in_chan = _channel_manager.get_channel(channel_name).clients_fd;

		for (std::set<int>::iterator it = clients_in_chan.begin(); it != clients_in_chan.end(); it++)
		{
			if (nicknames.length() > 0)
				nicknames = nicknames + std::string(" ");
			// std::set<int>::iterator next_it = it ++;
			// if (next_it == clients_in_chan.end()) //si avant-dernier
			// 	nicknames = nicknames + std::string("@"); //verifier si c'est bien le premier user a etre entré dans le chan (ou ca se trouve on s en fout ou ca se trouve le @ est le pour celui qui a les autorisations++ qu ipar default est celui qui a cree le chan)
			users_it = _user_manager.get_user(*it);
			std::cout <<BYEL <<"Client fd in chan : " <<users_it.get_fd() <<PRINT_END; //TEST
			std::cout <<BHGRN <<"User in chan : " + users_it.get_nickname() <<PRINT_END; //TEST
			nicknames = nicknames + users_it.get_nickname();
			std::cout <<BRED <<"nicknames = " + nicknames <<PRINT_END; //TEST
		}

		
		client.write(RPL_NAMREPLY(nicknames, channel_name));
		client.write(RPL_ENDOFNAMES(user.get_nickname(), channel_name)); */
	}
	
}
