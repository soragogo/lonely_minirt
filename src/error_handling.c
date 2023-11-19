#include "../includes/minirt.h"

void ft_error(char *log)
{
    ft_putstr_fd("Error\n", STDERR_FILENO);
    ft_putstr_fd(log, STDERR_FILENO);
    exit (EXIT_FAILURE);
}
