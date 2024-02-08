/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:16:07 by scely             #+#    #+#             */
/*   Updated: 2024/02/08 17:43:01 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_putchar_print(char c);
int	ft_putstr_print(char *s);
int	ft_putnbr_print(int n);
int	ft_putnbru_print(unsigned int n);
int	ft_print_hexa(unsigned int nbr, char c);
int	ft_printf(const char *str, ...);
int	ft_print_ptr(void *p);

#endif