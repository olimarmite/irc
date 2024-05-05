#include "CommandHandler.hpp"
#include <iostream>
#include <iterator>
#include <string>


void CommandHandler::_execute_command(Server &server, Client &client,
	const std::string &command, const std::string &args)
{
	std::cout << "Command: " << command << " Args: " << args << std::endl;
	for (int i = 0; g_command_table[i].command; i++)
	{
		if (g_command_table[i].command == command)
		{
			g_command_table[i].function(server, client, args);
			return ;
		}
	}
	client.write("ERROR: Unknown command\n");
}

void CommandHandler::handle_command(Server &server, Client &client,
	const std::string &msg)
{
	size_t	pos;
	std::string args;
	std::string command;
	std::string msg_copy = msg;

	for (std::vector<ICommandHandlerMiddleware *>::iterator it = _middlewares.begin(); it != _middlewares.end(); it++)
	{
		if ((*it)->handle_command(msg_copy, client, server) == STOP)
		{
			return ;
		}
	}

	pos = msg_copy.find(' ');
	if (pos != std::string::npos)
	{
		command = msg_copy.substr(0, pos);
		args = msg_copy.substr(pos + 1);
	}
	else
	{
		command = msg_copy;
	}
	CommandHandler::_execute_command(server, client, command, args);
}

CommandHandler::CommandHandler() : _middlewares()
{
}

CommandHandler::~CommandHandler()
{
}

void CommandHandler::clear_middlewares()
{
	for (std::vector<ICommandHandlerMiddleware *>::iterator it = _middlewares.begin(); it != _middlewares.end(); it++)
	{
		delete *it;
	}
	_middlewares.clear();
}

void CommandHandler::add_middleware(ICommandHandlerMiddleware *middleware)
{
	_middlewares.push_back(middleware);
}
