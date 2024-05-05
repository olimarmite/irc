#include "CommandHandler.hpp"
#include <iostream>
#include <string>

void	command_join(Server &server, Client &client, std::string const &args)
{
	(void)server;
	(void)args;
	server.get_channel_manager().join_channel(client, args);
}
