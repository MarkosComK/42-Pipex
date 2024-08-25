/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsoare <marsoare@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:14:18 by marsoare          #+#    #+#             */
/*   Updated: 2024/08/25 01:00:13 by marsoare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*pipex_init(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = malloc(1 * sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->pipefd = NULL;
	pipex->cmd_nb = 0;
	pipex->cmd_start = NULL;
	pipex->path = path_to_llist(envp, pipex);
	pipex->files = file_parser(argc, argv);
	if (!pipex->files)
		return (close_n_free(pipex), NULL);
	pipex->cmd = cmd_parser(argv, pipex);
	if (!pipex->cmd)
		return (close_n_free(pipex), NULL);
	pipex->cmd_start = pipex->cmd;
	pipex->cmd_nb = cmd_lstsize(pipex->cmd_start);
	pipex->exit_code = 0;
	return (pipex);
}

t_files	*file_parser(int argc, char **argv)
{
	t_files	*files;

	files = malloc(1 * sizeof(t_files));
	if (!files)
		return (NULL);
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
	{
		files->inf = NULL;
		files->here_doc = 1;
		files->lim = argv[2];
		files->in_e = 0;
		files->in_r = 0;
	}
	else
	{
		files->inf = argv[1];
		files->here_doc = 0;
		files->in_e = access(argv[1], F_OK);
		files->in_r = access(argv[1], R_OK);
	}
	files->out = argv[argc - 1];
	files->out_e = access(argv[argc -1], F_OK);
	files->out_w = access(argv[argc -1], W_OK);
	open_files(files);
	return (files);
}

void	open_files(t_files *files)
{
	files->out_fd = -1;
	files->in_fd = -1;
	if (!files->here_doc && ((!files->out_e && !files->out_w) || files->out_e))
		files->out_fd = open(files->out, O_TRUNC | O_WRONLY | O_CREAT, 00644);
	if (files->here_doc && ((!files->out_e && !files->out_w) || files->out_e))
		files->out_fd = open(files->out, O_APPEND | O_WRONLY | O_CREAT, 00644);
	files->out_e = access(files->out, F_OK);
	files->out_w = access(files->out, W_OK);
	if (!files->here_doc && !files->in_e && !files->in_r)
		files->in_fd = open(files->inf, O_RDONLY);
	if (files->here_doc)
	{
		files->in_fd = open("/tmp/.here_doc.txt", O_WRONLY | O_CREAT, 00644);
		launch_here_doc(files);
		close(files->in_fd);
		files->in_fd = open("/tmp/.here_doc.txt", O_RDONLY);
	}
}

void	launch_here_doc(t_files *files)
{
	char	*line;
	char	*data;

	data = ft_strdup("");
	if (!data)
		return ;
	while (1)
	{
		ft_fprintf(1, "here_doc > ");
		line = get_next_line(0);
		if (!line)
			return (free(data));
		if (*line == 0)
			break ;
		if (!ft_strncmp(line, files->lim, ft_strlen(files->lim)))
		{
			if (ft_strlen(line) == ft_strlen(files->lim) + 1)
				break ;
		}
		data = str_join_double_free(data, line);
		if (!data)
			return ;
	}
	write(files->in_fd, data, ft_strlen(data));
	return (free(line), free(data));
}

char	*str_join_double_free(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
			res[++j] = s1[i];
	i = -1;
	while (s2[++i])
			res[++j] = s2[i];
	res[++j] = '\0';
	free(s1);
	free(s2);
	return (res);
}

t_list	*path_to_llist(char **envp, t_pipex *pipex)
{
	t_list	*path;
	char	**tmp;

	while (*envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
			break ;
		envp++;
	}
	path = NULL;
	if (*envp)
	{
		tmp = ft_split(ft_strchr(*envp, '=') + 1, ':');
		if (!tmp)
		{
			free(pipex);
			exit(-2);
		}
		path = create_path_list(tmp, pipex);
	}
	return (path);
}

t_list	*create_path_list(char **tmp, t_pipex *pipex)
{
	int		i;
	char	*content;
	t_list	*new;
	t_list	*path;

	i = -1;
	path = NULL;
	while (tmp[++i])
	{
		content = ft_strdup(tmp[i]);
		new = ft_lstnew(content);
		if (!content || !new)
		{
			free(content);
			free(new);
			ft_lstclear(&path, &free);
			free_char_matrix(tmp);
			free(pipex);
			exit(-2);
		}
		ft_lstadd_back(&path, new);
	}
	free_char_matrix(tmp);
	return (path);
}
