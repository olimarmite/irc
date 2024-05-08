#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <string>


bool _is_authenticated(Client &client, UserManager &user_manager)
{
	User user =	user_manager.get_user(client.get_fd());

	return (user.get_is_authenticated() && user.get_nickname().empty() == false);
}

void CommandHandler::_execute_command(Client &client,
	const std::string &command, const std::string &args)
{
	//TODO: do a better auth command control (maybe a flag in the cammand table)

	if (DEBUG)
		std::cout << "check auth --> " << _is_authenticated(client, *_user_manager) << PRINT_END;

	// if (_is_authenticated(client, *_user_manager) == false)
	// {
	// 	if (command != "AUTH" && command != "NICK")
	// 	{
	// 		client.write("ERROR: You must authenticate first\n");
	// 		return ;
	// 	}
	// }

	std::cout << "Command: " << command << " Args: " << args << std::endl;
	for (int i = 0; g_command_table[i].command; i++)
	{
		//if (g_command_table[i].command == "PASS")
			//check correct password ( _password)
			//if not on close le client
		if (g_command_table[i].command == command)
		{
			std::cout << "in execute command. Command: " << command <<std::endl;
			g_command_table[i].function(*_channel_manager, *_user_manager, client, args);
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

	if (DEBUG)
		std::cout << BYEL << msg << PRINT_END;

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


void CommandHandler::init(ChannelManager &channel_manager, UserManager &user_manager)
{
	_channel_manager = &channel_manager;
	_user_manager = &user_manager;
}

void CommandHandler::on_connection(Client &client)
{
	User &user = _user_manager->get_user(client.get_fd());
	client.write(WELCOME_MESSAGE(user.get_username()));

	_user_manager->add_user(client.get_fd());
}

void CommandHandler::on_disconnection(Client &client)
{
	_channel_manager->leave_all_channels(client.get_fd());
	_user_manager->remove_user(client.get_fd());
}
