#include "../minishell.h"

int	is_op(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '&' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	token_and_reset(char *temp, t_list **token_list, int *i)
{
	temp[*i] = 0;
	if (*i == 0)
		return (-1);
	*i = 0;
	return (tokenization(temp, token_list));
}
