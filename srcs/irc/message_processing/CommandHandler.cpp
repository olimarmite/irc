#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "Macros.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <string>
#include "IrcReplies.hpp"

bool _is_authenticated(Client &client, UserManager &user_manager)
{
	User user =	user_manager.get_user(client.get_fd());

	return (user.get_is_authenticated() && user.get_nickname().empty() == false);
}

void CommandHandler::_execute_command(Client &client,
	const std::string &command, const std::string &args)
{
	//TODO: do a better auth command control (maybe a flag in the cammand table)

	// if (_is_authenticated(client, *_user_manager) == false)
	// {
	// 	if (command != "NICK" && command != "USER" && command != "PASS")
	// 	{
	// 		client.write(ERR_NOTREGISTERED(SERVER_NAME));
	// 		return ;
	// 	}
	// }

	if (DEBUG)
		std::cout << "Command: " << command << " | Args: " << args << std::endl;
	for (int i = 0; g_command_table[i].command; i++)
	{
		//if (g_command_table[i].command == "PASS")
			//check correct password ( _password)
			//if not on close le client
		if (g_command_table[i].command == command)
		{
			g_command_table[i].function(*_channel_manager, *_user_manager, *_client_manager, *_settings, client, args);
			if (DEBUG)
				std::cout << "Command " << command << " executed" << std::endl;
			return ;
		}
	}
	// client.write("ERROR: Unknown command\n");
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


void CommandHandler::init(ChannelManager &channel_manager, UserManager &user_manager, ClientManager &client_manager, const ServerSettings &settings)
{
	_channel_manager = &channel_manager;
	_user_manager = &user_manager;
	_client_manager = &client_manager;
	_settings = &settings;
}

void CommandHandler::on_connection(Client &client)
{
	// User &user = _user_manager->get_user(client.get_fd());

	_user_manager->add_user(client.get_fd());
	// client.write(WELCOME_MESSAGE(user.get_username())); //APRÈS SET USERNAME ET NICKNAME SINON PAS CORRECT! //HERE
}

void CommandHandler::on_disconnection(Client &client)
{
	_channel_manager->leave_all_channels(client.get_fd());
	_user_manager->remove_user(client.get_fd());
}
