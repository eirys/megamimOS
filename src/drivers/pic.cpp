/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:01:33 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 00:55:28 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pic.h"
#include "core.h"

namespace pic {

/* -------------------------------------------- */
/*                   PIC PORTS                  */
/* -------------------------------------------- */

static constexpr const u16 MASTER_COMMAND = 0x20;
static constexpr const u16 MASTER_DATA = 0x21;

static constexpr const u16 SLAVE_COMMAND = 0xA0;
static constexpr const u16 SLAVE_DATA = 0xA1;

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

/**
 * @brief The PIC should await a short period of time before sending a command.
 * This is because the PIC is slow and needs time to process the command.
*/
static
void _wait() {
    core::outB(0x80, 0);
}

static
void _disable() {
    core::outB(MASTER_DATA, 0xFF);
    core::outB(SLAVE_DATA, 0xFF);
}

/* -------------------------------------------- */

void sendEOI(IRQ irq) {
    if((u8)irq >= 8)
        core::outB(SLAVE_COMMAND, 0x20);

    core::outB(MASTER_COMMAND, 0x20);
}

void setMask(IRQMask irqMask) {
    core::outB(MASTER_DATA, (u8)irqMask);
    core::outB(SLAVE_DATA, (u8)((u16)irqMask >> 8));
}

/* -------------------------------------------- */

static
void _enableIRQs() {
    constexpr const u8 maskInv = ~((u8)IRQMask::Keyboard | (u8)IRQMask::Timer);
    setMask((pic::IRQMask)maskInv);
}

/**
 * @brief TODO
 * @note https://pdos.csail.mit.edu/6.828/2005/readings/hardware/8259A.pdf
*/
void init() {
    _disable();

    // Tell the PIC to start the initialization sequence
    core::outB(MASTER_COMMAND, 0x10 | 0x01);
    _wait();
    core::outB(SLAVE_COMMAND, 0x10 | 0x01);
    _wait();

    // Set master offset
    core::outB(MASTER_DATA, OFFSET);
    _wait();
    // Set slave offset
    core::outB(SLAVE_DATA, OFFSET + 8);
    _wait();

    // Tell master PIC that there is a slave PIC at IRQ2 (0x04)
    core::outB(MASTER_DATA, 0x04);
    _wait();
    // Tell slave PIC its cascade identity (0x02)
    core::outB(SLAVE_DATA, 0x02);
    _wait();

    // Set 8086 mode (don't ask me why, I don't know either)
    core::outB(MASTER_DATA, 0x01);
    _wait();
    core::outB(SLAVE_DATA, 0x01);
    _wait();

    _enableIRQs();
}

} // namespace pic