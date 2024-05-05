#pragma once
#include "Client.hpp"
#include <fcntl.h>
#include <string>
#include <vector>
#include "CommandMiddleware.hpp"

// class Client;
// class Server;


typedef void (*command_function_t)(
	Server &server,
	Client &client,
	std::string const &command
	);

struct g_command_table_t
{
	const char *command;
	command_function_t function;
};


void command_ping(Server &server, Client &client, std::string const &command);
void command_join(Server &server, Client &client, std::string const &command);
void command_sendmsg(Server &server, Client &client, std::string const &command);

const g_command_table_t g_command_table[] = {
	{"PING", command_ping},
	{"JOIN", command_join},
	{"SENDMSG", command_sendmsg},
	{NULL, NULL}};

class CommandHandler
{
private:
	MiddlewareContinuation _execute_middlewares(
		Server &server,
		Client &client,
		std::string const &command
		);
	void _execute_command(
		Server &server,
		Client &client,
		std::string const &command,
		std::string const &args
		);
	std::vector<ICommandHandlerMiddleware *> _middlewares;

public:
	CommandHandler();
	~CommandHandler();

	void handle_command(Server &server, Client &client,
		std::string const &msg);

	void add_middleware(ICommandHandlerMiddleware *middleware);
	void clear_middlewares();
};
