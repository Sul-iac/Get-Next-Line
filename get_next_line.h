/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:56:50 by qbarron           #+#    #+#             */
/*   Updated: 2024/01/19 14:56:50 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <io.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif

typedef	struct s_list
{
	char			*content;
	struct t_list	*next;
}					t_list;

char	*get_next_line(int fd);
void	read_and_stash(int fd, t_list **stash, int *readed_ptr);
int		found_new_line(t_list stash);
void	add_to_stash(t_list **stash, char *buf, int readed);
t_list	ft_lst_get_last();
void	extract_line(t_list *stash, char **line);
void 	generate_line(char **line, t_list *stash);
void	clean_stash(t_list **stash);
int		ft_strlen(char *str);
void	free_stash(t_list *stash);






#endif
