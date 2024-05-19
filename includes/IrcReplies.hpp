#pragma once

// Format
# define	DOTS		std::string(":")
# define	SPACE		std::string(" ")
# define	TILD		std::string("!~")
# define	NEW_LINE	std::string("\r\n")
# define	IP_ADD		std::string("@127.0.0.1")




/*****		USED				*****/

// NON-NUMERIC REPLIES
# define	WELCOME_MESSAGE(username)										DOTS + SERVER_NAME + " 001 " + username + \
																			" :Welcome to the " + SERVER_NAME + " IRC Network " + username + \
																			TILD + username + IP_ADD + NEW_LINE + \
																			DOTS + SERVER_NAME + " 002 " + username + \
																			" :Your host is ircserv, running version bahamut-2.2.2" + NEW_LINE + \
																			DOTS + SERVER_NAME + " 003 " + username + \
																			" :This server was created Tue Apr 30 2024 at 16:38:57 UTC" + NEW_LINE

# define	NICK_CHANGED(old_nick, username, new_nick, command)				DOTS + old_nick + TILD + username + IP_ADD + SPACE + command + " :" + new_nick + NEW_LINE
# define	MSG_RECEIVED(sdr_nick, rcv_usrnm, rcv_nick, msg, command)		DOTS + sdr_nick + TILD + rcv_usrnm + IP_ADD + SPACE + command + SPACE + rcv_nick + " :" + msg + NEW_LINE
# define	JOINED_CHANNEL(nickname, username, chan_name, command)			DOTS + nickname + TILD + username + IP_ADD + SPACE + command + " :" + chan_name + NEW_LINE
# define	RPL_TOPIC2(nickname, username, chan_name, chan_top, command)	DOTS + nickname + TILD + username + IP_ADD + SPACE + command + SPACE + chan_name + " :" + chan_top + NEW_LINE
# define	RPL_KICK(nickname, username, chan_name, kcked_nick, command)	DOTS + nickname + TILD + username + IP_ADD + SPACE + command + SPACE + chan_name + SPACE + kcked_nick + " :" + nickname + NEW_LINE




// ERRORS
# define	ERR_NOSUCHNICK(prefix, nickname)				DOTS + prefix + SPACE + "401 " + "" + nickname + " :No such nick/channel" + NEW_LINE
# define	ERR_NOSUCHSERVER(prefix, server_name)			DOTS + prefix + SPACE + "402 " + "" + server_name + " :No such server" + NEW_LINE
# define	ERR_NOSUCHCHANNEL(prefix, channel_name)			DOTS + prefix + SPACE + "403 " + "" + channel_name + " :No such channel" + NEW_LINE
# define	ERR_ERRONEUSNICKNAME(prefix, nick)				DOTS + prefix + SPACE + "432 " + "" + nick + " :Erroneus nickname" + NEW_LINE
# define	ERR_NICKNAMEINUSE(prefix, nick)					DOTS + prefix + SPACE + "433 " + "" + nick + " :Nickname is already in use" + NEW_LINE
# define	ERR_NEEDMOREPARAMS(prefix, command)				DOTS + prefix + SPACE + "461 " + "" + command + " :Not enough parameters" + NEW_LINE
# define	ERR_NOTONCHANNEL(prefix, channel)				DOTS + prefix + SPACE + "442 " + "" + channel + " :You're not on that channel" + NEW_LINE
# define	ERR_USERONCHANNEL(prefix, user, channel)		DOTS + prefix + SPACE + "443 " + "" + user + SPACE + channel + " :is already on channel" + NEW_LINE
// to be used in invite_utils.cpp and others
# define	ERR_CHANOPRIVSNEEDED(prefix, channel)			DOTS + prefix + SPACE + "482 " + "" + channel + " :You're not channel operator" + NEW_LINE

# define	ERR_INVITEONLYCHAN(prefix, channel)				DOTS + prefix + SPACE + "473 " + "" + channel + " :Cannot join channel (+i)" + NEW_LINE
# define	ERR_BADCHANNELKEY(prefix, channel)				DOTS + prefix + SPACE + "475 " + "" + channel + " :Cannot join channel (+k)" + NEW_LINE


// NUMERIC REPLIES
# define	RPL_INVITING(prefix, channel, nick)				DOTS + prefix + SPACE + "341 " + "" + channel + SPACE + nick + "" + NEW_LINE


/*****		NOT USED YET		*****/

