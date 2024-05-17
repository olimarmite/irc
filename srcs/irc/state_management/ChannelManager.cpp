#include "ChannelManager.hpp"
#include "Client.hpp"
#include <iostream>
#include <map>
#include <string>

/*	-----	Constructors & Destructors	-----	*/

ChannelManager::ChannelManager()
{
	return ;
}

ChannelManager::~ChannelManager()
{
	return ;
}

/*	-----		Getters & Setters		-----	*/

Channel	&ChannelManager::get_channel(std::string const &channel)
{
	int i = 0;
	while (channel[i] != ' ')
		i++;
	return _channels[channel.substr(0, i)];
}

void	ChannelManager::set_channel_name(std::string const & channel_name)
{
	_channels[channel_name].name = channel_name;
	return ;
}

void	ChannelManager::set_channel_topic(std::string const & channel_name, std::string const & channel_topic)
{
	_channels[channel_name].topic = channel_topic;
	return ;
}

/*	-----		Methods					-----	*/

void	ChannelManager::init(ClientManager &client_manager)
{
	_client_manager = &client_manager;
	return ;
}

void	ChannelManager::leave_channel(int client_fd, std::string const &channel)
{
	//HERE: cette fonction ne semble pas bien effacer les clients des channels 
	//cf. command send_msg qui check si le client est dans le channel

	Channel &channel_obj = get_channel(channel);
	channel_obj.clients_fd.erase(client_fd);

	_clientChannels[client_fd].erase(channel);

	return ;
}

void	ChannelManager::leave_all_channels(int client_fd)
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
	return ;
}

void	ChannelManager::create_channel(std::string const & channel_name, std::string const & password)
{
	Channel	new_channel;

	new_channel.name = channel_name;
	new_channel.password = password;
	_channels[channel_name] = new_channel;

	if (DEBUG)
		std::cout << "Created channel: " + channel_name << PRINT_END;

	return ;
}

bool	ChannelManager::is_user_in_channel(int client_fd, std::string const & channel_name)
{
	Channel	& channel = _channels[channel_name];

	if (channel.clients_fd.find(client_fd) != channel.clients_fd.end())
		return true;

	if (DEBUG)
		std::cout << "Didn't find user in " + channel_name << PRINT_END;
	return false;
}

void	ChannelManager::join_channel(int client_fd, std::string const & channel_name)
{

	std::cout << "channel name = " + channel_name << PRINT_END;
	
	set_channel_name(channel_name);
	_channels[channel_name].clients_fd.insert(client_fd);
	_clientChannels[client_fd].insert(channel_name);

	if (DEBUG)
	{
		std::cout << "Joined channel " << channel_name << std::endl;
		std::cout << "Channel size: " << _channels[channel_name].clients_fd.size() << std::endl;
		std::cout << client_fd << " Client size: " << _clientChannels[client_fd].size() << std::endl;
	}

	return ;
}

void	ChannelManager::send_message_to_channel(int client_fd, std::string const & channel_name, std::string const & message, UserManager &_user_manager)
{
	Channel	& channel = _channels[channel_name];
	std::set<int>::iterator it = channel.clients_fd.begin();

	for (; it != channel.clients_fd.end(); it++)
	{
		if (*it != client_fd)
		{
			Client dest_client = _client_manager->get_client(*it);
			User dest_user = _user_manager.get_user(dest_client.get_fd());
			User origin_user = _user_manager.get_user(client_fd);
			
			dest_client.write(MSG_RECEIVED(origin_user.get_nickname(), dest_user.get_username(), \
			channel_name, message));
		}
	}
	return ;
}

bool	ChannelManager::channel_exists(std::string const & channel_name)
{
	if (_channels.find(channel_name) != _channels.end())
		return true;

	if (DEBUG)
		std::cout << channel_name + " does not exist, it will be created" << PRINT_END;
	return false;
}


////////debug
void ChannelManager::print_all_channels()
{
	std::map<std::string, Channel>::iterator it = _channels.begin();
	std::cout << "Number of channels: " << _channels.size() << PRINT_END;

	while (it != _channels.end())
	{
		std::cout << " - " << it->second.name << PRINT_END;
		it++;
	}
	return ;
}

void ChannelManager::print_all_clients(std::string channel_name)
{
	Channel &channel = _channels[channel_name];
	std::set<int>::iterator it = channel.clients_fd.begin();

	std::cout << "Number of clients in " << channel_name << ": " << channel.clients_fd.size() << PRINT_END;

	while (it != channel.clients_fd.end())
	{
		std::cout << " - " << *it << PRINT_END;
		it++;
	}
	return ;
}

ClientManager &ChannelManager::get_client_manager()
{
	return *_client_manager;
}
