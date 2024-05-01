#include "../includes/Server.hpp"
#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"

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
*/

int main(int argc, char **argv)
{
	if (is_arg_valid(argc, argv) == false)
		return EXIT_FAILURE;

	//TODO: signals handler (check what signals)

	std::string	port = argv[1];
	std::string	password = argv[2];

	try
	{
		Server	server(port, password);

		server.launch();
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