#include <iostream>
#include <string>
#define CODE 200
#define MESSAGE_TEMPLATE "Hello, <ARG1>! Your code is <ARG2>."
#define MESSAGE_TEMPLATE_PART1 "Hello, "
#define MESSAGE_TEMPLATE_PART2 "! Your code is "
#define MESSAGE_TEMPLATE_PART3 "."
#define ARG1 "John"
#define ARG2 "successful"
#define DESCRIPTION "This is a sample response message."

struct IrcMessage
{
	const int code;
	const std::string message_template;
	const std::string description;
	const std::string message;

	IrcMessage() :
		code(CODE),
		message_template(MESSAGE_TEMPLATE),
		description(DESCRIPTION),
		message(std::string(MESSAGE_TEMPLATE_PART1) + ARG1 + MESSAGE_TEMPLATE_PART2 + ARG2 + MESSAGE_TEMPLATE_PART3)
	{
	}
};


int main(void)
{
	IrcMessage irc_message;

	(void)irc_message;
	std::cout << irc_message.message << std::endl;
	std::cout << irc_message.description << std::endl;
	std::cout << irc_message.message_template << std::endl;
	std::cout << "Code: " << irc_message.code << std::endl;
	return 0;
}
