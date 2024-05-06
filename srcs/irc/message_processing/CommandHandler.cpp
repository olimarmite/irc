#include "CommandHandler.hpp"
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include <iostream>
#include <string>


void CommandHandler::_execute_command(Client &client,
	const std::string &command, const std::string &args)
{
	std::cout << "Command: " << command << " Args: " << args << std::endl;
	for (int i = 0; g_command_table[i].command; i++)
	{
		if (g_command_table[i].command == command)
		{
			g_command_table[i].function(*_channel_manager, client, args);
			std::cout << "Command " << command << " executed" << std::endl;
			return ;
		}
	}
	client.write("ERROR: Unknown command\n");
}

void CommandHandler::handle_command(Client &client,
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
	CommandHandler::_execute_command(client, command, args);
}

CommandHandler::CommandHandler()
{
}

CommandHandler::~CommandHandler()
{
}


void CommandHandler::init(ChannelManager &channel_manager)
{
	_channel_manager = &channel_manager;
}
