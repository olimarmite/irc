#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <sstream>
#include <string>

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

void	command_user( //ne doit être accessible que à la connection
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;

	//TODO utiliser bool authentified pour ne pouvoir
	//entrer dans cette fonction qu'une fois


	User &user = _user_manager.get_user(client.get_fd());

	std::string username = args.substr(0, args.find(' '));
	user.set_username(username);
	// client.write(nickname + " has been invited to channel " + channel_name + "\n"); // check dalnet

	client.write(WELCOME_MESSAGE(user.get_username())); 
	
	return ;
}