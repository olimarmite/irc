
#include "ClientManager.hpp"
#include <iostream>
#include <ostream>
#include <sys/epoll.h>
#include "ChannelManager.hpp"
#include "Macros.hpp"

void ClientManager::add_client(int client_fd)
{
	(void)client_fd;
	_clients[client_fd].init(client_fd, *_command_handler);
}

void ClientManager::remove_client(int client_fd)
{
	_clients.erase(client_fd);
}

void ClientManager::disconnect_all_clients()
{
	std::map<int, Client>::iterator it = _clients.begin();


	while (it != _clients.end())
	{
		it->second.disconnect();
		++it;
	}
	destroy_unused_clients();
}

Client &ClientManager::get_client(int client_fd)
{
	return (_clients[client_fd]);
}

ClientManager::ClientManager() :
	_clients()
{
}

ClientManager::~ClientManager()
{
}

void ClientManager::init(CommandHandler &command_handler)
{
	_command_handler = &command_handler;
}

void ClientManager::destroy_unused_clients()
{
	std::map<int, Client>::iterator it = _clients.begin();


	while (it != _clients.end())
	{
		if (it->second.get_fd() == INVALID_FD)
			_clients.erase(it++);
		else
			++it;
	}	
}