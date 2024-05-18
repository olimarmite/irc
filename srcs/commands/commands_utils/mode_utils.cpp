#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"
#include "../includes/User.hpp"
#include "../includes/UserManager.hpp"
#include "../includes/ChannelManager.hpp"
#include "../includes/Client.hpp"
#include "../includes/ClientManager.hpp"
#include "../includes/IrcReplies.hpp"

// TODO
// // peut etre faire un boolean is_channel_invite_only pour pas l'update une deuxieme fois
// void	update_channel_invite_only(char sign)
// {
// 	if (sign == '+')
// 	{
// 		std::cout << "invite only mode activated" << std::endl;
// 	}
// 	else if (sign == '-')
// 	{
// 		std::cout << "invite only mode deactivated" << std::endl;
// 	}
// 	return ;
// }

// void	update_topic_restricted_to_operators()
// {
// 	return ;
// }

// void	update_channel_key()
// {
// 	return ;
// }

// void	update_user_limit()
// {
// 	return ;
// }

// void	update_channel_operator()
// {
// 	return ;
// }

// bool	is_valid_mode(std::string const & modestring)
// {
// 	if (modestring.length() != 2)
// 		return false;

// 	if (modestring[0] != '+' && modestring[0] != '-')
// 		return false;
	
// 	if (
// 		modestring[1] != 'i' &&
// 		modestring[1] != 't' &&
// 		modestring[1] != 'k' &&
// 		modestring[1] != 'l' &&
// 		modestring[1] != 'o'
// 		)
// 		return false;
// 	return true;
// }

// void	update_mode(char sign, char mode)
// {
// 	if (mode == 'i')
// 		update_channel_invite_only(sign);
// 	else if (mode == 't')
// 		update_topic_restricted_to_operators();
// 	else if (mode == 'k')
// 		update_channel_key();
// 	else if (mode == 'l')
// 		update_user_limit();
// 	else if (mode == 'o')
// 		update_channel_operator();

// 	return ;
// }