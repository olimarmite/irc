
#include <sstream>
#include <string>
struct IrcMessage
	{
		const int code;
		const std::string message_template;
		const std::string description;
		const std::string message;

		IrcMessage(const int code, const std::string message_template, const std::string description, const std::string message) :
			code(code),
			message_template(message_template),
			description(description),
			message(message)
		{
		}


		const std::string get_full_message(const std::string user, const std::string prefix) const
		{
			std::stringstream ss;

			ss << prefix << " " << code << " " << user << " " << message << "\r\n";
			return ss.str();
		}

		static IrcMessage ERR_NOSUCHNICK(const std::string nickname)

		{
			return IrcMessage(
			401,
			"<nickname> :No such nick/channel",
			"Used to indicate the nickname parameter supplied to a command is currently unused.",
			std::string("") + "" + nickname + " :No such nick/channel"
			);
		}


		static IrcMessage ERR_NOSUCHSERVER(const std::string server_name)

		{
			return IrcMessage(
			402,
			"<server name> :No such server",
			"Used to indicate the server name given currently doesn't exist.",
			std::string("") + "" + server_name + " :No such server"
			);
		}


		static IrcMessage ERR_NOSUCHCHANNEL(const std::string channel_name)

		{
			return IrcMessage(
			403,
			"<channel name> :No such channel",
			"Used to indicate the given channel name is invalid.",
			std::string("") + "" + channel_name + " :No such channel"
			);
		}


		static IrcMessage ERR_CANNOTSENDTOCHAN(const std::string channel_name)

		{
			return IrcMessage(
			404,
			"<channel name> :Cannot send to channel",
			"Sent to a user who is either (a) not on a channel which is mode +n or (b) not a chanop (or mode +v) on a channel which has mode +m set and is trying to send a PRIVMSG message to that channel.",
			std::string("") + "" + channel_name + " :Cannot send to channel"
			);
		}


		static IrcMessage ERR_TOOMANYCHANNELS(const std::string channel_name)

		{
			return IrcMessage(
			405,
			"<channel name> :You have joined too many channels",
			"Sent to a user when they have joined the maximum number of allowed channels and they try to join another channel.",
			std::string("") + "" + channel_name + " :You have joined too many channels"
			);
		}


		static IrcMessage ERR_WASNOSUCHNICK(const std::string nickname)

		{
			return IrcMessage(
			406,
			"<nickname> :There was no such nickname",
			"Returned by WHOWAS to indicate there is no history information for that nickname.",
			std::string("") + "" + nickname + " :There was no such nickname"
			);
		}


		static IrcMessage ERR_TOOMANYTARGETS(const std::string target)

		{
			return IrcMessage(
			407,
			"<target> :Duplicate recipients. No message delivered",
			"Returned to a client which is attempting to send PRIVMSG/NOTICE using the user@host destination format and for a user@host which has several occurrences.",
			std::string("") + "" + target + " :Duplicate recipients. No message delivered"
			);
		}


		static IrcMessage ERR_NOORIGIN()

		{
			return IrcMessage(
			409,
			":No origin specified",
			"PING or PONG message missing the originator parameter which is required since these commands must work without valid prefixes.",
			std::string("") + ":No origin specified"
			);
		}


		static IrcMessage ERR_NORECIPIENT(const std::string command)

		{
			return IrcMessage(
			411,
			":No recipient given (<command>)",
			"n/a",
			std::string("") + ":No recipient given (" + command + ")"
			);
		}


		static IrcMessage ERR_NOTEXTTOSEND()

		{
			return IrcMessage(
			412,
			":No text to send",
			"412 - 414 are returned by PRIVMSG to indicate that the message wasn't delivered for some reason.",
			std::string("") + ":No text to send"
			);
		}


		static IrcMessage ERR_NOTTOPLEVEL(const std::string mask)

		{
			return IrcMessage(
			413,
			"<mask> :No toplevel domain specified",
			"412 - 414 are returned by PRIVMSG to indicate that the message wasn't delivered for some reason. ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that are returned when an invalid use of \"PRIVMSG $<server>\" or \"PRIVMSG #<host>\" is attempted.",
			std::string("") + "" + mask + " :No toplevel domain specified"
			);
		}


		static IrcMessage ERR_WILDTOPLEVEL(const std::string mask)

		{
			return IrcMessage(
			414,
			"<mask> :Wildcard in toplevel domain",
			"412 - 414 are returned by PRIVMSG to indicate that the message wasn't delivered for some reason. ERR_NOTOPLEVEL and ERR_WILDTOPLEVEL are errors that are returned when an invalid use of \"PRIVMSG $<server>\" or \"PRIVMSG #<host>\" is attempted.",
			std::string("") + "" + mask + " :Wildcard in toplevel domain"
			);
		}


		static IrcMessage ERR_UNKNOWNCOMMAND(const std::string command)

		{
			return IrcMessage(
			421,
			"<command> :Unknown command",
			"Returned to a registered client to indicate that the command sent is unknown by the server.",
			std::string("") + "" + command + " :Unknown command"
			);
		}


		static IrcMessage ERR_NOMOTD()

		{
			return IrcMessage(
			422,
			":MOTD File is missing",
			"Server's MOTD file could not be opened by the server.",
			std::string("") + ":MOTD File is missing"
			);
		}


		static IrcMessage ERR_NOADMININFO(const std::string server)

		{
			return IrcMessage(
			423,
			"<server> :No administrative info available",
			"Returned by a server in response to an ADMIN message when there is an error in finding the appropriate information.",
			std::string("") + "" + server + " :No administrative info available"
			);
		}


		static IrcMessage ERR_FILEERROR(const std::string file_op, const std::string file)

		{
			return IrcMessage(
			424,
			":File error doing <file op> on <file>",
			"Generic error message used to report a failed file operation during the processing of a message.",
			std::string("") + ":File error doing " + file_op + " on " + file + ""
			);
		}


		static IrcMessage ERR_NONICKNAMEGIVEN()

		{
			return IrcMessage(
			431,
			":No nickname given",
			"Returned when a nickname parameter expected for a command and isn't found.",
			std::string("") + ":No nickname given"
			);
		}


		static IrcMessage ERR_ERRONEUSNICKNAME(const std::string nick)

		{
			return IrcMessage(
			432,
			"<nick> :Erroneus nickname",
			"Returned after receiving a NICK message which contains characters which do not fall in the defined set. See section x.x.x for details on valid nicknames.",
			std::string("") + "" + nick + " :Erroneus nickname"
			);
		}


		static IrcMessage ERR_NICKNAMEINUSE(const std::string nick)

		{
			return IrcMessage(
			433,
			"<nick> :Nickname is already in use",
			"Returned when a NICK message is processed that results in an attempt to change to a currently existing nickname.",
			std::string("") + "" + nick + " :Nickname is already in use"
			);
		}


		static IrcMessage ERR_NICKCOLLISION(const std::string nick)

		{
			return IrcMessage(
			436,
			"<nick> :Nickname collision KILL",
			"Returned by a server to a client when it detects a nickname collision (registered of a NICK that already exists by another server).",
			std::string("") + "" + nick + " :Nickname collision KILL"
			);
		}


		static IrcMessage ERR_USERNOTINCHANNEL(const std::string nick, const std::string channel)

		{
			return IrcMessage(
			441,
			"<nick> <channel> :They aren't on that channel",
			"Returned by the server to indicate that the target user of the command is not on the given channel.",
			std::string("") + "" + nick + " " + channel + " :They aren't on that channel"
			);
		}


		static IrcMessage ERR_NOTONCHANNEL(const std::string channel)

		{
			return IrcMessage(
			442,
			"<channel> :You're not on that channel",
			"Returned by the server whenever a client tries to perform a channel effecting command for which the client isn't a member.",
			std::string("") + "" + channel + " :You're not on that channel"
			);
		}


		static IrcMessage ERR_USERONCHANNEL(const std::string user, const std::string channel)

		{
			return IrcMessage(
			443,
			"<user> <channel> :is already on channel",
			"Returned when a client tries to invite a user to a channel they are already on.",
			std::string("") + "" + user + " " + channel + " :is already on channel"
			);
		}


		static IrcMessage ERR_NOLOGIN(const std::string user)

		{
			return IrcMessage(
			444,
			"<user> :User not logged in",
			"Returned by the summon after a SUMMON command for a user was unable to be performed since they were not logged in.",
			std::string("") + "" + user + " :User not logged in"
			);
		}


		static IrcMessage ERR_SUMMONDISABLED()

		{
			return IrcMessage(
			445,
			":SUMMON has been disabled",
			"Returned as a response to the SUMMON command. Must be returned by any server which does not implement it.",
			std::string("") + ":SUMMON has been disabled"
			);
		}


		static IrcMessage ERR_USERSDISABLED()

		{
			return IrcMessage(
			446,
			":USERS has been disabled",
			"Returned as a response to the USERS command. Must be returned by any server which does not implement it.",
			std::string("") + ":USERS has been disabled"
			);
		}


		static IrcMessage ERR_NOTREGISTERED()

		{
			return IrcMessage(
			451,
			":You have not registered",
			"Returned by the server to indicate that the client must be registered before the server will allow it to be parsed in detail.",
			std::string("") + ":You have not registered"
			);
		}


		static IrcMessage ERR_NEEDMOREPARAMS(const std::string command)

		{
			return IrcMessage(
			461,
			"<command> :Not enough parameters",
			"Returned by the server by numerous commands to indicate to the client that it didn't supply enough parameters.",
			std::string("") + "" + command + " :Not enough parameters"
			);
		}


		static IrcMessage ERR_ALREADYREGISTRED()

		{
			return IrcMessage(
			462,
			":You may not reregister",
			"Returned by the server to any link which tries to change part of the registered details (such as password or user details from second USER message).",
			std::string("") + ":You may not reregister"
			);
		}


		static IrcMessage ERR_NOPERMFORHOST()

		{
			return IrcMessage(
			463,
			":Your host isn't among the privileged",
			"Returned to a client which attempts to register with a server which does not been setup to allow connections from the host the attempted connection is tried.",
			std::string("") + ":Your host isn't among the privileged"
			);
		}


		static IrcMessage ERR_PASSWDMISMATCH()

		{
			return IrcMessage(
			464,
			":Password incorrect",
			"Returned to indicate a failed attempt at registering a connection for which a password was required and was either not given or incorrect.",
			std::string("") + ":Password incorrect"
			);
		}


		static IrcMessage ERR_YOUREBANNEDCREEP()

		{
			return IrcMessage(
			465,
			":You are banned from this server",
			"Returned after an attempt to connect and register yourself with a server which has been setup to explicitly deny connections to you.",
			std::string("") + ":You are banned from this server"
			);
		}


		static IrcMessage ERR_KEYSET(const std::string channel)

		{
			return IrcMessage(
			467,
			"<channel> :Channel key already set",
			"n/a",
			std::string("") + "" + channel + " :Channel key already set"
			);
		}


		static IrcMessage ERR_CHANNELISFULL(const std::string channel)

		{
			return IrcMessage(
			471,
			"<channel> :Cannot join channel (+l)",
			"n/a",
			std::string("") + "" + channel + " :Cannot join channel (+l)"
			);
		}


		static IrcMessage ERR_UNKNOWNMODE(const std::string _char)

		{
			return IrcMessage(
			472,
			"<char> :is unknown mode char to me",
			"n/a",
			std::string("") + "" + _char + " :is unknown mode char to me"
			);
		}


		static IrcMessage ERR_INVITEONLYCHAN(const std::string channel)

		{
			return IrcMessage(
			473,
			"<channel> :Cannot join channel (+i)",
			"n/a",
			std::string("") + "" + channel + " :Cannot join channel (+i)"
			);
		}


		static IrcMessage ERR_BANNEDFROMCHAN(const std::string channel)

		{
			return IrcMessage(
			474,
			"<channel> :Cannot join channel (+b)",
			"n/a",
			std::string("") + "" + channel + " :Cannot join channel (+b)"
			);
		}


		static IrcMessage ERR_BADCHANNELKEY(const std::string channel)

		{
			return IrcMessage(
			475,
			"<channel> :Cannot join channel (+k)",
			"n/a",
			std::string("") + "" + channel + " :Cannot join channel (+k)"
			);
		}


		static IrcMessage ERR_NOPRIVILEGES()

		{
			return IrcMessage(
			481,
			":Permission Denied- You're not an IRC operator",
			"Any command requiring operator privileges to operate must return this error to indicate the attempt was unsuccessful.",
			std::string("") + ":Permission Denied- You're not an IRC operator"
			);
		}


		static IrcMessage ERR_CHANOPRIVSNEEDED(const std::string channel)

		{
			return IrcMessage(
			482,
			"<channel> :You're not channel operator",
			"Any command requiring 'chanop' privileges (such as MODE messages) must return this error if the client making the attempt is not a chanop on the specified channel.",
			std::string("") + "" + channel + " :You're not channel operator"
			);
		}


		static IrcMessage ERR_CANTKILLSERVER()

		{
			return IrcMessage(
			483,
			":You cant kill a server!",
			"Any attempts to use the KILL command on a server are to be refused and this error returned directly to the client.",
			std::string("") + ":You cant kill a server!"
			);
		}


		static IrcMessage ERR_NOOPERHOST()

		{
			return IrcMessage(
			491,
			":No O-lines for your host",
			"If a client sends an OPER message and the server has not been configured to allow connections from the client's host as an operator, this error must be returned.",
			std::string("") + ":No O-lines for your host"
			);
		}


		static IrcMessage ERR_UMODEUNKNOWNFLAG()

		{
			return IrcMessage(
			501,
			":Unknown MODE flag",
			"Returned by the server to indicate that a MODE message was sent with a nickname parameter and that the a mode flag sent was not recognized.",
			std::string("") + ":Unknown MODE flag"
			);
		}


		static IrcMessage ERR_USERSDONTMATCH()

		{
			return IrcMessage(
			502,
			":Cant change mode for other users",
			"Error sent to any user trying to view or change the user mode for a user other than themselves.",
			std::string("") + ":Cant change mode for other users"
			);
		}

	};

