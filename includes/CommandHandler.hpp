#pragma once

#include <fcntl.h>
#include <string>
#include <vector>
#include "CommandMiddleware.hpp"
#include "UserManager.hpp"

class Client;
class ChannelManager;

typedef void (*command_function_t)(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
);

struct g_command_table_t
{
	const char *command;
	command_function_t function;
};


void command_ping(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	);
void command_join(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	);
void command_sendmsg(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	);

void command_auth(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	);

void command_nick(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	);

void command_info(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	);

const g_command_table_t g_command_table[] = {
	{"PING", command_ping},
	{"JOIN", command_join},
	{"SENDMSG", command_sendmsg},
	{"AUTH", command_auth},
	{"NICK", command_nick},
	{"INFO", command_info},
	{NULL, NULL}};

class CommandHandler
{
private:
	void _execute_command(
		Client &client,
		std::string const &command,
		std::string const &args
		);
	ChannelManager *_channel_manager;
	UserManager *_user_manager;

public:
	CommandHandler();
	~CommandHandler();

	void init(ChannelManager &channel_manager, UserManager &user_manager);
	void handle_command(Client &client,
		std::string const &msg);
	void on_connection(Client &client);
	void on_disconnection(Client &client);
};
