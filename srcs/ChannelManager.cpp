#include "ChannelManager.hpp"
#include "Client.hpp"
#include <iostream>
#include <iterator>
#include <map>
#include <string>

ChannelManager::ChannelManager() {}

ChannelManager::~ChannelManager() {}

void ChannelManager::join_channel(Client &client, std::string const &channel)
{
	_channels[channel].clients[client.getFd()] = client;

}


Channel &ChannelManager::get_channel(std::string const &channel)
{
	return _channels[channel];
}

void ChannelManager::send_message_to_channel(Client &client, std::string const &channel, std::string const &message)
{
	Channel &channel_obj = get_channel(channel);

	std::map<int, Client>::iterator it = channel_obj.clients.begin();
	while (it != channel_obj.clients.end())
	{
		if (it->second.getFd() != client.getFd())
		{
			it->second.write(message);
		}
		it++;
	}
}
