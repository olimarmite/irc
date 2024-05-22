#include "ChannelManager.hpp"
#include "Client.hpp"
#include "IrcReplies.hpp"
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
	while (channel[i] != ' ' && channel[i])
		i++;
  
	std::string channel_name = channel.substr(0, i);
	return _channels[channel_name];
}

std::set<int>	ChannelManager::get_operators(std::string const & channel_name)
{
	Channel channel = get_channel(channel_name);
	return channel.operators;
}

std::set<std::string>	ChannelManager::get_channels_for_users(int client_fd)
{
	std::map<int, std::set<std::string> >::iterator it = _clientChannels.find(client_fd);
	if(it != _clientChannels.end())
		return it->second;
	return std::set<std::string>();
}

/* ClientManager	&ChannelManager::get_client_manager()
{
	return *_client_manager;
} */

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

void	ChannelManager::create_channel(std::string const & channel_name, std::string const & password, int const & client_fd)
{
	Channel	new_channel;

	if (DEBUG)
		std::cout << BCYN "pass = " << password << PRINT_END;

	new_channel.name = channel_name;
	new_channel.password = password;
	new_channel.topic = "";
	new_channel.is_invite_only = false;
	new_channel.is_topic_restricted_to_operators = false;
	new_channel.is_key_needed = false;
	new_channel.user_limit = 2000;
	new_channel.operators.insert(client_fd);

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
	set_channel_name(channel_name);
	_channels[channel_name].clients_fd.insert(client_fd);
	_clientChannels[client_fd].insert(channel_name);

	if (DEBUG)
		std::cout << "Number of clients in channel : " << _channels[channel_name].clients_fd.size() << std::endl;

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
			channel_name, message, "PRIVMSG"));
		}
	}
	return ;
}

void ChannelManager::send_message_to_channel2(std::string const &channel, std::string const &message)
{
	Channel &channel_obj = get_channel(channel);

	std::set<int>::iterator it = channel_obj.clients_fd.begin();
	while (it != channel_obj.clients_fd.end())
	{
		_client_manager->get_client(*it).write(message);
		it++;
	}
}


bool	ChannelManager::channel_exists(std::string const & channel_name)
{
	if (_channels.find(channel_name) != _channels.end())
	{
		if (DEBUG)
			std::cout << channel_name + " exists" << PRINT_END;
		return true;
	}
	return false;
}

bool	ChannelManager::is_operator(int client_fd, std::string channel_name)
{
	Channel channel = get_channel(channel_name);
	for (std::set<int>::iterator it = channel.operators.begin(); it != channel.operators.end(); it++)
	{
		if (*it == client_fd)
			return true;
	}
	return false;
}

/*	-----		Debug					-----	*/
void ChannelManager::print_all_channels()
{
	std::cout <<"List of channels" <<std::endl;
	std::map<std::string, Channel>::iterator it = _channels.begin();
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
	// std::set<int>::iterator it = channel.clients_fd.begin();

	std::cout << "Number of clients in " << channel_name << ": " << channel.clients_fd.size() << PRINT_END;

	// while (it != channel.clients_fd.end())
	// {
	// 	std::cout << " - " << *it << PRINT_END;
	// 	it++;
	// }
	return ;
}

void	ChannelManager::print_operators(std::string channel_name, UserManager user_manager)
{
	Channel channel = get_channel(channel_name);
	for (std::set<int>::iterator it = channel.operators.begin(); it != channel.operators.end(); it++)
	{
		Client client = _client_manager->get_client(*it);
		User user = user_manager.get_user(client.get_fd());

		std::cout <<"- " <<user.get_nickname() <<std::endl;
	}
}

std::map<std::string, Channel>	ChannelManager::get_all_channels()
{
	return _channels;
}
