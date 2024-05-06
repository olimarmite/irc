
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
	std::cout << "Client disconnected: " << client_fd << std::endl;
	_channel_manager->leave_all_channels(client_fd);
	_clients.erase(client_fd);
	std::cout << "Client removed: " << client_fd << std::endl;
}

Client &ClientManager::get_client(int client_fd)
{
	return (_clients[client_fd]);
}

ClientManager::ClientManager() :
	_clients(),
	_channel_manager(NULL)
{
}

ClientManager::~ClientManager()
{

}

void ClientManager::init(ChannelManager &channel_manager, CommandHandler &command_handler)
{
	_channel_manager = &channel_manager;
	_command_handler = &command_handler;
}
