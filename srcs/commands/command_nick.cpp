#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include "IrcReplies.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>

void	command_nick(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{
	// TODO quand 2nd user change de nick, msg n'apparait pas
	// -> peut etre pas bon client avec le write

	// TODO KARL quand un user change de nick, envoie a tous ses channel + fenetre de base
	(void)_server_settings;
	(void)_channel_manager;
	(void)_client_manager;

	User	& user = _user_manager.get_user(client.get_fd());

	if (is_nickname_valid(args, _user_manager, user, client) == false)
		return ;

	if (DEBUG)
		std::cout << "old nickname = " <<user.get_nickname() <<std::endl;

	// TODO handle_nick_command
	///envoyer a tous les clients de tous les channels
	// std::map<std::string, Channel> channels = _channel_manager.get_all_channels();
	// std::map<std::string, Channel>::iterator channels_it;
	/* std::set<std::string> channels = _channel_manager.get_channels_for_users(client.get_fd());
	std::set<std::string>::iterator channels_it;
	// std::map<std::string, Channel> channels = _channel_manager.get_all_channels();
	// std::map<std::string, Channel>::iterator channels_it;
	for (channels_it = channels.begin(); channels_it != channels.end(); channels_it++)
	{
		Channel curr_channel = _channel_manager.get_channel(*channels_it);
		//std::cout <<BRED <<"Channel = " << channels_it->first <<PRINT_END; //TEST
		//_channel_manager.send_message_to_channel(0, channels_it->first, "test", _user_manager);

		// std::set<int> clients_in_channel = channels_it->second.clients_fd;
		std::set<int> clients_in_channel = curr_channel.clients_fd;
		std::set<int>::iterator clients_it;
		for (clients_it = clients_in_channel.begin(); clients_it != clients_in_channel.end(); clients_it++)
		{
			Client &curr_client = _client_manager.get_client(*clients_it);
			//std::cout <<BRED <<"Client fd = " <<curr_client.get_fd() <<PRINT_END; //TEST
			curr_client.write(NICK_CHANGED(user.get_nickname(), user.get_username(), args, "NICK"));
		}

		//_channel_manager.send_message_to_channel2(curr_channel.name, NICK_CHANGED(user.get_nickname(), user.get_username(), args, "NICK")); //TODO MODIFIER SEND_MSG_TI_CHANN POUR QU IL SOIT PLUS FLEXIBLE ET MARCHE POUR LES DEUX
		//client.write(NICK_CHANGED(user.get_nickname(), user.get_username(), args, "NICK"));

	} */

	//FIX KARL: msg ne doit pas etre bon car ne s'envoie pas dans les bonnes fenetres
	client.write(NICK_CHANGED(user.get_nickname(), user.get_username(), args, "NICK")); 
	user.set_nickname(args);

	if (DEBUG)
		std::cout << "new nickname = " <<user.get_nickname() <<std::endl;

	if (DEBUG)
	{
		std::cout <<"ALL USERS : " <<std::endl;
		_user_manager.print_all_users();
	}
}