// ERRORS
# define	ERR_CANNOTSENDTOCHAN(prefix, channel_name)		DOTS + prefix + SPACE + "404 " + "" + channel_name + " :Cannot send to channel" + NEW_LINE
# define	ERR_TOOMANYCHANNELS(prefix, channel_name)		DOTS + prefix + SPACE + "405 " + "" + channel_name + " :You have joined too many channels" + NEW_LINE
# define	ERR_WASNOSUCHNICK(prefix, nickname)				DOTS + prefix + SPACE + "406 " + "" + nickname + " :There was no such nickname" + NEW_LINE
# define	ERR_TOOMANYTARGETS(prefix, target)				DOTS + prefix + SPACE + "407 " + "" + target + " :Duplicate recipients. No message delivered" + NEW_LINE
# define	ERR_NOORIGIN(prefix)							DOTS + prefix + SPACE + "409 " + ":No origin specified" + NEW_LINE
# define	ERR_NORECIPIENT(prefix, command)				DOTS + prefix + SPACE + "411 " + ":No recipient given (" + command + ")" + NEW_LINE
# define	ERR_NOTEXTTOSEND(prefix)						DOTS + prefix + SPACE + "412 " + ":No text to send" + NEW_LINE
# define	ERR_NOTTOPLEVEL(prefix, mask)					DOTS + prefix + SPACE + "413 " + "" + mask + " :No toplevel domain specified" + NEW_LINE
# define	ERR_WILDTOPLEVEL(prefix, mask)					DOTS + prefix + SPACE + "414 " + "" + mask + " :Wildcard in toplevel domain" + NEW_LINE
# define	ERR_UNKNOWNCOMMAND(prefix, command)				DOTS + prefix + SPACE + "421 " + "" + command + " :Unknown command" + NEW_LINE
# define	ERR_NOMOTD(prefix)								DOTS + prefix + SPACE + "422 " + ":MOTD File is missing" + NEW_LINE
# define	ERR_NOADMININFO(prefix, server)					DOTS + prefix + SPACE + "423 " + "" + server + " :No administrative info available" + NEW_LINE
# define	ERR_FILEERROR(prefix, file_op, file)			DOTS + prefix + SPACE + "424 " + ":File error doing " + file_op + " on " + file + "" + NEW_LINE
# define	ERR_NONICKNAMEGIVEN(prefix)						DOTS + prefix + SPACE + "431 " + ":No nickname given" + NEW_LINE
# define	ERR_NICKCOLLISION(prefix, nick)					DOTS + prefix + SPACE + "436 " + "" + nick + " :Nickname collision KILL" + NEW_LINE
# define	ERR_USERNOTINCHANNEL(prefix, nick, channel)		DOTS + prefix + SPACE + "441 " + "" + nick + SPACE + channel + " :They aren't on that channel" + NEW_LINE
# define	ERR_NOLOGIN(prefix, user)						DOTS + prefix + SPACE + "444 " + "" + user + " :User not logged in" + NEW_LINE
# define	ERR_SUMMONDISABLED(prefix)						DOTS + prefix + SPACE + "445 " + ":SUMMON has been disabled" + NEW_LINE
# define	ERR_USERSDISABLED(prefix)						DOTS + prefix + SPACE + "446 " + ":USERS has been disabled" + NEW_LINE
# define	ERR_NOTREGISTERED(prefix)						DOTS + prefix + SPACE + "451 " + ":You have not registered" + NEW_LINE
# define	ERR_ALREADYREGISTRED(prefix)					DOTS + prefix + SPACE + "462 " + ":You may not reregister" + NEW_LINE
# define	ERR_NOPERMFORHOST(prefix)						DOTS + prefix + SPACE + "463 " + ":Your host isn't among the privileged" + NEW_LINE
# define	ERR_PASSWDMISMATCH(prefix)						DOTS + prefix + SPACE + "464 " + ":Password incorrect" + NEW_LINE
# define	ERR_YOUREBANNEDCREEP(prefix)					DOTS + prefix + SPACE + "465 " + ":You are banned from this server" + NEW_LINE
# define	ERR_KEYSET(prefix, channel)						DOTS + prefix + SPACE + "467 " + "" + channel + " :Channel key already set" + NEW_LINE
# define	ERR_CHANNELISFULL(prefix, channel)				DOTS + prefix + SPACE + "471 " + "" + channel + " :Cannot join channel (+l)" + NEW_LINE
# define	ERR_UNKNOWNMODE(prefix, char)					DOTS + prefix + SPACE + "472 " + "" + char + " :is unknown mode char to me" + NEW_LINE
# define	ERR_BANNEDFROMCHAN(prefix, channel)				DOTS + prefix + SPACE + "474 " + "" + channel + " :Cannot join channel (+b)" + NEW_LINE
# define	ERR_NOPRIVILEGES(prefix)						DOTS + prefix + SPACE + "481 " + ":Permission Denied- You're not an IRC operator" + NEW_LINE
# define	ERR_CANTKILLSERVER(prefix)						DOTS + prefix + SPACE + "483 " + ":You cant kill a server!" + NEW_LINE
# define	ERR_NOOPERHOST(prefix)							DOTS + prefix + SPACE + "491 " + ":No O-lines for your host" + NEW_LINE
# define	ERR_UMODEUNKNOWNFLAG(prefix)					DOTS + prefix + SPACE + "501 " + ":Unknown MODE flag" + NEW_LINE
# define	ERR_USERSDONTMATCH(prefix)						DOTS + prefix + SPACE + "502 " + ":Cant change mode for other users" + NEW_LINE

