#include "../minishell.h"

char	*get_input(void)
{
	char	*input;

	if (isatty(0))
	{
		if (!isatty(2))
			input = readline("");
		else if (g_exit_status == 0)
			input = readline(PROMPT_OK);
		else
			input = readline(PROMPT_KO);
		if (input && input[0] != 0)
			add_history(input);
	}
	else
	{
		input = get_next_line(0);
		if (input && input[ft_strlen(input) - 1] == '\n')
			input[ft_strlen(input) - 1] = 0;
	}
	return (input);
}
