#pragma once

// Format
# define	DOTS		std::string(":")
# define	NEW_LINE	std::string("\r\n")

// ERRORS
# define	ERR_NOSUCHNICK(prefix, nickname)				DOTS + prefix + " " + "401 " + "" + nickname + " :No such nick/channel" + NEW_LINE
# define	ERR_NOSUCHSERVER(prefix, server_name)			DOTS + prefix + " " + "402 " + "" + server_name + " :No such server" + NEW_LINE
# define	ERR_NOSUCHCHANNEL(prefix, channel_name)			DOTS + prefix + " " + "403 " + "" + channel_name + " :No such channel" + NEW_LINE
# define	ERR_CANNOTSENDTOCHAN(prefix, channel_name)		DOTS + prefix + " " + "404 " + "" + channel_name + " :Cannot send to channel" + NEW_LINE
# define	ERR_TOOMANYCHANNELS(prefix, channel_name)		DOTS + prefix + " " + "405 " + "" + channel_name + " :You have joined too many channels" + NEW_LINE
# define	ERR_WASNOSUCHNICK(prefix, nickname)				DOTS + prefix + " " + "406 " + "" + nickname + " :There was no such nickname" + NEW_LINE
# define	ERR_TOOMANYTARGETS(prefix, target)				DOTS + prefix + " " + "407 " + "" + target + " :Duplicate recipients. No message delivered" + NEW_LINE
# define	ERR_NOORIGIN(prefix)							DOTS + prefix + " " + "409 " + ":No origin specified" + NEW_LINE
# define	ERR_NORECIPIENT(prefix, command)				DOTS + prefix + " " + "411 " + ":No recipient given (" + command + ")" + NEW_LINE
# define	ERR_NOTEXTTOSEND(prefix)						DOTS + prefix + " " + "412 " + ":No text to send" + NEW_LINE
# define	ERR_NOTTOPLEVEL(prefix, mask)					DOTS + prefix + " " + "413 " + "" + mask + " :No toplevel domain specified" + NEW_LINE
# define	ERR_WILDTOPLEVEL(prefix, mask)					DOTS + prefix + " " + "414 " + "" + mask + " :Wildcard in toplevel domain" + NEW_LINE
# define	ERR_UNKNOWNCOMMAND(prefix, command)				DOTS + prefix + " " + "421 " + "" + command + " :Unknown command" + NEW_LINE
# define	ERR_NOMOTD(prefix)								DOTS + prefix + " " + "422 " + ":MOTD File is missing" + NEW_LINE
# define	ERR_NOADMININFO(prefix, server)					DOTS + prefix + " " + "423 " + "" + server + " :No administrative info available" + NEW_LINE
# define	ERR_FILEERROR(prefix, file_op, file)			DOTS + prefix + " " + "424 " + ":File error doing " + file_op + " on " + file + "" + NEW_LINE
# define	ERR_NONICKNAMEGIVEN(prefix)						DOTS + prefix + " " + "431 " + ":No nickname given" + NEW_LINE
# define	ERR_ERRONEUSNICKNAME(prefix, nick)				DOTS + prefix + " " + "432 " + "" + nick + " :Erroneus nickname" + NEW_LINE
# define	ERR_NICKNAMEINUSE(prefix, nick)					DOTS + prefix + " " + "433 " + "" + nick + " :Nickname is already in use" + NEW_LINE
# define	ERR_NICKCOLLISION(prefix, nick)					DOTS + prefix + " " + "436 " + "" + nick + " :Nickname collision KILL" + NEW_LINE
# define	ERR_USERNOTINCHANNEL(prefix, nick, channel)		DOTS + prefix + " " + "441 " + "" + nick + " " + channel + " :They aren't on that channel" + NEW_LINE
# define	ERR_NOTONCHANNEL(prefix, channel)				DOTS + prefix + " " + "442 " + "" + channel + " :You're not on that channel" + NEW_LINE
# define	ERR_USERONCHANNEL(prefix, user, channel)		DOTS + prefix + " " + "443 " + "" + user + " " + channel + " :is already on channel" + NEW_LINE
# define	ERR_NOLOGIN(prefix, user)						DOTS + prefix + " " + "444 " + "" + user + " :User not logged in" + NEW_LINE
# define	ERR_SUMMONDISABLED(prefix)						DOTS + prefix + " " + "445 " + ":SUMMON has been disabled" + NEW_LINE
# define	ERR_USERSDISABLED(prefix)						DOTS + prefix + " " + "446 " + ":USERS has been disabled" + NEW_LINE
# define	ERR_NOTREGISTERED(prefix)						DOTS + prefix + " " + "451 " + ":You have not registered" + NEW_LINE
# define	ERR_NEEDMOREPARAMS(prefix, command)				DOTS + prefix + " " + "461 " + "" + command + " :Not enough parameters" + NEW_LINE
# define	ERR_ALREADYREGISTRED(prefix)					DOTS + prefix + " " + "462 " + ":You may not reregister" + NEW_LINE
# define	ERR_NOPERMFORHOST(prefix)						DOTS + prefix + " " + "463 " + ":Your host isn't among the privileged" + NEW_LINE
# define	ERR_PASSWDMISMATCH(prefix)						DOTS + prefix + " " + "464 " + ":Password incorrect" + NEW_LINE
# define	ERR_YOUREBANNEDCREEP(prefix)					DOTS + prefix + " " + "465 " + ":You are banned from this server" + NEW_LINE
# define	ERR_KEYSET(prefix, channel)						DOTS + prefix + " " + "467 " + "" + channel + " :Channel key already set" + NEW_LINE
# define	ERR_CHANNELISFULL(prefix, channel)				DOTS + prefix + " " + "471 " + "" + channel + " :Cannot join channel (+l)" + NEW_LINE
# define	ERR_UNKNOWNMODE(prefix, char)					DOTS + prefix + " " + "472 " + "" + char + " :is unknown mode char to me" + NEW_LINE
# define	ERR_INVITEONLYCHAN(prefix, channel)				DOTS + prefix + " " + "473 " + "" + channel + " :Cannot join channel (+i)" + NEW_LINE
# define	ERR_BANNEDFROMCHAN(prefix, channel)				DOTS + prefix + " " + "474 " + "" + channel + " :Cannot join channel (+b)" + NEW_LINE
# define	ERR_BADCHANNELKEY(prefix, channel)				DOTS + prefix + " " + "475 " + "" + channel + " :Cannot join channel (+k)" + NEW_LINE
# define	ERR_NOPRIVILEGES(prefix)						DOTS + prefix + " " + "481 " + ":Permission Denied- You're not an IRC operator" + NEW_LINE
# define	ERR_CHANOPRIVSNEEDED(prefix, channel)			DOTS + prefix + " " + "482 " + "" + channel + " :You're not channel operator" + NEW_LINE
# define	ERR_CANTKILLSERVER(prefix)						DOTS + prefix + " " + "483 " + ":You cant kill a server!" + NEW_LINE
# define	ERR_NOOPERHOST(prefix)							DOTS + prefix + " " + "491 " + ":No O-lines for your host" + NEW_LINE
# define	ERR_UMODEUNKNOWNFLAG(prefix)					DOTS + prefix + " " + "501 " + ":Unknown MODE flag" + NEW_LINE
# define	ERR_USERSDONTMATCH(prefix)						DOTS + prefix + " " + "502 " + ":Cant change mode for other users" + NEW_LINE

