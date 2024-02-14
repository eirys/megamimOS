/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic_handler.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:28:27 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 19:00:55 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"
# include "idt_decl.h"
# include "pic.h"
# include "debug.h"

namespace cpu::idt {

# define _DECL_INTERNAL     __attribute__ ((no_caller_saved_registers)) static
# define _DECL_INTERRUPT    __attribute__ ((interrupt)) static

/* ------------------- TIMER ------------------ */

_DECL_INTERNAL
void timerInternal() {
    // do stuff
    LOG("Timer interrupt\n");
    pic::sendEOI(pic::IRQ::Timer);
}

_DECL_INTERRUPT
void timerInterrupt(InterruptFrame* frame) {
    timerInternal();
}

/* ----------------- KEYBOARD ----------------- */

_DECL_INTERNAL
void keyboardInternal() {
    // do stuff
    LOG("Keyborad interrupt\n");
    pic::sendEOI(pic::IRQ::Keyboard);
}

_DECL_INTERRUPT
void keyboardInterrupt(InterruptFrame* frame) {
    keyboardInternal();
}

# undef _DECL_INTERNAL
# undef _DECL_INTERRUPT

} // namespace cpu::idt