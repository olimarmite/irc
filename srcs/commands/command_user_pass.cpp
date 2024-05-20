#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "User.hpp"
#include "IrcReplies.hpp"
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
	// (void)_client_manager;
	// (void)_server_settings;


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
	ClientManager &_client_manager,
	const ServerSettings &_server_settings,
	Client &client,
	std::string const &args
	)
{

/* 	IMPORTANT : j'ai mis les parties de code concernant authentification = true
	en commentaire parce que quand on écrit /user ça interprète la commande
	"userhost" et non "user" donc je crois que c'est de toutes façons pas
	possible d'entrer dans cette fonction plus d'une fois (lors de la connection) */

/* 	if (_user_manager.get_user(client.get_fd()).get_is_authenticated() == true)
	{
		if (DEBUG)
			std::cout <<BRED <<"User cmd is invalid : user is already authentified" <<PRINT_END;
		client.write(ALREADY_REGISTRED());
	} */

	(void)_channel_manager;
	(void)args;
	(void)_user_manager;
	(void)_client_manager;
	(void)_server_settings;


	User &user = _user_manager.get_user(client.get_fd());

	std::string username = args.substr(0, args.find(' '));
	user.set_username(username);

/* 	user.set_is_authenticated(true);
	if (DEBUG)
		std::cout <<BHGRN <<"User authentification set to true" <<PRINT_END;
 */
	client.write(WELCOME_MESSAGE(user.get_username()));

	return ;
}
