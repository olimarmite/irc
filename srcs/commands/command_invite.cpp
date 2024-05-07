
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <sstream>
#include <string>


//HERE creer command_user.cpp, pass.cpp

void	command_invite(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;

	std::string	channel_name, nickname;
	
	std::istringstream iss(args);

	if (!(iss >> channel_name >> nickname) || channel_name.empty() || nickname.empty())
	{
		client.write("Invalid arguments\n");
		return ;
	}
	
	if (_channel_manager.channel_exists(channel_name) == false)
	{
		client.write("Channel " + channel_name + " does not exist.\n");
		return ;
	}


	
	
	int	user_fd = 0;

	Channel &channel = _channel_manager.get_channel(channel_name);
	User &user_to_invite = _user_manager.get_user(user_fd);

	nickname = user_to_invite.get_nickname();

	channel.clients_fd.insert(user_to_invite.get_fd());
	client.write(nickname + " has been invited to channel " + channel_name + "\n"); // check dalnet
	
	//TODO ? or not ?
	//RFC --> <client><nick><channel>

	return ;
}

// TODO trouver moyen de recuperer _password du serveur
// void	command_pass(
// 	ChannelManager &_channel_manager,
// 	UserManager &_user_manager,
// 	Client &client,
// 	std::string const &args
// 	)
// {
// 	(void)_channel_manager;
// 	(void)args;
// 	(void)_user_manager;

// 	std::string	entered_password = args; // TODO parsing args mdp
//     if (entered_password != _password)
//     {
//         message = "Invalid password : connection to server refused\r\n";
//         int bytes_sent = send(user_fd, message.c_str(), message.length(), MSG_NOSIGNAL); //le proteger
//         if (bytes_sent == INVALID_NB)
//             throw std::runtime_error(ERROR_SEND);
//         close (user_fd);
//         throw std::runtime_error(ERROR_PASSW);
//     }
// 	return ;
// }

void	command_user(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;


	User &user = _user_manager.get_user(client.get_fd());

	user.set_username(args);
	// client.write(nickname + " has been invited to channel " + channel_name + "\n"); // check dalnet
	return ;
}
