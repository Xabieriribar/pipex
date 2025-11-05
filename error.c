#include "pipex.h"

void	ft_fork_error(void)
{
	perror("Fork failed");
	exit(EXIT_FAILURE);
}

void	ft_dup_failed(void)
{
	perror("Dup failed");
	exit(EXIT_FAILURE);
}