/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:28:27 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 01:47:01 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace cpu::idt {

# define _DECL_INTERRUPT    __attribute__ ((interrupt))

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

struct InterruptFrame;

_DECL_INTERRUPT void    timerInterrupt(InterruptFrame* frame);
_DECL_INTERRUPT void    keyboardInterrupt(InterruptFrame* frame);

# undef _DECL_INTERRUPT

} // namespace cpu::idt