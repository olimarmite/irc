#pragma once

#include <fcntl.h>
#include <string>
#include <vector>
#include "CommandMiddleware.hpp"

class Client;
class ChannelManager;

typedef void (*command_function_t)(
	ChannelManager &_channel_manager,
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
	Client &client,
	std::string const &args
	);
void command_join(
	ChannelManager &_channel_manager,
	Client &client,
	std::string const &args
	);
void command_sendmsg(
	ChannelManager &_channel_manager,
	Client &client,
	std::string const &args
	);

const g_command_table_t g_command_table[] = {
	{"PING", command_ping},
	{"JOIN", command_join},
	{"SENDMSG", command_sendmsg},
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

public:
	CommandHandler();
	~CommandHandler();

	void init(ChannelManager &channel_manager);
	void handle_command(Client &client,
		std::string const &msg);
};
