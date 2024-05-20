#include "Client.hpp"
#include "ChannelManager.hpp"
#include "IrcReplies.hpp"
#include "UserManager.hpp"
#include <string>

std::string parse_nickname(std::string args)
{
	int i = 0;
	while (args[i] != ' ')
		i++;
	return args.substr(0, i);
}

std::string parse_message(std::string args)
{
	int i = 0;
	while (args[i] != ' ')
		i++;
	while (args[i] != ':')
		i++;
	i++; //skip ':'
	return args.substr(i, args.length());
}

void	command_sendmsg(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	/*
		Par default /msg ecrit a un USER et non un channel
		ex: /msg test salut --> message privé pour le user test
		/msg #test salut --> message dans le channel test
		Si test existe en tant que channel et non en tant que
		user, si on écrit à test sans # alors irssi va ouvrir un
		chat privé avec un user test (qui n'existe pas).
	 */


	User origin_user = _user_manager.get_user(client.get_fd());

	std::string message = parse_message(args);

	if (args[0] != '#') //if private message
	{
		if (DEBUG)
		{
			std::cout <<"List of users" <<std::endl;
			_user_manager.print_all_users();
		}
		
		std::string nickname = parse_nickname(args);
		if (_user_manager.user_exists(nickname) == true)
		{
			if (DEBUG)
				std::cout <<BBLU <<"Nick/channel found" <<PRINT_END;

			User dest_user = _user_manager.get_user_by_name(nickname);
			Client dest_client = _channel_manager.get_client_manager().get_client(dest_user.get_fd());

			dest_client.write(MSG_RECEIVED(origin_user.get_nickname(), dest_user.get_username(), \
			dest_user.get_nickname(), message, "PRIVMSG"));
		}
		else
		{
			if (DEBUG)
				std::cout <<BRED <<"Nick/channel not found" <<PRINT_END;
			User origin_user = _user_manager.get_user(client.get_fd());
			client.write(ERR_NOSUCHNICK(SERVER_NAME, nickname));
			return ;
		}
	}
	else //message for channel
	{
		if (DEBUG)
			_channel_manager.print_all_channels();

		Channel channel = _channel_manager.get_channel(args);

		if (_channel_manager.channel_exists(channel.name) == false) //if channel n'existe pas alors le creer
			command_join(_channel_manager, _user_manager, client, args); //join le nouveau channel créé
		else
		{
			if (DEBUG)
				std::cout <<BBLU <<"Channel exists" <<PRINT_END;

			if (_channel_manager.is_user_in_channel(client.get_fd(), channel.name) == false) //if user n'est pas dans le channel
			{
				if (DEBUG)
					std::cout <<BCYN <<"User not in channel (was kicked out?)" <<PRINT_END;
				//TODO : RPL client not in channel
				return ;
			}
			if (DEBUG)
			{
				std::cout <<BCYN <<"User found in channel " <<channel.name <<PRINT_END;
				_channel_manager.print_all_clients(channel.name);
			}
			_channel_manager.send_message_to_channel(client.get_fd(), channel.name, args, _user_manager); //on envoie le msg dans le channel
		}
	}
}
