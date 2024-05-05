
#include <iostream>
#include "CommandMiddleware.hpp"

MiddlewareContinuation AuthMiddleware::handle_command(std::string &command, Client &client, Server &server) const
{
	(void)client;
	(void)server;

	if (client.getIsAuthanticated() == false)
	{
		if (command == "AUTH")
		{
			client.setIsAuthanticated(true);
		}
		else
		{
			std::cout << "Client is not authanticated" << std::endl;
			return STOP;
		}
	}

	return CONTINUE;
}
