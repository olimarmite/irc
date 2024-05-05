#include "CommandHandler.hpp"
#include <iostream>
#include <string>
#include "Server.hpp"

void	command_sendmsg(Server &server, Client &client, std::string const &args)
{
	(void)server;
	(void)args;
	server.get_channel_manager().send_message_to_channel(client, "default", args);
}
