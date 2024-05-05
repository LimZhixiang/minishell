/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhilim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:15:24 by zhilim            #+#    #+#             */
/*   Updated: 2023/10/06 11:41:37 by zhilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_t_parse(t_parse *ptr)
{
	t_parse	*current;
	t_parse	*next;

	if (ptr == NULL)
		return ;
	current = ptr;
	while (current != NULL)
	{
		next = current->next;
		free(current->arg);
		free(current);
		current = next;
	}
}

void	free_t_env(t_env *ptr)
{
	t_env	*current;
	t_env	*next;

	if (ptr == NULL)
		return ;
	current = ptr;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	ft_free_all(t_mini *mini, int state)
{
	if (state == EXIT_SHELL)
	{
		free_t_env(mini->env);
		free (mini);
		return ;
	}
	free_t_parse(mini->input);
}

char	*ft_var_exp(char *new, t_mini *mini)
{
	int		i;
	int		j;
	char	*name;
	char	*result;

	i = 0;
	while (new[i])
	{
		if (ft_quote(new, i) != 1 && new[i] == '$'
			&& ft_valid_env(new[i + 1]) != 0)
		{
			j = 1;
			while (ft_valid_env(new[i + j]) != 0)
				j++;
			name = ft_substr(new, i, j);
			result = ft_get_env(name, mini);
			new = replace_env(new, result, name, i);
			i = 0;
			free(name);
			free(result);
		}
		else
			i++;
	}
	return (new);
}

int	ft_space_line(char *new, char *line)
{
	int	i;
	int	j;
	int	sep;

	sep = 0;
	i = 0;
	j = 0;
	while (new && line[i])
	{
		sep = is_sep(line[i]);
		if (sep != 0 && ft_quote(line, i) == 0)
		{
			if (i != 0 && line[i - 1] != ' ' && is_sep(line[i - 1]) != sep)
				new[j++] = ' ';
			new[j++] = line[i++];
			if (sep != 1 && is_sep(line[i]) == sep)
				new[j++] = line[i++];
			if (!ft_strchr(" \0", line[i]))
				new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	return (1);
}

char	*malloc_char(int size)
{
	char	*new;

	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	return (new);
}

char	*ft_alloc_space(char *line)
{
	int		i;
	int		space;
	int		sep;

	space = 0;
	i = 0;
	while (line[i])
	{
		sep = is_sep(line[i]);
		if (sep != 0 && ft_quote(line, i) == 0)
		{
			if (i != 0 && !ft_strchr(" ", line[i - 1])
				&& is_sep(line[i - 1]) != sep)
				space++;
			if (sep != 1 && is_sep(line[i + 1]) == sep)
				i++;
			if (!ft_strchr("\0", line[i + 1]))
				space++;
		}
		i++;
	}
	return (malloc_char(i + space));
}

//[START DEL]testing rmb to rm
void	print_input(t_mini *mini)
{
	t_parse	*temp;
	int		i;
	char	*s;

	i = 0;
	temp = mini->input;
	while (temp)
	{
		printf("[Node%i]\n", i++);
		printf("Arg : [%s]\n", temp->arg);
		if (temp->type == 1)
			s = ft_strdup("CMD");
		if (temp->type == 2)
			s = ft_strdup("ARG");
		if (temp->type == 3)
			s = ft_strdup("DELIMITER");
		if (temp->type == 4)
			s = ft_strdup("FILENAME");
		if (temp->type == 5)
			s = ft_strdup("PIPE");
		if (temp->type == 6)
			s = ft_strdup("OUTPUT");
		if (temp->type == 7)
			s = ft_strdup("APPEND");
		if (temp->type == 8)
			s = ft_strdup("INPUT");
		if (temp->type == 9)
			s = ft_strdup("HDOC");
		printf("Type: %s, %i\n", s, temp->type);
		free(s);
		temp = temp->next;
		if (temp)
		{
			printf("   |\n");
			printf("   V\n");
		}
	}
	printf("\n");
}

void	print_input_tgt(t_mini *mini)
{
	t_parse	*temp;
	int		i;

	i = 0;
	temp = mini->input;
	printf("\033[0;32mMINI INPUT: ");
	while (temp)
	{
		if (i == 0)
			printf("[");
		printf("%s", temp->arg);
		if (temp->next)
			printf(" ");
		else
			printf("]\n\033[0m");
		i++;
		temp = temp->next;
	}
	printf("\n");
}
//[END DEL]testing rmb to rm

int	parsing(char *line, t_mini *mini)
{
	char	*new;

	new = ft_alloc_space(line);
	if (new == NULL)
		return (0);
	ft_space_line(new, line);
	if (tokenization(new, mini) == 0)
		return (0);
	ft_rm_quotes(mini);
	//[START DEL]testing rmb to rm
	printf("\033[0;31mMINI->INPUT(AFT PARSING)\n\033[0m");
	print_input(mini);
	printf("USER INPUT: [%s]\n", line);
	print_input_tgt(mini);
	//[START DEL]testing rmb to rm
	return (1);
}
