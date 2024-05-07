#include "ChannelManager.hpp"
#include "Client.hpp"
#include <iostream>
#include <map>
#include <string>


ChannelManager::ChannelManager() {}

ChannelManager::~ChannelManager() {}

void ChannelManager::join_channel(int client_fd, std::string const &channel)
{
	_channels[channel].clients_fd.insert(client_fd);
	_clientChannels[client_fd].insert(channel);
	std::cout << "Joined channel " << channel << std::endl;
	std::cout << "Channel size: " << _channels[channel].clients_fd.size() << std::endl;
	std::cout << client_fd << " Client size: " << _clientChannels[client_fd].size() << std::endl;
}

Channel &ChannelManager::get_channel(std::string const &channel)
{
	return _channels[channel];
}

void ChannelManager::send_message_to_channel(std::string const &channel, std::string const &message)
{
	Channel &channel_obj = get_channel(channel);

	std::set<int>::iterator it = channel_obj.clients_fd.begin();
	while (it != channel_obj.clients_fd.end())
	{
		_client_manager->get_client(*it).write(message);
		it++;
	}
}

void ChannelManager::init(ClientManager &client_manager)
{
	_client_manager = &client_manager;
}

void ChannelManager::leave_channel(int client_fd, std::string const &channel)
{
	Channel &channel_obj = get_channel(channel);

	std::cout << "Leaving channel " << channel << std::endl;
	channel_obj.clients_fd.erase(client_fd);

	_clientChannels[client_fd].erase(channel);
}

void ChannelManager::leave_all_channels(int client_fd)
{
	std::set<std::string> channels_set = _clientChannels[client_fd];
	std::cout << client_fd << " Client size: " << _clientChannels[client_fd].size() << std::endl;


	std::set<std::string>::iterator it = channels_set.begin();
	std::cout << "Leaving all channels" << std::endl;
	while (it != channels_set.end())
	{
		leave_channel(client_fd, *it);
		it++;
	}
}
