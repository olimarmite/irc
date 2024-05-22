#include "../../includes/signals.hpp"
#include "../../includes/Macros.hpp"

bool g_signals;

int	set_signals(void)
{
	g_signals = true;
	struct sigaction	signal;

	memset(&signal, 0, sizeof(signal));
	signal.sa_flags = SA_SIGINFO | SA_RESTART;
	signal.sa_handler = &signals_handler;
	if (sigaction(SIGINT, &signal, NULL) == -1 || sigaction(SIGQUIT, &signal, NULL) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* void	signal_handler(int signal, \
siginfo_t *info, void *ucontext) */
void	signals_handler(int signal)
{
	(void)signal;
	g_signals = false;
}