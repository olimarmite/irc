#include "Client.hpp"
#include "ChannelManager.hpp"
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
	ClientManager &_client_manager,
	const ServerSettings &_settings,
	Client &client,
	std::string const &args
	)
{
	(void)_client_manager;
	(void)_settings;

	/*
		Par default /msg ecrit a un USER et non un channel
		ex: /msg test salut --> message privé pour le user test
		/msg #test salut --> message dans le channel test
		Si test existe en tant que channel et non en tant que
		user, si on écrit à test sans # alors irssi va ouvrir un
		chat privé avec un user test (qui n'existe pas).
	 */

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

			User origin_user = _user_manager.get_user(client.get_fd());

			std::string message = parse_message(args);

			dest_client.write(MSG_RECEIVED(origin_user.get_nickname(), dest_user.get_username(), \
			dest_user.get_nickname(), message));
		}
		else
		{
			if (DEBUG)
				std::cout <<BRED <<"Nick/channel not found" <<PRINT_END;
			User origin_user = _user_manager.get_user(client.get_fd());
			client.write(UNKNOWN_NICK_CHAN(origin_user.get_nickname(), nickname));
			return ;
		}
	}
	else //message for channel
	{
		if (DEBUG)
		{
			std::cout <<"List of channels" <<std::endl;
			_channel_manager.print_all_channels();
		}

		Channel channel = _channel_manager.get_channel(args);

		if (DEBUG)
			std::cout <<BCYN <<"channel name returned: " <<channel.name <<PRINT_END;

		if (_channel_manager.channel_exists(channel.name) == false) //if channel n'existe pas alors le creer
		{
			command_join(_channel_manager, _user_manager, _client_manager, _settings, client, args); //join le nouveau channel créé
		}
		// KARL HERE -> IL MANQUE JUSTE LE FD EN PREMIER ARGUMENT
		// _channel_manager.send_message_to_channel(channel.name, args); //on envoie le msg dans le channel
	}



//CODE CI-DESSOUS : QD ON CREAIT CHANNEL POUR MESSAGES PRIVÉS

/* 	Channel channel = _channel_manager.get_channel(args);

	if (_channel_manager.channel_exists(channel.name) == false) //if channel n'existe pas alors le creer
	{
		command_join(_channel_manager, _user_manager, client, args); //join le nouveau channel créé

		if (args[0] != '#') //if private message
		{
			if (_user_manager.user_exists(args) == true) //join aussi le user du meme nom que le channel dedans
			{
				User user = _user_manager.get_user_by_name(args);
				//get client thanks to user_fd
				Client dest_client = _channel_manager.get_client_manager().get_client(user.get_fd());
				command_join(_channel_manager, _user_manager, dest_client, args);
			}
		}
	}

	//IMPORTANT : puisque j'ai effacé la fonction send_message_to_user je ne pense pas avoir besoin
	//de send_message_to_channel(), juste du bon message protocolaire
	_channel_manager.send_message_to_channel(channel.name, args); //on envoie le msg dans le channel (privé ou pas) */
}
