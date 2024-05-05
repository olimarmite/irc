
#include <iostream>
#include "CommandMiddleware.hpp"

MiddlewareContinuation DebugMiddleware::handle_command(std::string &command, Client &client, Server &server) const
{
	(void)client;
	(void)server;
	std::cout << "CommandHandlerDebugMiddleware: " << command << std::endl;
	return CONTINUE;
}
