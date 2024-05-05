#pragma once
#include "Client.hpp"
#include "Server.hpp"
#include <fcntl.h>
#include <string>

// class Client;
// class Server;


typedef void (*command_function_t)(Server &server, Client &client, std::string const &command);

typedef struct
{
	const char *command;
	command_function_t function;
} g_command_table_t;


void command_ping(Server &server, Client &client, std::string const &command);

const g_command_table_t g_command_table[] = {
	{"PING", command_ping},
	{NULL, NULL}};

class CommandHandler
{
  private:
	static void _execute_command(Server &server, Client &client, std::string const &command, std::string const &args);
  public:
	static void handleCommand(Server &server, Client &client,
		std::string const &msg);
};
