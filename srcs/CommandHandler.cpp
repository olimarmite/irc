#include "CommandHandler.hpp"
#include <iostream>
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
	pos = msg.find(' ');
	if (pos != std::string::npos)
	{
		command = msg.substr(0, pos);
		args = msg.substr(pos + 1);
	}
	else
	{
		command = msg;
	}
	CommandHandler::_execute_command(server, client, command, args);
}
