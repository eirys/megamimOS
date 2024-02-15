/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic_handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 01:17:12 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 14:05:16 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pic_handler.h"
#include "pic.h"
#include "idt_decl.h"
#include "debug.h"

namespace cpu::idt {

# define _DECL_INTERNAL     __attribute__ ((no_caller_saved_registers)) static
# define _DECL_INTERRUPT    __attribute__ ((interrupt))

/* ------------------- TIMER ------------------ */

_DECL_INTERNAL
void timerInternal() {
    // do stuff
    pic::sendEOI(pic::IRQ::Timer);
}

_DECL_INTERRUPT
void timerInterrupt(InterruptFrame* frame) {
    (void)frame;
    timerInternal();
}

/* ----------------- KEYBOARD ----------------- */

_DECL_INTERNAL
void keyboardInternal() {
    // do stuff
    pic::sendEOI(pic::IRQ::Keyboard);
}

_DECL_INTERRUPT
void keyboardInterrupt(InterruptFrame* frame) {
    (void)frame;
    keyboardInternal();
}

# undef _DECL_INTERNAL
# undef _DECL_INTERRUPT

} // namespace cpu::idt
