/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic_handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 01:17:12 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 01:46:54 by etran            ###   ########.fr       */
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
    LOG("Timer interrupt\n");
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
    LOG("Keyborad interrupt\n");
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