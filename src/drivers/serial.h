/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serial.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 01:28:47 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 21:11:34 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "core.h"

namespace serial {

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

void    init();

void    write_byte(u8 byte);
void    write_str(i8 const *bytes, u32 count = 128);
void    write_nbr(u32 value);

} // namespace serial