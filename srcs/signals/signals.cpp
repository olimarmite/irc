#include "../../includes/signals.hpp"
#include "../../includes/Macros.hpp"

bool g_signals;

int	set_signals(void)
{
	g_signals = true;
	struct sigaction	signal;

	memset(&signal, 0, sizeof(signal));
	signal.sa_flags = SA_SIGINFO | SA_RESTART;
	signal.sa_handler = &sigint_handler;
	if (sigaction(SIGINT, &signal, NULL) == -1)
		return (EXIT_FAILURE); //verifier
	// signal.sa_handler = SIG_IGN; //TODO : check which signals to ignore
	return (EXIT_SUCCESS);
}

/* void	signal_handler(int signal, \
siginfo_t *info, void *ucontext) */
void	sigint_handler(int signal)
{
	if (DEBUG)
		std::cout <<BCYN <<"in signal handler" <<PRINT_END;
	(void)signal;
	//sortir de la while et faire appel au deconstructeur
	g_signals = false;
/* 	delete[] requests --> attendre nouvelle structure d'olivier 
	puis mettre requests dans une classe et "delete[] requests" 
	dans son deconstructeur. */
}