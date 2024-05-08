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
	//TODO: il faut envoyer message privé à IRSSI pour qu'il ouvre un chat de channel

	Channel &channel_obj = get_channel(channel);

	std::set<int>::iterator it = channel_obj.clients_fd.begin();
	while (it != channel_obj.clients_fd.end())
	{
		_client_manager->get_client(*it).write(message);
		it++;
	}
}

void ChannelManager::send_message_to_client(std::string origin_nickname, \
std::string origin_username, std::string dest_nickname, Client dest_client, \
Client origin_client, std::string const &message)
{
	std::cout <<BHMAG <<"DANS SEND MSG TO CLIENT FONCTION" <<PRINT_END;

	//:caro123!~casomarr@5cfe-3e61-45ea-bc48-51f0.210.62.ip PRIVMSG karl123 :salut toi
	
	//faire une macro
	std::string to_send = ":" + origin_nickname + "!~" + \
	origin_username + "@127.0.0.1 PRIVMSG " + dest_nickname + \
	" :" + message;

	//VU LE RAWLOG DE KARL.LOG ET LELA.LOG AUCUN NE RECOIT TO_SEND C EST POUR CA QUE CA
	//MARCHE PAS

	(void)origin_client;
	std::cout <<BHMAG <<"origin_client fd = " <<origin_client.get_fd() <<PRINT_END;
	std::cout <<BHMAG <<"dest_client fd = " <<dest_client.get_fd() <<PRINT_END;
	dest_client.write(message);
	send(dest_client.get_fd(), to_send.c_str(), to_send.length(), 0);
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

bool	ChannelManager::channel_exists(std::string const & channel_name)
{
	if (_channels.find(channel_name) != _channels.end())
		return true;
	return false;
}

//test function
void	ChannelManager::print_all_channels()
{
	std::map<std::string, Channel>::iterator it = _channels.begin();
	while (it != _channels.end())
	{
		std::cout << " - " <<it->second.name <<std::endl;
		it++;
	}
}

ClientManager &ChannelManager::get_client_manager()
{
	return *_client_manager;
}
