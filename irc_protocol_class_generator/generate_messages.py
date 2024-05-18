import yaml
import json
with open('IRC_messages.yaml', 'r') as file:
		prime_service = yaml.safe_load(file)


# json.dump(prime_service, open('IRC_messages.json', 'w'), indent=4)


ERROR_REPLIES = prime_service['ERROR_REPLIES']
COMMAND_RESPONSES = prime_service['COMMAND_RESPONSES']
RESERVED_NUMERAL = prime_service['RESERVED_NUMERALS']



# File error doing <file op> on <file> (Generic error message used to report a failed file operation during the processing of a message.
def extract_reply_arguments(reply):
	argmuments_list = []

	start = -1
	end = -1
	for i in range(len(reply)):
		if reply[i] == '<' and start == -1:
			start = i
		if reply[i] == '>' and start != -1:
			end = i
			argmuments_list.append(reply[start:end +1])
			start = -1
	return argmuments_list

def generate_error_replies():
	for error_code in ERROR_REPLIES:
		error_data = ERROR_REPLIES[error_code]
		error_name = error_data['name']
		error_reply = error_data['reply']
		error_description = error_data['desc']
		# print(f"{error_code} {error_name} : {error_reply} ({error_description})")
		print(f"#define IRC_{error_name} {error_code}")
		print(error_reply)
		print(extract_reply_arguments(error_reply))


# generate_error_replies()

# print(extract_reply_arguments("File error doing <file op> on <file>"))

# '''
# std::string reply_ERR_CHANOPRIVSNEEDED(std::string argmument_1, std::string argmument_2) {

# }



"""
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
"""

def convert_arg_to_cpp(arg):
	arg_cp = arg
	arg_cp = arg_cp.replace("<", "")
	arg_cp = arg_cp.replace(">", "")
	arg_cp = arg_cp.replace(" ", "_")

	return arg_cp


# def generate_irc_message_class(code, message_template, description, argmuments_list):

# 	message_constructor = '"' + message_template + '"'
# 	constructor_args = ", ".join(["const std::string " + convert_arg_to_cpp(argmuments_list[i]) for i in range(len(argmuments_list))])

# 	for i in range(len(argmuments_list)):
# 		message_constructor = message_constructor.replace(argmuments_list[i], f'" + {convert_arg_to_cpp(argmuments_list[i])} + "')

# 	class_code = """
# 	struct IrcMessage
# 	{
# 		const int code;
# 		const std::string message_template;
# 		const std::string description;
# 		const std::string message;
# 	""" + f"""
# 		IrcMessage({constructor_args}) :
# 			code({code}),
# 			message_template({message_template}),
# 			description({description}),
# 			message(std::string("") + {message_constructor})
# 	""" + """
# 		{
# 		}
# 	};
# 	"""
# 	print(class_code)



# def generate_irc_message_class(code, name,  message_template, description, argmuments_list):

# 	message_constructor = '"' + message_template + '"'
# 	constructor_args = ", ".join(["const std::string " + convert_arg_to_cpp(argmuments_list[i]) for i in range(len(argmuments_list))])

# 	for i in range(len(argmuments_list)):
# 		message_constructor = message_constructor.replace(argmuments_list[i], f'" + {convert_arg_to_cpp(argmuments_list[i])} + "')

# 	formated_name = name.upper().replace(" ", "_")
# 	class_code = """
# 	struct IrcMessage
# 	{
# 		const int code;
# 		const std::string message_template;
# 		const std::string description;
# 		const std::string message;

# 		IrcMessage(const int code, const std::string message_template, const std::string description, const std::string message) :
# 			code(code),
# 			message_template(message_template),
# 			description(description),
# 			message(message)
# 		{
# 		}

# 	""" + f"""
# 		static IrcMessage {formated_name}({constructor_args})
# 	""" + """
# 		{
# 			return IrcMessage(
# 			code({code}),
# 			message_template({message_template}),
# 			description({description}),
# 			message(std::string("") + {message_constructor})
# 			);
# 		}
# 	};
# 	"""
# 	print(class_code)



def generate_irc_message_class(code, name,  message_template, description, argmuments_list):

	message_constructor = '"' + message_template + '"'
	constructor_args = ", ".join(["prefix"] + [convert_arg_to_cpp(argmuments_list[i]) for i in range(len(argmuments_list))])

	for i in range(len(argmuments_list)):
		message_constructor = message_constructor.replace(argmuments_list[i], f'" + {convert_arg_to_cpp(argmuments_list[i])} + "')

	formated_name = name.upper().replace(" ", "_")
	description =  description.replace('\n', '').replace('\"', '\\"')
	# class_code = f"""
	# 	static IrcMessage {formated_name}({constructor_args})
	# """ + """
	# 	{""" + f"""
	# 		return IrcMessage(
	# 		{code},
	# 		"{message_template}",
	# 		"{description}",
	# 		std::string("") + {message_constructor}
	# 		);""" + """
	# 	}
	# """
	class_code = f"""
	# define {formated_name}({constructor_args})	std::string(":") + \
	prefix + " " + "{code} " + {message_constructor} + std::string("\\r\\n")
	"""
	# print(class_code)
	return class_code

# generate_irc_message_class(404, "test_error", "File error doing <file op> on <file>", "Generic error message used to report a failed file operation during the processing of a message.", ["<file op>", "<file>"])


all_named_constructors = []

for error_code in ERROR_REPLIES:
	error_data = ERROR_REPLIES[error_code]
	error_name = error_data['name']
	error_reply = error_data['reply']
	error_description = error_data['desc']
	argmuments_list = extract_reply_arguments(error_reply)

	# generate_irc_message_class(error_code, error_name, error_reply, error_description, argmuments_list)
	all_named_constructors.append(generate_irc_message_class(error_code, error_name, error_reply, error_description, argmuments_list))

# print("\n".join(all_named_constructors))

for command in COMMAND_RESPONSES:
	command_data = COMMAND_RESPONSES[command]
	command_name = command_data['name']
	command_reply = command_data['reply']
	command_description = command_data['desc']
	argmuments_list = extract_reply_arguments(command_reply)

	# generate_irc_message_class(command, command_name, command_reply, command_description, argmuments_list)
	all_named_constructors.append(generate_irc_message_class(command, command_name, command_reply, command_description, argmuments_list))


# full_class_code = """
# 	struct IrcMessage
# 	{
# 		const int code;
# 		const std::string message_template;
# 		const std::string description;
# 		const std::string message;

# 		IrcMessage(const int code, const std::string message_template, const std::string description, const std::string message) :
# 			code(code),
# 			message_template(message_template),
# 			description(description),
# 			message(message)
# 		{
# 		}

# 	"""
full_class_code = ""
full_class_code += "\n".join(all_named_constructors)
# full_class_code += """
# 	};
# 	"""
print(full_class_code)


# # define NICK_CHANGED(old_nick, username, new_nick)	std::string(":") + \
# 	old_nick + "!~" + username + "@127.0.0.1 NICK :" + new_nick + std::string("\n")
