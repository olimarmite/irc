


#include "Client.hpp"
#include <iostream>

enum MiddlewareContinuation
{
	CONTINUE,
	STOP
};

class ICommandHandlerMiddleware
{
	public:
		virtual MiddlewareContinuation handle_command(std::string &command, Client &client, Server &server) const = 0;
		virtual ~ICommandHandlerMiddleware() {}
};


class DebugMiddleware : public ICommandHandlerMiddleware
{
	public:
		MiddlewareContinuation handle_command(std::string &command, Client &client, Server &server) const;

};

class AuthMiddleware : public ICommandHandlerMiddleware
{
	public:
		MiddlewareContinuation handle_command(std::string &command, Client &client, Server &server) const;

};
