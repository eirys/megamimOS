/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic_handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 01:17:12 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 03:30:38 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pic_handler.h"
#include "pic.h"
#include "pit.h"
#include "idt_decl.h"
#include "event_handler.h"
#include "ps2.h"
#include "time.h"

namespace cpu::idt {

# define _DECL_INTERNAL     __attribute__ ((no_caller_saved_registers)) static
# define _DECL_INTERRUPT    __attribute__ ((interrupt))

/* ------------------- TIMER ------------------ */

_DECL_INTERNAL
void timerInternal() {
    kfs::microsecondsSinceBoot += pit::tickDurationMicros;
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
    ui::EventHandler::insertScancode(ps2::readData());
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
