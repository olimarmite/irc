#include "CommandHandler.hpp"
#include <iostream>
#include <string>


void	command_ping(Server &server, Client &client, std::string const &args)
{
	(void)server;
	(void)args;
	client.write("PONG !\n");
}
