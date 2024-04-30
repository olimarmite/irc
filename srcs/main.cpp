#include "../includes/Server.hpp"
#include "../includes/Macros.hpp"
#include "../includes/utils.hpp"

int main(int argc, char **argv)
{
	if (is_arg_valid(argc, argv) == false)
		return EXIT_FAILURE;

	//TODO: signals handler (check what signals)

	std::string	port = argv[1];
	std::string	password = argv[2];

	try
	{
		Server		server(port, password);

		server.launch();
		while (true)
		{
			server.run();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return EXIT_SUCCESS;
}