// REPLIES
# define	RPL_WHOISUSER(prefix, nick, user, host, real_name)		DOTS + prefix + SPACE + "311 " + "" + nick + SPACE + user + SPACE + host + " * :" + real_name + "" + NEW_LINE
# define	RPL_WHOISSERVER(prefix, nick, server, server_info)		DOTS + prefix + SPACE + "312 " + "" + nick + SPACE + server + " :" + server_info + "" + NEW_LINE
# define	RPL_WHOISOPERATOR(prefix, nick)							DOTS + prefix + SPACE + "313 " + "" + nick + " :is an IRC operator" + NEW_LINE
# define	RPL_WHOISIDLE(prefix, nick, integer)					DOTS + prefix + SPACE + "317 " + "" + nick + SPACE + integer + " :seconds idle" + NEW_LINE
# define	RPL_ENDOFWHOIS(prefix, nick)							DOTS + prefix + SPACE + "318 " + "" + nick + " :End of /WHOIS list" + NEW_LINE
# define	RPL_WHOISCHANNELS(prefix, nick, channel, space)			DOTS + prefix + SPACE + "319 " + "" + nick + " :{[@|+]" + channel + "" + space + "}" + NEW_LINE
# define	RPL_WHOWASUSER(prefix, nick, user, host, real_name)		DOTS + prefix + SPACE + "314 " + "" + nick + SPACE + user + SPACE + host + " * :" + real_name + "" + NEW_LINE
# define	RPL_ENDOFWHOWAS(prefix, nick)							DOTS + prefix + SPACE + "369 " + "" + nick + " :End of WHOWAS" + NEW_LINE
# define	RPL_LISTSTART(prefix)									DOTS + prefix + SPACE + "321 " + "Channel :Users Name" + NEW_LINE
# define	RPL_LISTEND(prefix)										DOTS + prefix + SPACE + "323 " + ":End of /LIST" + NEW_LINE
# define	RPL_CHANNELMODEIS(prefix, channel, mode, mode_params)	DOTS + prefix + SPACE + "324 " + "" + channel + SPACE + mode + SPACE + mode_params + "" + NEW_LINE
# define	RPL_NOTOPIC(prefix, channel)							DOTS + prefix + SPACE + "331 " /* + "" */ + channel + " :No topic is set" + NEW_LINE
# define	RPL_TOPIC(prefix, channel, topic)						DOTS + prefix + SPACE + "332 " + "" + channel + " :" + topic + "" + NEW_LINE
# define	RPL_SUMMONING(prefix, user)								DOTS + prefix + SPACE + "342 " + "" + user + " :Summoning user to IRC" + NEW_LINE
# define	RPL_ENDOFWHO(prefix, name)								DOTS + prefix + SPACE + "315 " + "" + name + " :End of /WHO list" + NEW_LINE
# define	RPL_ENDOFNAMES(prefix, channel)							DOTS + prefix + SPACE + "366 " + "" + channel + " :End of /NAMES list" + NEW_LINE
# define	RPL_ENDOFLINKS(prefix, mask)							DOTS + prefix + SPACE + "365 " + "" + mask + " :End of /LINKS list" + NEW_LINE
# define	RPL_BANLIST(prefix, channel, banid)						DOTS + prefix + SPACE + "367 " + "" + channel + SPACE + banid + "" + NEW_LINE
# define	RPL_ENDOFBANLIST(prefix, channel)						DOTS + prefix + SPACE + "368 " + "" + channel + " :End of channel ban list" + NEW_LINE
# define	RPL_INFO(prefix, string)								DOTS + prefix + SPACE + "371 " + ":" + string + "" + NEW_LINE
# define	RPL_ENDOFINFO(prefix)									DOTS + prefix + SPACE + "374 " + ":End of /INFO list" + NEW_LINE
# define	RPL_MOTDSTART(prefix, server)							DOTS + prefix + SPACE + "375 " + ":- " + server + " Message of the day -" + NEW_LINE
# define	RPL_MOTD(prefix, text)									DOTS + prefix + SPACE + "372 " + ":- " + text + "" + NEW_LINE
# define	RPL_ENDOFMOTD(prefix)									DOTS + prefix + SPACE + "376 " + ":End of /MOTD command" + NEW_LINE
# define	RPL_YOUREOPER(prefix)									DOTS + prefix + SPACE + "381 " + ":You are now an IRC operator" + NEW_LINE
# define	RPL_REHASHING(prefix, config_file)						DOTS + prefix + SPACE + "382 " + "" + config_file + " :Rehashing" + NEW_LINE
# define	RPL_USERSSTART(prefix)									DOTS + prefix + SPACE + "392 " + ":UserID Terminal Host" + NEW_LINE
# define	RPL_USERS(prefix)										DOTS + prefix + SPACE + "393 " + ":%-8s %-9s %-8s" + NEW_LINE
# define	RPL_ENDOFUSERS(prefix)									DOTS + prefix + SPACE + "394 " + ":End of users" + NEW_LINE
# define	RPL_NOUSERS(prefix)										DOTS + prefix + SPACE + "395 " + ":Nobody logged in" + NEW_LINE
# define	RPL_TRACECONNECTING(prefix, class, server)				DOTS + prefix + SPACE + "201 " + "Try. " + class + SPACE + server + "" + NEW_LINE
# define	RPL_TRACEHANDSHAKE(prefix, class, server)				DOTS + prefix + SPACE + "202 " + "H.S. " + class + SPACE + server + "" + NEW_LINE
# define	RPL_TRACEOPERATOR(prefix, class, nick)					DOTS + prefix + SPACE + "204 " + "Oper " + class + SPACE + nick + "" + NEW_LINE
# define	RPL_TRACEUSER(prefix, class, nick)						DOTS + prefix + SPACE + "205 " + "User " + class + SPACE + nick + "" + NEW_LINE
# define	RPL_TRACENEWTYPE(prefix, newtype, client_name)			DOTS + prefix + SPACE + "208 " + "" + newtype + " 0 " + client_name + "" + NEW_LINE
# define	RPL_TRACELOG(prefix, logfile, debug_level)				DOTS + prefix + SPACE + "261 " + "File " + logfile + SPACE + debug_level + "" + NEW_LINE
# define	RPL_STATSCOMMANDS(prefix, command, count)				DOTS + prefix + SPACE + "212 " + "" + command + SPACE + count + "" + NEW_LINE
# define	RPL_STATSCLINE(prefix, host, name, port, class)			DOTS + prefix + SPACE + "213 " + "C " + host + " * " + name + SPACE + port + SPACE + class + "" + NEW_LINE
# define	RPL_STATSNLINE(prefix, host, name, port, class)			DOTS + prefix + SPACE + "214 " + "N " + host + " * " + name + SPACE + port + SPACE + class + "" + NEW_LINE
# define	RPL_STATSKLINE(prefix, host, username, port, class)		DOTS + prefix + SPACE + "216 " + "K " + host + " * " + username + SPACE + port + SPACE + class + "" + NEW_LINE
# define	RPL_ENDOFSTATS(prefix, stats_letter)					DOTS + prefix + SPACE + "219 " + "" + stats_letter + " :End of /STATS report" + NEW_LINE
# define	RPL_STATSUPTIME(prefix)									DOTS + prefix + SPACE + "242 " + ":Server Up %d days %d:%02d:%02d" + NEW_LINE
# define	RPL_STATSOLINE(prefix, hostmask, name)					DOTS + prefix + SPACE + "243 " + "O " + hostmask + " * " + name + "" + NEW_LINE
# define	RPL_STATSHLINE(prefix, hostmask, servername)			DOTS + prefix + SPACE + "244 " + "H " + hostmask + " * " + servername + "" + NEW_LINE
# define	RPL_UMODEIS(prefix, user_mode_string)					DOTS + prefix + SPACE + "221 " + "" + user_mode_string + "" + NEW_LINE
# define	RPL_LUSEROP(prefix, integer)							DOTS + prefix + SPACE + "252 " + "" + integer + " :operator(s) online" + NEW_LINE
# define	RPL_LUSERUNKNOWN(prefix, integer)						DOTS + prefix + SPACE + "253 " + "" + integer + " :unknown connection(s)" + NEW_LINE
# define	RPL_LUSERCHANNELS(prefix, integer)						DOTS + prefix + SPACE + "254 " + "" + integer + " :channels formed" + NEW_LINE