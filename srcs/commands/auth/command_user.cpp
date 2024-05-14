#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#include "CommandHandler.hpp"
#include "Server.hpp"
#include "UserManager.hpp"
#include <iostream>
#include <string>
#include "IrcMessage.hpp"


// https://datatracker.ietf.org/doc/html/rfc1459#section-4.1.3

	// client.write(IrcMessage::ERR_NICKNAMEINUSE(_user_manager.get_user(client.get_fd()).get_nickname()).get_full_message("bob", ":ircserv"));

void	command_user(
	ChannelManager &_channel_manager,
	UserManager &_user_manager,
	Client &client,
	std::string const &args
	)
{
	(void)_channel_manager;
	(void)args;
	(void)_user_manager;


	User &user = _user_manager.get_user(client.get_fd());

	user.set_username(args);
	// client.write(nickname + " has been invited to channel " + channel_name + "\n"); // check dalnet

	// std::string const & response = IrcMessage::RPL_WELCOME(user.get_nickname()).get_full_message("bob", ":ircserv");

	// std::string const & response = IrcMessage::ERR_NEEDMOREPARAMS()


	return ;
}
