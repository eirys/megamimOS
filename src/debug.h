/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:34:12 by etran             #+#    #+#             */
/*   Updated: 2024/02/18 21:28:09 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef _DEBUG
# include "serial.h"
# define LOG_NUM    serial::write_nbr
# define LOG_C      serial::write_byte
# define LOG        serial::write_str
# define NL         serial::write_byte('\n')
#else
# define LOG_NUM    (void)
# define LOG_C      (void)
# define LOG        (void)
# define NL         (void)
#endif