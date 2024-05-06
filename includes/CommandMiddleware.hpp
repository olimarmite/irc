


#include <iostream>


class Client;
class ClientManager;

enum MiddlewareContinuation
{
	CONTINUE,
	STOP
};

class ICommandHandlerMiddleware
{
	public:
		virtual MiddlewareContinuation handle_command(std::string &command, Client &client) const = 0;
		virtual ~ICommandHandlerMiddleware() {}
};


class DebugMiddleware : public ICommandHandlerMiddleware
{
	public:
		MiddlewareContinuation handle_command(std::string &command, Client &client) const;

};

class AuthMiddleware : public ICommandHandlerMiddleware
{
	public:
		MiddlewareContinuation handle_command(std::string &command, Client &client) const;

};
