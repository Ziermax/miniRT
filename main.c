/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:37:21 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/09/18 18:41:33 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define IP 0
#define MASK 1

typedef struct s_interface
{
	int	ip;
	int	mask;
}	t_interface;

void	print_split(char **split)
{
	if (!split)
		return ;
	while (*split)
	{
		printf("%s\n", *split);
		split++;
	}
}

void	print_byte(char	byte)
{
	char	bytes_str[8];
	int		i;

	i = 8;
	while (i-- > 0)
		bytes_str[7 - i] = ((byte >> i) & 1) + '0';
	write(1, bytes_str, 8);
}
	//bytes_str[8] = '\n';

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

char	*check_number_range(char *num, int range)
{
	int	nbr;
	int	i;

	i = 0;
	nbr = 0;
	while (ft_isdigit(num[i]))
	{
		nbr = nbr * 10 + num[i] - '0';
		if (nbr > range || (nbr == 0 && i != 0))
			return (write(2, "Wrong number scope\n", 19), NULL);
		i++;
	}
	if (num[i] && num[i] != '.')
		return (write(2, "Non digit in number\n", 20), NULL);

	return (&num[i]);
}

int	check_ip_syntax(char *ip)
{
	int	points;

	points = 0;
	while (*ip)
	{
		ip = check_number_range(ip, 255);
		if (!ip)
			return (1);
		if (*ip == '.')
		{
			points += 1;
			if (!*(++ip) || points >= 4)
				return (write(2, "Incorrect points\n", 17), 1);
		}
	}
	if (points != 3)
		return (write(2, "Not enough bytes in IP\n", 23), 1);
	return (0);
}

int	check_mask_syntax(char *mask)
{
	int	points;

	if (*mask == '/' && mask[1])
	{
		mask = check_number_range(mask + 1, 32);
		if (!mask || *mask)
			return (1);
		return (0);
	}
	points = 0;
	while (*mask)
	{
		mask = check_number_range(mask, 255);
		if (!mask)
			return (1);
		if (*mask == '.')
		{
			points += 1;
			if (!*(++mask) || points >= 4)
				return (write(2, "Incorrect points\n", 17), 1);
		}
	}
	if (points != 3)
		return (write(2, "Not enough bytes in mask\n", 25), 1);
	return (0);
}

void	free_split(void *split)
{
	void	**aux;
	int		i;

	if (!split)
		return ;
	aux = split;
	i = 0;
	while (aux[i])
		free(aux[i++]);
	free(aux);
}

int	count_words(char *str, char c)
{
	int	words;

	words = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			words++;
		while (*str && *str != c)
			str++;
	}
	return (words);
}

char	*get_words(char **str_p, char c)
{
	char	*str;
	char	*word;
	int		len;
	int		i;

	str = *str_p;
	while (*str == c)
		str++;
	len = 0;
	while (str[len] && str[len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
		word[i++] = *(str++);
	word[i] = '\0';
	*str_p = str;
	return (word);
}

char	**ft_split(char *str, char c)
{
	char	**split;
	int		words;
	int		i;

	if (!str)
		return (NULL);
	words = count_words(str, c);
	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (i < words)
	{
		split[i] = get_words(&str, c);
		if (!split[i])
			return (free_split(split), NULL);
		i++;
	}
	split[i] = NULL;
	return (split);
}

int	ft_atoi(char *str)
{
	int	nbr;
	int	sign;

	if (!str)
		return (0);
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	nbr = 0;
	while (ft_isdigit(*str))
	{
		nbr = nbr * 10 + *str - '0';
		str++;
	}
	return (nbr);
}

int	get_ip(char *str)
{
	char	**split_ip;
	int		i;
	int		ip;

	split_ip = ft_split(str, '.');
	if (!split_ip)
		return (write(2, "Mallocation failed\n", 19), -1);
	i = 0;
	ip = 0;
	while (split_ip[i])
	{
		ip = (ft_atoi(split_ip[i]) & 255) << ((3 - i) * 8) | ip;
		i++;
	}
	free_split(split_ip);
	return (ip);
}
//	char	*byte;
//	byte = (char *)&ip;
//	i = 4;
//	while (i-- > 0)
//		print_byte(byte[i]);
//	write(1, "\n", 1);

int	get_mask(char *str)
{
	int	mask;
	int	ones;
	int	i;

	if (*str != '/')
		return (get_ip(str));
	str++;
	ones = ft_atoi(str);
	mask = 0;
	i = 0;
	while (i < ones)
		mask = mask |(1 << (31 - i++));
	return (mask);
}
		//printf("Displacing: %d | %d\n", 31 - i, 1 << (31 - i));

t_interface	get_interface_data(char *ip_str, char *mask_str)
{
	t_interface	interface;

	interface.ip = get_ip(ip_str);
	interface.mask = get_mask(mask_str);
	return (interface);
}

void	print_address(int address)
{
	unsigned char	*aux;

	aux = (unsigned char *)&address;
	printf("%.3d.%.3d.%.3d.%.3d\n", aux[3], aux[2], aux[1], aux[0]);
}

void	print_address_bits(int address)
{
	char	*aux;
	int		i;

	aux = (char *)&address;
	i = 4;
	while (i-- > 0)
	{
		print_byte(aux[i]);
		if (i != 0)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void	print_interface(t_interface interface)
{
	//write(1, "Interface:\n | ip:\t\t", 19);
	printf(" Interface:\n\n + IP: ");
	print_address(interface.ip);
	write(1, " - \t", 3);
	//write(1, "\t\t\t\t", 2);
	print_address_bits(interface.ip);
	//write(1, "   mask:\t", 9);
	printf("\n + MASK: ");
	print_address(interface.mask);
	write(1, " - \t", 3);
	//write(1, "\t\t\t\t", 2);
	print_address_bits(interface.mask);
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	t_interface	interface;

	if (argc != 3)
		return (write(2, "Wrong number of arguments!\n", 27), 1);
	if (check_ip_syntax(argv[1]) || check_mask_syntax(argv[2]))
		return (write(2, "Syntax error in interface\n", 26), 2);
	interface = get_interface_data(argv[1], argv[2]);
	print_interface(interface);
	return (0);
}
//	for (int i = 0; i < 256; i++)
//		print_byte(i);
