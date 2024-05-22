#include "Client.hpp"
#include "ChannelManager.hpp"
#include "IrcReplies.hpp"
#include "UserManager.hpp"
#include <string>

// TODO KARL

std::string parse_nickname(std::string args)
{
	// code -- karl
	// std::istringstream	ss(args);
	// std::string			nickname;
	// std::getline(ss, nickname, ' ');

	// return nickname;
	// --- fin

	// --> code initial
	int i = 0;
	while (args[i] != ' ')
		i++;
	return args.substr(0, i);
}

std::string parse_message(std::string args)
{
	// -- code karl
	// std::istringstream	ss(args);
	// std::string			to_throw, message;
	// std::getline(ss, to_throw, ' ');
	// std::getline(ss, to_throw, ':');
	// std::getline(ss, message);

	// return message;
	// -- fin

	// -->code initial
	int i = 0;
	while (args[i] != ' ')
		i++;
	while (args[i] != ':')
		i++;
	i++; //skip ':'
	return args.substr(i, args.length());
}

// bool	is_it_private_message(std::string args)
// {
// 	if (args[0] != '#')
// 		return true;
// 	return false;
// }

// void	handle_private_message(UserManager &_user_manager, ClientManager &_client_manager, Client &client, std::string args)
// {
// 	std::string nickname = parse_nickname(args);
// 	std::string message = parse_message(args);

// 	if (_user_manager.user_exists(nickname) == true)
// 	{
// 		User dest_user = _user_manager.get_user_by_name(nickname);
// 		Client dest_client = _client_manager.get_client(dest_user.get_fd());

// 		dest_client.write(MSG_RECEIVED(origin_user.get_nickname(), dest_user.get_username(), \
// 		dest_user.get_nickname(), message, "PRIVMSG"));
// 	}
// 	else
// 	{
// 		User origin_user = _user_manager.get_user(client.get_fd());
// 		client.write(ERR_NOSUCHNICK(SERVER_NAME, nickname));
// 		return ;
// 	}
// }

// void	handle_channel_message(ChannelManager &_channel_manager, UserManager &_user_manager, ClientManager &_client_manager, Client &client, std::string args)
// {
// 	Channel channel = _channel_manager.get_channel(args);

// 	if (_channel_manager.channel_exists(channel.name) == false) //if channel n'existe pas alors le creer
// 	{
// 		//command_join(_channel_manager, _user_manager, client, args); //join le nouveau channel créé
// 		command_join(_channel_manager, _user_manager, _client_manager, _server_settings, client, args); //join le nouveau channel créé
// 	}
// 	else
// 	{
// 		if (_channel_manager.is_user_in_channel(client.get_fd(), channel.name) == false) //if user n'est pas dans le channel
// 		{
// 			//TODO : RPL client not in channel
// 			return ;
// 		}
// 		_channel_manager.send_message_to_channel(client.get_fd(), channel.name, message, _user_manager); //on envoie le msg dans le channel
// 	}
// }


void	command_sendmsg(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	//FIX CARO quand un user ecrit dans un channel, ca montre le username a la place du nickname
	// pour sa propre fenetre de chat
	// le nickname est indique dans la barre bleue en bas a gauche

	/*
		Par default /msg ecrit a un USER et non un channel
		ex: /msg test salut --> message privé pour le user test
		/msg #test salut --> message dans le channel test
		Si test existe en tant que channel et non en tant que
		user, si on écrit à test sans # alors irssi va ouvrir un
		chat privé avec un user test (qui n'existe pas).
	 */

	
	(void)_client_manager;
	(void)_server_settings;

	User origin_user = _user_manager.get_user(client.get_fd());
	std::string message = parse_message(args);
	if (DEBUG)
		std::cout <<BRED <<"MESSAGE = " + message <<PRINT_END;//TEST

	// ---------- CODE KARL ------
	/*
	std::istringstream	ss(args);
	std::string			message, nickname;


	std::string message = parse_message(args);
	std::cout <<BRED <<"MESSAGE = " + message <<PRINT_END;//TEST

	if (is_it_private_message(args) == true)
		handle_private_message(_user_manager, _client_manager, client, args);
	
	else
		handle_channel_message(_channel_manager, _user_manager, _client_manager, client, args);
	return ;
	*/
	//----- FIN CODE KARL -------

	
	
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
			Client dest_client = _client_manager.get_client(dest_user.get_fd());

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
		{
			if (DEBUG)
				std::cout <<BBLU <<"Channel doesn't exist : creation of new channel" <<PRINT_END;
			//command_join(_channel_manager, _user_manager, client, args); //join le nouveau channel créé
			command_join(_channel_manager, _user_manager, _client_manager, _server_settings, client, args); //join le nouveau channel créé

		}
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
			_channel_manager.send_message_to_channel(client.get_fd(), channel.name, message, _user_manager); //on envoie le msg dans le channel
		}
	}
}
