/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 18:39:07 by qbarron           #+#    #+#             */
/*   Updated: 2023/12/31 18:39:07 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "utils.c"

char *get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;
	int				readed;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, &line, 0) < 0)
		return(NULL);
	readed = 1;
	line = NULL;
	// 1. lire le fichier et ajouter a la liste chainee les characteres
	read_and_stash(fd, &stash, &readed);
	if (stash == NULL)
		return (NULL);
	// 2. extraire la stash dans la variable line
	extract_line(stash, &line);
	// 3. nettoyer la stash pour le prochain appel de gnl
	clean_stash(&stash);
	//condition pour identifer quand on a deja finit de lire un fichier
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);	
	}
}

void read_and_stash(int fd, t_list **stash, int *readed_ptr)
{
	char	*buf;

	while (!find_new_line(&stash) && *readed_ptr != 0)  				//si egale a zero il n'y a rien a lire
	{
		buf = malloc(sizeof(char) + BUFFER_SIZE + 1);					//on malloc le buffer pour prendre la taille souhaiter du BUFFER
		if (buf == NULL)
			return;
		readed_ptr = (int)read (fd, buf, BUFFER_SIZE);					//on dit au pointeur de copier le fichier a longeur du BS
		if ((*stash == NULL && *readed_ptr == 0) || *readed_ptr == -1)
		{
			free(buf);
			return;
		}
		buf[*readed_ptr] = '\0'; 										//ferme la chaine de charactere par \0 apres le buffer size
		add_to_stash(stash, buf, *read_ptr);
		free (buf);														//on free dans la boucle pour que le buf soit free a chaque fois qu'il y a un nouveau read
	}
}

void add_to_stash(t_list **stash, char *buf, int readed)
{
	int	i;
	t_list	*last;												//le dernier node de la stash
	t_list	*new_node;											//pour ajouter a la fin de la liste, on doit ajouter un new node

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;										//il n'y a pas de prochain maillon de chaine grace au NULL
	new_node->content = malloc(sizeof(char) * (readed + 1)); 	//on alloue de la memoire au contenue du dernier maillon = la stash
	if (new_node->content == NULL)
		return ;
	i = -1;
	while (buf[++i] && i < readed)								//tant qu'il y a quelque chose dans le buf et qu'il y a toujours quelque chose a lire dans readed
		new_node->content[i] = buf[i];  						//on met le contenue du buffer dans le content de la new node.
	new_node->content[i] = '\0';								//on ferme la node par un charactere de fin de ligne
	if (*stash == NULL)											//s'il n'y a rien dans la stash
	{
		*stash = new_node;										//on met dans la stash le contenue de new_node (cf le contenue du buf)
		return ;
	}
	last = ft_lst_get_last(stash);								//sinon, on remplit le dernier element de la stash dans le dernier content de la stash.
	last->next = new_node;										//le node suivant last est remplit par new_node
}

//extrait tous les characteres de la stash et les stocks das la out line,
//s'arretant apres le premier \n qu'il rencontre
void extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);					//attribue de la memoire
	if (*line == NULL)							//on place le checker de memoire ici au lieu de dans generate_line car la modification de la line se fait dans cette fonction ci. Dans generate_line, //on ne fait qu'allouer de la memoire, on ne travaille pas directement sur son content
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] == stash->content[i];
				break;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

//calcule le nombre de char dans la ligne actuelle
// inclu \n s'il y en a un, et alloue la memoire en fonction

void generate_line(char **line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content == '\n') //si le character actuel est un \n
			{
				len++;					//augmente la taille de la ligne
				break;					//et sort de la boucle
			}
			len++;						//sinon compte le charactere dans la taille
			i++;						//et incremente la boucle
		}
		stash = stash->next;			//on incremente la liste
	}
	*line = malloc(sizeof(char) * (len + 1));
}
