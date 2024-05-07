#include "Server.hpp"
#include "utils.hpp"
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include "UserManager.hpp"

/*
	Pour tester si port est libre :
		ss -tuln | grep <port>
	--> si ne renvoie rien c'est bon

	SERVER :
	./ircserv <port> <password>

	USER avec netcast :
	nc -C localhost <port>
	--> -C pour \r\n
	Puis je tapes "PASS <password>" sans qu'on me le demande
	(je ne recevrai pas de prompt type "Enter password :").

	USER avec irssi :
	/connect localhost <port> <password>

	Il faut que ca marche avec irssi, pas juste netcat
	(sytaxe particuliere type welcome_msg sans lequel
	ca ne permet pas de se connecter).

	irssi
	/rawlog open fichier.log

	!!Bien penser à fermer irssi et netcat avant de
	ctrl + C le serveur.

	Pou voir ce que IRSSI et netcat envoient au serveur :
	Lancer le serveur sur le port 1510
	Lancer sur un autre terminal : ./socat -v TCP-LISTEN:1237 TCP:localhost:1510
	Connecter le User au port 1237
*/


int main(int argc, char **argv)
{
	if (is_arg_valid(argc, argv) == false)
		return EXIT_FAILURE;

	//TODO: signals handler (check what signals)

	int port = atoi(argv[1]); //TODO: use more safe function
	std::string	password = argv[2];

	try
	{

		Server	server(port, password);
		ChannelManager channel_manager = ChannelManager();
		ClientManager client_manager = ClientManager();
		CommandHandler command_handler = CommandHandler();
		UserManager user_manager = UserManager();

		client_manager.init(command_handler);
		channel_manager.init(client_manager);
		command_handler.init(channel_manager, user_manager);
		server.init(client_manager);


		while (true)
		{
			server.run();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return EXIT_SUCCESS;
}