// REPLIES
# define	RPL_WHOISUSER(prefix, nick, user, host, real_name)						DOTS + prefix + " " + "311 " + "" + nick + " " + user + " " + host + " * :" + real_name + "" + NEW_LINE
# define	RPL_WHOISSERVER(prefix, nick, server, server_info)						DOTS + prefix + " " + "312 " + "" + nick + " " + server + " :" + server_info + "" + NEW_LINE
# define	RPL_WHOISOPERATOR(prefix, nick)											DOTS + prefix + " " + "313 " + "" + nick + " :is an IRC operator" + NEW_LINE
# define	RPL_WHOISIDLE(prefix, nick, integer)									DOTS + prefix + " " + "317 " + "" + nick + " " + integer + " :seconds idle" + NEW_LINE
# define	RPL_ENDOFWHOIS(prefix, nick)											DOTS + prefix + " " + "318 " + "" + nick + " :End of /WHOIS list" + NEW_LINE
# define	RPL_WHOISCHANNELS(prefix, nick, channel, space)							DOTS + prefix + " " + "319 " + "" + nick + " :{[@|+]" + channel + "" + space + "}" + NEW_LINE
# define	RPL_WHOWASUSER(prefix, nick, user, host, real_name)						DOTS + prefix + " " + "314 " + "" + nick + " " + user + " " + host + " * :" + real_name + "" + NEW_LINE
# define	RPL_ENDOFWHOWAS(prefix, nick)											DOTS + prefix + " " + "369 " + "" + nick + " :End of WHOWAS" + NEW_LINE
# define	RPL_LISTSTART(prefix)													DOTS + prefix + " " + "321 " + "Channel :Users Name" + NEW_LINE
# define	RPL_LISTEND(prefix)														DOTS + prefix + " " + "323 " + ":End of /LIST" + NEW_LINE
# define	RPL_CHANNELMODEIS(prefix, channel, mode, mode_params)					DOTS + prefix + " " + "324 " + "" + channel + " " + mode + " " + mode_params + "" + NEW_LINE
# define	RPL_NOTOPIC(prefix, channel)											DOTS + prefix + " " + "331 " /* + "" */ + channel + " :No topic is set" + NEW_LINE
# define	RPL_TOPIC(prefix, channel, topic)										DOTS + prefix + " " + "332 " + "" + channel + " :" + topic + "" + NEW_LINE
# define	RPL_INVITING(prefix, channel, nick)										DOTS + prefix + " " + "341 " + "" + channel + " " + nick + "" + NEW_LINE
# define	RPL_SUMMONING(prefix, user)												DOTS + prefix + " " + "342 " + "" + user + " :Summoning user to IRC" + NEW_LINE
# define	RPL_VERSION(prefix, version, debuglevel, server, comments)				DOTS + prefix + " " + "351 " + "" + version + "." + debuglevel + " " + server + " :" + comments + "" + NEW_LINE
# define	RPL_ENDOFWHO(prefix, name)												DOTS + prefix + " " + "315 " + "" + name + " :End of /WHO list" + NEW_LINE
# define	RPL_ENDOFNAMES(prefix, channel)											DOTS + prefix + " " + "366 " + "" + channel + " :End of /NAMES list" + NEW_LINE
# define	RPL_LINKS(prefix, mask, server, hopcount, server_info)					DOTS + prefix + " " + "364 " + "" + mask + " " + server + " :" + hopcount + " " + server_info + "" + NEW_LINE
# define	RPL_ENDOFLINKS(prefix, mask)											DOTS + prefix + " " + "365 " + "" + mask + " :End of /LINKS list" + NEW_LINE
# define	RPL_BANLIST(prefix, channel, banid)										DOTS + prefix + " " + "367 " + "" + channel + " " + banid + "" + NEW_LINE
# define	RPL_ENDOFBANLIST(prefix, channel)										DOTS + prefix + " " + "368 " + "" + channel + " :End of channel ban list" + NEW_LINE
# define	RPL_INFO(prefix, string)												DOTS + prefix + " " + "371 " + ":" + string + "" + NEW_LINE
# define	RPL_ENDOFINFO(prefix)													DOTS + prefix + " " + "374 " + ":End of /INFO list" + NEW_LINE
# define	RPL_MOTDSTART(prefix, server)											DOTS + prefix + " " + "375 " + ":- " + server + " Message of the day -" + NEW_LINE
# define	RPL_MOTD(prefix, text)													DOTS + prefix + " " + "372 " + ":- " + text + "" + NEW_LINE
# define	RPL_ENDOFMOTD(prefix)													DOTS + prefix + " " + "376 " + ":End of /MOTD command" + NEW_LINE
# define	RPL_YOUREOPER(prefix)													DOTS + prefix + " " + "381 " + ":You are now an IRC operator" + NEW_LINE
# define	RPL_REHASHING(prefix, config_file)										DOTS + prefix + " " + "382 " + "" + config_file + " :Rehashing" + NEW_LINE
# define	RPL_USERSSTART(prefix)													DOTS + prefix + " " + "392 " + ":UserID Terminal Host" + NEW_LINE
# define	RPL_USERS(prefix)														DOTS + prefix + " " + "393 " + ":%-8s %-9s %-8s" + NEW_LINE
# define	RPL_ENDOFUSERS(prefix)													DOTS + prefix + " " + "394 " + ":End of users" + NEW_LINE
# define	RPL_NOUSERS(prefix)														DOTS + prefix + " " + "395 " + ":Nobody logged in" + NEW_LINE
# define	RPL_TRACECONNECTING(prefix, class, server)								DOTS + prefix + " " + "201 " + "Try. " + class + " " + server + "" + NEW_LINE
# define	RPL_TRACEHANDSHAKE(prefix, class, server)								DOTS + prefix + " " + "202 " + "H.S. " + class + " " + server + "" + NEW_LINE
# define	RPL_TRACEUNKNOWN(prefix, class, client_IP_address_in_dot_form)			DOTS + prefix + " " + "203 " + "???? " + class + " [" + client_IP_address_in_dot_form + "]" + NEW_LINE
# define	RPL_TRACEOPERATOR(prefix, class, nick)									DOTS + prefix + " " + "204 " + "Oper " + class + " " + nick + "" + NEW_LINE
# define	RPL_TRACEUSER(prefix, class, nick)										DOTS + prefix + " " + "205 " + "User " + class + " " + nick + "" + NEW_LINE
# define	RPL_TRACENEWTYPE(prefix, newtype, client_name)							DOTS + prefix + " " + "208 " + "" + newtype + " 0 " + client_name + "" + NEW_LINE
# define	RPL_TRACELOG(prefix, logfile, debug_level)								DOTS + prefix + " " + "261 " + "File " + logfile + " " + debug_level + "" + NEW_LINE
# define	RPL_STATSCOMMANDS(prefix, command, count)								DOTS + prefix + " " + "212 " + "" + command + " " + count + "" + NEW_LINE
# define	RPL_STATSCLINE(prefix, host, name, port, class)							DOTS + prefix + " " + "213 " + "C " + host + " * " + name + " " + port + " " + class + "" + NEW_LINE
# define	RPL_STATSNLINE(prefix, host, name, port, class)							DOTS + prefix + " " + "214 " + "N " + host + " * " + name + " " + port + " " + class + "" + NEW_LINE
# define	RPL_STATSKLINE(prefix, host, username, port, class)						DOTS + prefix + " " + "216 " + "K " + host + " * " + username + " " + port + " " + class + "" + NEW_LINE
# define	RPL_STATSYLINE(prefix, class, ping_frequency, connect_frequency, max_sendq)	DOTS + prefix + " " + "218 " + "Y " + class + " " + ping_frequency + " " + connect_frequency + " " + max_sendq + "" + NEW_LINE
# define	RPL_ENDOFSTATS(prefix, stats_letter)									DOTS + prefix + " " + "219 " + "" + stats_letter + " :End of /STATS report" + NEW_LINE
# define	RPL_STATSLLINE(prefix, hostmask, servername, maxdepth)					DOTS + prefix + " " + "241 " + "L " + hostmask + " * " + servername + " " + maxdepth + "" + NEW_LINE
# define	RPL_STATSUPTIME(prefix)													DOTS + prefix + " " + "242 " + ":Server Up %d days %d:%02d:%02d" + NEW_LINE
# define	RPL_STATSOLINE(prefix, hostmask, name)									DOTS + prefix + " " + "243 " + "O " + hostmask + " * " + name + "" + NEW_LINE
# define	RPL_STATSHLINE(prefix, hostmask, servername)							DOTS + prefix + " " + "244 " + "H " + hostmask + " * " + servername + "" + NEW_LINE
# define	RPL_UMODEIS(prefix, user_mode_string)									DOTS + prefix + " " + "221 " + "" + user_mode_string + "" + NEW_LINE
# define	RPL_LUSEROP(prefix, integer)											DOTS + prefix + " " + "252 " + "" + integer + " :operator(s) online" + NEW_LINE
# define	RPL_LUSERUNKNOWN(prefix, integer)										DOTS + prefix + " " + "253 " + "" + integer + " :unknown connection(s)" + NEW_LINE
# define	RPL_LUSERCHANNELS(prefix, integer)										DOTS + prefix + " " + "254 " + "" + integer + " :channels formed" + NEW_LINE
