#include "get_next_line.h"

// cherche un charactere de nouvelle ligne dans la liste chainee

int found_new_line(t_list *stash)
{
	int 	i;
	t_list *current; 

	if (stash == NULL)					//si stash est vide, tu retournes zero, pas de newline trouvee
		return (0);
	current = ft_lst_get_last(stash);	//appelle la fonction pour definir notre stash sur le dernier chainon de la chaine
	i = 0;
	while(current->content[i])			//tant qu'il y a quelquechose a lire
	{
		if (current->content[i] == '\n')	
			return (1);					//si on trouve le \n, renvoie un
		i++;							//sinon continue d'incrementer
	}
	return (0);
}

//renvoie un pointeur vers le dernier element de la stash
t_list ft_lst_get_last(t_list *stash)
{
	t_list *current;

	current = stash;
	while (current && current->next)
		current = current->next;		// current = dernier maillon
	return (current);				
}

//on veut le dernier chainon de la liste car c'est la que sera la stash finale

int	ft_strlen(char *str)
{
	while (str[i] != '\0')
		i++;
	return (i);
}

//on clean la stash car les characteres extrait de line ne nous servent plus a rien.
//Seulement les characteres non retournes a la fin de gnl() seront conserve dans la static stash
void	clean_stash(t_list **stash)
{
	t_list *list;
	t_list *clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] && last->content[i] == '\n')
		i++;
	clean_node = malloc(sizeof(char) + (st_strlen(last->content) - i) + 1) 		//je veux la longeur de tous les charactere du dernier chainon de la stash, moins les characteres que l'on vient de compter (- i). Il restera donc que les characteres a garder 
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++]; 							//je vais copier dans clean_node tout ce qui est dans le content de la stash qui n'a pas ete envoye
	clean->content[j] = '\0';
	free_stash(*stash);															//on free la stash
	*stash = clean_node;
}

void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}