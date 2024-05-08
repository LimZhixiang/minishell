int	check_valid_export(char *arg)
{
	while (arg[i])
	{
		if (valid_env_name(arg[i]) > 0)
		{
			if (i == 0 && valid_env_name(arg[i]) != 1)
				print_env_error(arg);
			else if
		}
	}
}


int	export(t_mini *mini, char **cmdarg)
{
	int	i;

	i = 1;
	while (cmdarg[i])
	{
		if (!ft_strchr(cmdarg[i], '=') || valid_env_name(cmdarg[i]) > 0)
		{
			i++;
		}
	}
}