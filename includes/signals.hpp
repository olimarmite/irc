#pragma once

#include "Macros.hpp"

#include <csignal>
// #include <iostream>

int		set_signals(void);
void	sigint_handler(int signal);
