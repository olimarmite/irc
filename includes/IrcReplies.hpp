
	# define ERR_NOSUCHNICK(prefix, nickname)	std::string(":") + 	prefix + " " + "401 " + "" + nickname + " :No such nick/channel" + std::string("\r\n")


	# define ERR_NOSUCHSERVER(prefix, server_name)	std::string(":") + 	prefix + " " + "402 " + "" + server_name + " :No such server" + std::string("\r\n")


	# define ERR_NOSUCHCHANNEL(prefix, channel_name)	std::string(":") + 	prefix + " " + "403 " + "" + channel_name + " :No such channel" + std::string("\r\n")


	# define ERR_CANNOTSENDTOCHAN(prefix, channel_name)	std::string(":") + 	prefix + " " + "404 " + "" + channel_name + " :Cannot send to channel" + std::string("\r\n")


	# define ERR_TOOMANYCHANNELS(prefix, channel_name)	std::string(":") + 	prefix + " " + "405 " + "" + channel_name + " :You have joined too many channels" + std::string("\r\n")


	# define ERR_WASNOSUCHNICK(prefix, nickname)	std::string(":") + 	prefix + " " + "406 " + "" + nickname + " :There was no such nickname" + std::string("\r\n")


	# define ERR_TOOMANYTARGETS(prefix, target)	std::string(":") + 	prefix + " " + "407 " + "" + target + " :Duplicate recipients. No message delivered" + std::string("\r\n")


	# define ERR_NOORIGIN(prefix)	std::string(":") + 	prefix + " " + "409 " + ":No origin specified" + std::string("\r\n")


	# define ERR_NORECIPIENT(prefix, command)	std::string(":") + 	prefix + " " + "411 " + ":No recipient given (" + command + ")" + std::string("\r\n")


	# define ERR_NOTEXTTOSEND(prefix)	std::string(":") + 	prefix + " " + "412 " + ":No text to send" + std::string("\r\n")


	# define ERR_NOTTOPLEVEL(prefix, mask)	std::string(":") + 	prefix + " " + "413 " + "" + mask + " :No toplevel domain specified" + std::string("\r\n")


	# define ERR_WILDTOPLEVEL(prefix, mask)	std::string(":") + 	prefix + " " + "414 " + "" + mask + " :Wildcard in toplevel domain" + std::string("\r\n")


	# define ERR_UNKNOWNCOMMAND(prefix, command)	std::string(":") + 	prefix + " " + "421 " + "" + command + " :Unknown command" + std::string("\r\n")


	# define ERR_NOMOTD(prefix)	std::string(":") + 	prefix + " " + "422 " + ":MOTD File is missing" + std::string("\r\n")


	# define ERR_NOADMININFO(prefix, server)	std::string(":") + 	prefix + " " + "423 " + "" + server + " :No administrative info available" + std::string("\r\n")


	# define ERR_FILEERROR(prefix, file_op, file)	std::string(":") + 	prefix + " " + "424 " + ":File error doing " + file_op + " on " + file + "" + std::string("\r\n")


	# define ERR_NONICKNAMEGIVEN(prefix)	std::string(":") + 	prefix + " " + "431 " + ":No nickname given" + std::string("\r\n")


	# define ERR_ERRONEUSNICKNAME(prefix, nick)	std::string(":") + 	prefix + " " + "432 " + "" + nick + " :Erroneus nickname" + std::string("\r\n")


	# define ERR_NICKNAMEINUSE(prefix, nick)	std::string(":") + 	prefix + " " + "433 " + "" + nick + " :Nickname is already in use" + std::string("\r\n")


	# define ERR_NICKCOLLISION(prefix, nick)	std::string(":") + 	prefix + " " + "436 " + "" + nick + " :Nickname collision KILL" + std::string("\r\n")


	# define ERR_USERNOTINCHANNEL(prefix, nick, channel)	std::string(":") + 	prefix + " " + "441 " + "" + nick + " " + channel + " :They aren't on that channel" + std::string("\r\n")


	# define ERR_NOTONCHANNEL(prefix, channel)	std::string(":") + 	prefix + " " + "442 " + "" + channel + " :You're not on that channel" + std::string("\r\n")


	# define ERR_USERONCHANNEL(prefix, user, channel)	std::string(":") + 	prefix + " " + "443 " + "" + user + " " + channel + " :is already on channel" + std::string("\r\n")


	# define ERR_NOLOGIN(prefix, user)	std::string(":") + 	prefix + " " + "444 " + "" + user + " :User not logged in" + std::string("\r\n")


	# define ERR_SUMMONDISABLED(prefix)	std::string(":") + 	prefix + " " + "445 " + ":SUMMON has been disabled" + std::string("\r\n")


	# define ERR_USERSDISABLED(prefix)	std::string(":") + 	prefix + " " + "446 " + ":USERS has been disabled" + std::string("\r\n")


	# define ERR_NOTREGISTERED(prefix)	std::string(":") + 	prefix + " " + "451 " + ":You have not registered" + std::string("\r\n")


	# define ERR_NEEDMOREPARAMS(prefix, command)	std::string(":") + 	prefix + " " + "461 " + "" + command + " :Not enough parameters" + std::string("\r\n")


	# define ERR_ALREADYREGISTRED(prefix)	std::string(":") + 	prefix + " " + "462 " + ":You may not reregister" + std::string("\r\n")


	# define ERR_NOPERMFORHOST(prefix)	std::string(":") + 	prefix + " " + "463 " + ":Your host isn't among the privileged" + std::string("\r\n")


	# define ERR_PASSWDMISMATCH(prefix)	std::string(":") + 	prefix + " " + "464 " + ":Password incorrect" + std::string("\r\n")


	# define ERR_YOUREBANNEDCREEP(prefix)	std::string(":") + 	prefix + " " + "465 " + ":You are banned from this server" + std::string("\r\n")


	# define ERR_KEYSET(prefix, channel)	std::string(":") + 	prefix + " " + "467 " + "" + channel + " :Channel key already set" + std::string("\r\n")


	# define ERR_CHANNELISFULL(prefix, channel)	std::string(":") + 	prefix + " " + "471 " + "" + channel + " :Cannot join channel (+l)" + std::string("\r\n")


	# define ERR_UNKNOWNMODE(prefix, char)	std::string(":") + 	prefix + " " + "472 " + "" + char + " :is unknown mode char to me" + std::string("\r\n")


	# define ERR_INVITEONLYCHAN(prefix, channel)	std::string(":") + 	prefix + " " + "473 " + "" + channel + " :Cannot join channel (+i)" + std::string("\r\n")


	# define ERR_BANNEDFROMCHAN(prefix, channel)	std::string(":") + 	prefix + " " + "474 " + "" + channel + " :Cannot join channel (+b)" + std::string("\r\n")


	# define ERR_BADCHANNELKEY(prefix, channel)	std::string(":") + 	prefix + " " + "475 " + "" + channel + " :Cannot join channel (+k)" + std::string("\r\n")


	# define ERR_NOPRIVILEGES(prefix)	std::string(":") + 	prefix + " " + "481 " + ":Permission Denied- You're not an IRC operator" + std::string("\r\n")


	# define ERR_CHANOPRIVSNEEDED(prefix, channel)	std::string(":") + 	prefix + " " + "482 " + "" + channel + " :You're not channel operator" + std::string("\r\n")


	# define ERR_CANTKILLSERVER(prefix)	std::string(":") + 	prefix + " " + "483 " + ":You cant kill a server!" + std::string("\r\n")


	# define ERR_NOOPERHOST(prefix)	std::string(":") + 	prefix + " " + "491 " + ":No O-lines for your host" + std::string("\r\n")


	# define ERR_UMODEUNKNOWNFLAG(prefix)	std::string(":") + 	prefix + " " + "501 " + ":Unknown MODE flag" + std::string("\r\n")


	# define ERR_USERSDONTMATCH(prefix)	std::string(":") + 	prefix + " " + "502 " + ":Cant change mode for other users" + std::string("\r\n")


	# define RPL_NONE(prefix)	std::string(":") + 	prefix + " " + "300 " + "n/a" + std::string("\r\n")


	# define RPL_AWAY(prefix, nick, away_message)	std::string(":") + 	prefix + " " + "301 " + "" + nick + " :" + away_message + "" + std::string("\r\n")


	# define RPL_UNAWAY(prefix)	std::string(":") + 	prefix + " " + "305 " + ":You are no longer marked as being away" + std::string("\r\n")


	# define RPL_NOWAWAY(prefix)	std::string(":") + 	prefix + " " + "306 " + ":You have been marked as being away" + std::string("\r\n")


	# define RPL_WHOISUSER(prefix, nick, user, host, real_name)	std::string(":") + 	prefix + " " + "311 " + "" + nick + " " + user + " " + host + " * :" + real_name + "" + std::string("\r\n")


	# define RPL_WHOISSERVER(prefix, nick, server, server_info)	std::string(":") + 	prefix + " " + "312 " + "" + nick + " " + server + " :" + server_info + "" + std::string("\r\n")


	# define RPL_WHOISOPERATOR(prefix, nick)	std::string(":") + 	prefix + " " + "313 " + "" + nick + " :is an IRC operator" + std::string("\r\n")


	# define RPL_WHOISIDLE(prefix, nick, integer)	std::string(":") + 	prefix + " " + "317 " + "" + nick + " " + integer + " :seconds idle" + std::string("\r\n")


	# define RPL_ENDOFWHOIS(prefix, nick)	std::string(":") + 	prefix + " " + "318 " + "" + nick + " :End of /WHOIS list" + std::string("\r\n")


	# define RPL_WHOISCHANNELS(prefix, nick, channel, space)	std::string(":") + 	prefix + " " + "319 " + "" + nick + " :{[@|+]" + channel + "" + space + "}" + std::string("\r\n")


	# define RPL_WHOWASUSER(prefix, nick, user, host, real_name)	std::string(":") + 	prefix + " " + "314 " + "" + nick + " " + user + " " + host + " * :" + real_name + "" + std::string("\r\n")


	# define RPL_ENDOFWHOWAS(prefix, nick)	std::string(":") + 	prefix + " " + "369 " + "" + nick + " :End of WHOWAS" + std::string("\r\n")


	# define RPL_LISTSTART(prefix)	std::string(":") + 	prefix + " " + "321 " + "Channel :Users Name" + std::string("\r\n")


	# define RPL_LISTEND(prefix)	std::string(":") + 	prefix + " " + "323 " + ":End of /LIST" + std::string("\r\n")


	# define RPL_CHANNELMODEIS(prefix, channel, mode, mode_params)	std::string(":") + 	prefix + " " + "324 " + "" + channel + " " + mode + " " + mode_params + "" + std::string("\r\n")


	# define RPL_NOTOPIC(prefix, channel)	std::string(":") + 	prefix + " " + "331 " /* + "" */ + channel + " :No topic is set" + std::string("\r\n")


	# define RPL_TOPIC(prefix, channel, topic)	std::string(":") + 	prefix + " " + "332 " + "" + channel + " :" + topic + "" + std::string("\r\n")


	# define RPL_INVITING(prefix, channel, nick)	std::string(":") + 	prefix + " " + "341 " + "" + channel + " " + nick + "" + std::string("\r\n")


	# define RPL_SUMMONING(prefix, user)	std::string(":") + 	prefix + " " + "342 " + "" + user + " :Summoning user to IRC" + std::string("\r\n")


	# define RPL_VERSION(prefix, version, debuglevel, server, comments)	std::string(":") + 	prefix + " " + "351 " + "" + version + "." + debuglevel + " " + server + " :" + comments + "" + std::string("\r\n")


	# define RPL_ENDOFWHO(prefix, name)	std::string(":") + 	prefix + " " + "315 " + "" + name + " :End of /WHO list" + std::string("\r\n")


	# define RPL_ENDOFNAMES(prefix, channel)	std::string(":") + 	prefix + " " + "366 " + "" + channel + " :End of /NAMES list" + std::string("\r\n")


	# define RPL_LINKS(prefix, mask, server, hopcount, server_info)	std::string(":") + 	prefix + " " + "364 " + "" + mask + " " + server + " :" + hopcount + " " + server_info + "" + std::string("\r\n")


	# define RPL_ENDOFLINKS(prefix, mask)	std::string(":") + 	prefix + " " + "365 " + "" + mask + " :End of /LINKS list" + std::string("\r\n")


	# define RPL_BANLIST(prefix, channel, banid)	std::string(":") + 	prefix + " " + "367 " + "" + channel + " " + banid + "" + std::string("\r\n")


	# define RPL_ENDOFBANLIST(prefix, channel)	std::string(":") + 	prefix + " " + "368 " + "" + channel + " :End of channel ban list" + std::string("\r\n")


	# define RPL_INFO(prefix, string)	std::string(":") + 	prefix + " " + "371 " + ":" + string + "" + std::string("\r\n")


	# define RPL_ENDOFINFO(prefix)	std::string(":") + 	prefix + " " + "374 " + ":End of /INFO list" + std::string("\r\n")


	# define RPL_MOTDSTART(prefix, server)	std::string(":") + 	prefix + " " + "375 " + ":- " + server + " Message of the day -" + std::string("\r\n")


	# define RPL_MOTD(prefix, text)	std::string(":") + 	prefix + " " + "372 " + ":- " + text + "" + std::string("\r\n")


	# define RPL_ENDOFMOTD(prefix)	std::string(":") + 	prefix + " " + "376 " + ":End of /MOTD command" + std::string("\r\n")


	# define RPL_YOUREOPER(prefix)	std::string(":") + 	prefix + " " + "381 " + ":You are now an IRC operator" + std::string("\r\n")


	# define RPL_REHASHING(prefix, config_file)	std::string(":") + 	prefix + " " + "382 " + "" + config_file + " :Rehashing" + std::string("\r\n")


	# define RPL_USERSSTART(prefix)	std::string(":") + 	prefix + " " + "392 " + ":UserID Terminal Host" + std::string("\r\n")


	# define RPL_USERS(prefix)	std::string(":") + 	prefix + " " + "393 " + ":%-8s %-9s %-8s" + std::string("\r\n")


	# define RPL_ENDOFUSERS(prefix)	std::string(":") + 	prefix + " " + "394 " + ":End of users" + std::string("\r\n")


	# define RPL_NOUSERS(prefix)	std::string(":") + 	prefix + " " + "395 " + ":Nobody logged in" + std::string("\r\n")


	# define RPL_TRACECONNECTING(prefix, class, server)	std::string(":") + 	prefix + " " + "201 " + "Try. " + class + " " + server + "" + std::string("\r\n")


	# define RPL_TRACEHANDSHAKE(prefix, class, server)	std::string(":") + 	prefix + " " + "202 " + "H.S. " + class + " " + server + "" + std::string("\r\n")


	# define RPL_TRACEUNKNOWN(prefix, class, client_IP_address_in_dot_form)	std::string(":") + 	prefix + " " + "203 " + "???? " + class + " [" + client_IP_address_in_dot_form + "]" + std::string("\r\n")


	# define RPL_TRACEOPERATOR(prefix, class, nick)	std::string(":") + 	prefix + " " + "204 " + "Oper " + class + " " + nick + "" + std::string("\r\n")


	# define RPL_TRACEUSER(prefix, class, nick)	std::string(":") + 	prefix + " " + "205 " + "User " + class + " " + nick + "" + std::string("\r\n")


	# define RPL_TRACENEWTYPE(prefix, newtype, client_name)	std::string(":") + 	prefix + " " + "208 " + "" + newtype + " 0 " + client_name + "" + std::string("\r\n")


	# define RPL_TRACELOG(prefix, logfile, debug_level)	std::string(":") + 	prefix + " " + "261 " + "File " + logfile + " " + debug_level + "" + std::string("\r\n")


	# define RPL_STATSCOMMANDS(prefix, command, count)	std::string(":") + 	prefix + " " + "212 " + "" + command + " " + count + "" + std::string("\r\n")


	# define RPL_STATSCLINE(prefix, host, name, port, class)	std::string(":") + 	prefix + " " + "213 " + "C " + host + " * " + name + " " + port + " " + class + "" + std::string("\r\n")


	# define RPL_STATSNLINE(prefix, host, name, port, class)	std::string(":") + 	prefix + " " + "214 " + "N " + host + " * " + name + " " + port + " " + class + "" + std::string("\r\n")


	# define RPL_STATSKLINE(prefix, host, username, port, class)	std::string(":") + 	prefix + " " + "216 " + "K " + host + " * " + username + " " + port + " " + class + "" + std::string("\r\n")


	# define RPL_STATSYLINE(prefix, class, ping_frequency, connect_frequency, max_sendq)	std::string(":") + 	prefix + " " + "218 " + "Y " + class + " " + ping_frequency + " " + connect_frequency + " " + max_sendq + "" + std::string("\r\n")


	# define RPL_ENDOFSTATS(prefix, stats_letter)	std::string(":") + 	prefix + " " + "219 " + "" + stats_letter + " :End of /STATS report" + std::string("\r\n")


	# define RPL_STATSLLINE(prefix, hostmask, servername, maxdepth)	std::string(":") + 	prefix + " " + "241 " + "L " + hostmask + " * " + servername + " " + maxdepth + "" + std::string("\r\n")


	# define RPL_STATSUPTIME(prefix)	std::string(":") + 	prefix + " " + "242 " + ":Server Up %d days %d:%02d:%02d" + std::string("\r\n")


	# define RPL_STATSOLINE(prefix, hostmask, name)	std::string(":") + 	prefix + " " + "243 " + "O " + hostmask + " * " + name + "" + std::string("\r\n")


	# define RPL_STATSHLINE(prefix, hostmask, servername)	std::string(":") + 	prefix + " " + "244 " + "H " + hostmask + " * " + servername + "" + std::string("\r\n")


	# define RPL_UMODEIS(prefix, user_mode_string)	std::string(":") + 	prefix + " " + "221 " + "" + user_mode_string + "" + std::string("\r\n")


	# define RPL_LUSEROP(prefix, integer)	std::string(":") + 	prefix + " " + "252 " + "" + integer + " :operator(s) online" + std::string("\r\n")


	# define RPL_LUSERUNKNOWN(prefix, integer)	std::string(":") + 	prefix + " " + "253 " + "" + integer + " :unknown connection(s)" + std::string("\r\n")


	# define RPL_LUSERCHANNELS(prefix, integer)	std::string(":") + 	prefix + " " + "254 " + "" + integer + " :channels formed" + std::string("\r\n")


	# define RPL_ADMINME(prefix, server)	std::string(":") + 	prefix + " " + "256 " + "" + server + " :Administrative info" + std::string("\r\n")


	# define RPL_ADMINLOC1(prefix, admin_info)	std::string(":") + 	prefix + " " + "257 " + ":" + admin_info + "" + std::string("\r\n")


	# define RPL_ADMINLOC2(prefix, admin_info)	std::string(":") + 	prefix + " " + "258 " + ":" + admin_info + "" + std::string("\r\n")


	# define RPL_ADMINEMAIL(prefix, admin_info)	std::string(":") + 	prefix + " " + "259 " + ":" + admin_info + "" + std::string("\r\n")
