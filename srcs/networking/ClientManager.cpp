
#include "ClientManager.hpp"
#include <sys/epoll.h>
#include "ChannelManager.hpp"

void ClientManager::add_client(int client_fd)
{
	(void)client_fd;
	_clients[client_fd].init(client_fd, *_command_handler);
}

void ClientManager::remove_client(int client_fd)
{
	_clients[client_fd].disconnect();
	_clients.erase(client_fd);
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
