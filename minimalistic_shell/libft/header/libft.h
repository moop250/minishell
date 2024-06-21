/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:55:47 by pberset           #+#    #+#             */
/*   Updated: 2024/05/27 13:49:49 by pberset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

// Converts an int into a string
char	*ft_itoa(int n);
// Returns the substring of char *s from int start of size_t len
char	*ft_substr(char const *s, unsigned int start, size_t len);
// Finds the first occurence of int c (char) in char *s. 
// //Returns the pointer to that occurrence.
char	*ft_strchr(const char *s, int c);
// Returns a new pointer that is a duplicate of char *s1
char	*ft_strdup(const char *s1);
// Returns a new string that is a concatenation of char *s1 and char *s2
char	*ft_strjoin(char const *s1, char const *s2);
// Applies the function 'f(int, char)' to each char of char *s 
// and passing its index as first argument to create a new string
// resulting from successive applications of 'f'
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
// Finds char *needle into char *haystack whithin size_t len char. 
// Returns the start occurence of needle in haystack or NULL if no match found
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
// Finds the last occurence of int c (char) in char *s. 
// Returns the pointer to that occurrence
char	*ft_strrchr(const char *s, int c);
// Returns a copy of char *s1 with the char specified in char *set 
// removed from the beginning and the end of s1
char	*ft_strtrim(char const *s1, char const *set);
// Returns a char **table containing splits of char *s 
// according to the separator char c.
char	**ft_split(char const *s, char c);
// Returns the int converted value of char *str. 
// Ignores all space(3) from the beginning of *str 
// and applies the first +/- sign found. 
int		ft_atoi(const char *str);
// Returns 1 if int c is a char digit or letter. Otherwise 0
int		ft_isalnum(int c);
// Returns 1 if int c is a letter. Otherwise 0
int		ft_isalpha(int c);
// returns 1 if int c is an ascii char (0 to 127). Otherwise 0
int		ft_isascii(int c);
// Returns 1 if int c is a digit ('0' to '9'). Otherwise 0
int		ft_isdigit(int c);
// Returns 1 if int c is printable (from 32 to 126). Otherwise 0
int		ft_isprint(int c);
// Compares void *s1 and void *s2 whithin size_t n 
// and returns the difference of the first mismatch. 
// + if s1 is bigger, Otherwise -
int		ft_memcmp(const void *s1, const void *s2, size_t n);
// Compares int *i1 and int *i2 
// and returns the difference of the mismatch. 
// + if s1 is bigger, Otherwise -
int		ft_memcmp_i(const int *i1, const int *i2);
// Computes the power of 10 of int pow
int		ft_pow10(int pow);
// Compares char *s1 and char *s2 whithin size_t n 
// and returns the difference of the first mismatch. 
// 0 < if s1 is bigger, 0 > otherwise
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// Changes int c from uppercase to lowercase
int		ft_tolower(int c);
// Changes int c from lowercase to uppercase
int		ft_toupper(int c);
// Writes char c into file descriptor int fd
int		ft_putchar_fd(char c, int fd);
// Writes char *s into file descriptor int fd with a newline
int		ft_putendl_fd(char *s, int fd);
// Writes char *s into the STDERR_FILENO error output
int		ft_puterr_fd(char *s);
// Writes int n into file descriptor int fd
int		ft_putnbr_fd(int n, int fd);
// Writes unsigned int n into file descriptor int fd | max 4294967295
//int		ft_putuint_fd(unsigned int n, int fd);
// Writes lowercase (0) or uppercase (1) hexadecimal conversion of int
//int		ft_puthex_fd(int n, int case, int fd);
// Writes char *s into file descriptor int fd
int		ft_putstr_fd(char *s, int fd);
// Returns the length of char *s
size_t	ft_strlen(const char *s);
// Concatenates size_t dstsize char from char *src into char *dst 
// and returns the length of the NULL terminated string it tried to create. 
// Success result should be equal to ft_strlen(dst) + ft_strlen(src)
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
// Copies size_t dstsize char from char *src into char *dst 
// and returns the length of the NULL terminated string it tried to create. 
// Success result should be equal to ft_strlen(dst) + ft_strlen(src)
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
// Fills size_t n of void *s with '\0'
void	ft_bzero(void *s, size_t n);
// Applie the function 'f(int, char*)' to char *s passing 
// its index as first argument. Each char is passed by address 
// to be modified if necessary
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// Allocates memory of size_t size for size_t count elements. 
// Returns NULL pointer if size || count == 0
void	*ft_calloc(size_t count, size_t size);
// Frees a tab of strings
void	ft_free_tab(char **tab);
// Frees a tab of int
void	ft_free_int_tab(int **tab, size_t size);
// Returns the index of void *s that matches int c (char) whithin size_t n
void	*ft_memchr(const void *s, int c, size_t n);
// Copies size_t n elements from void *src into void *dst
void	*ft_memcpy(void *dst, const void *src, size_t n);
// Copies size_t len elements from void *src into void *dst. 
// Memory ovelap is handled
void	*ft_memmove(void *dst, const void *src, size_t len);
// Sets size_t len elements of void *b with int c
void	*ft_memset(void *b, int c, size_t len);

// content: the data contained in the node. 
// void * allows to store any type of data
//next: the address of the next node or NULL if next is the last one
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;
// Allocates and returns a new node. 
// The member "content" is initialized with the value of void *content. 
// The member "next" is initialized to NULL
t_list	*ft_lstnew(void *content);
// Adds t_list *new at the begining of t_list **lst
void	ft_lstadd_front(t_list **lst, t_list *new);
// Returns the number of nodes in t_list *lst
int		ft_lstsize(t_list *lst);
// Returns the last node of t_list *lst
t_list	*ft_lstlast(t_list *lst);
// Adds t_list *new at the end of t_list **lst
void	ft_lstadd_back(t_list **lst, t_list *new);
// Takes a t_list *lst node of the list, clears the content 
// with void (*del)(void *)) and frees the node
void	ft_lstdelone(t_list *lst, void (*del)(void *));
// Deletes and frees the given node and all of its successors. 
// The pointer to the list is set to NULL
void	ft_lstclear(t_list **lst, void (*del)(void *));
// Iterates the t_list **lst and applies void (*f)(void *) 
// to the content of each node
void	ft_lstiter(t_list *lst, void (*f)(void *));
// Iterates the t_list *lst and applies void *(*f)(void *) 
// to each elements of the list. Returns a new list resulting 
// of the iterations of f on lst or NULL if allocation fails. 
// void (*del)(void *) is used to delete the content of a node as need be
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
#endif
