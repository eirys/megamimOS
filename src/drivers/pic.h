/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:55:52 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 18:40:50 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"
# include "core.h"

/**
 * @brief The PIC (Programmable Interrupt Controller) is a chip that
 * manages the interrupts of the CPU.
 * It is used to manage the IRQs (Interrupt Requests) and
 * to send them to the CPU.
*/
namespace pic {

/* -------------------------------------------- */
/*                   PIC PORTS                  */
/* -------------------------------------------- */

static constexpr const u16 MASTER_COMMAND = 0x20;
static constexpr const u16 MASTER_DATA = 0x21;

static constexpr const u16 SLAVE_COMMAND = 0xA0;
static constexpr const u16 SLAVE_DATA = 0xA1;

// https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interrupt_Controller#IRQs
enum class IRQ: u8 {
    Timer           = 0,
    Keyboard        = 1,
    Cascade         = 2,
    COM2            = 3,
    COM1            = 4,
    Printer2        = 5,
    FloppyDisk      = 6,
    Printer1        = 7,
    RealTimeClock   = 8,
    ACPI            = 9,
    Periph2         = 10,
    Periph1         = 11,
    Mouse           = 12,
    MathCoProcessor = 13,
    PrimaryATA      = 14,
    SecondaryATA    = 15
};

enum class IRQMask: u16 {
    Timer           = 1 << (u8)IRQ::Timer,
    Keyboard        = 1 << (u8)IRQ::Keyboard,
    Cascade         = 1 << (u8)IRQ::Cascade,
    COM2            = 1 << (u8)IRQ::COM2,
    COM1            = 1 << (u8)IRQ::COM1,
    Printer2        = 1 << (u8)IRQ::Printer2,
    FloppyDisk      = 1 << (u8)IRQ::FloppyDisk,
    Printer1        = 1 << (u8)IRQ::Printer1,
    RealTimeClock   = 1 << (u8)IRQ::RealTimeClock,
    ACPI            = 1 << (u8)IRQ::ACPI,
    Periph2         = 1 << (u8)IRQ::Periph2,
    Periph1         = 1 << (u8)IRQ::Periph1,
    Mouse           = 1 << (u8)IRQ::Mouse,
    MathCoProcessor = 1 << (u8)IRQ::MathCoProcessor,
    PrimaryATA      = 1 << (u8)IRQ::PrimaryATA,
    SecondaryATA    = 1 << (u8)IRQ::SecondaryATA
};

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

/**
 * @brief The PIC should await a short period of time before sending a command.
 * This is because the PIC is slow and needs time to process the command.
*/
static inline
void wait(void) {
    core::outB(0x80, 0);
}

static inline
void sendEOI(IRQ irq) {
    if((u8)irq >= 8)
        core::outB(SLAVE_COMMAND, 0x20);

    core::outB(MASTER_COMMAND, 0x20);
}

/* -------------------------------------------- */

void setMask(IRQMask irqMask) {
    core::outB(MASTER_DATA, (u8)irqMask);
    core::outB(SLAVE_DATA, (u8)((u16)irqMask >> 8));
}

void disable() {
    core::outB(MASTER_DATA, 0xFF);
    core::outB(SLAVE_DATA, 0xFF);
}

/* -------------------------------------------- */

static constexpr u8 OFFSET = 0x20;

/**
 * @brief TODO
 * @note https://pdos.csail.mit.edu/6.828/2005/readings/hardware/8259A.pdf
*/
static
void init() {
    disable();

    // Tell the PIC to start the initialization sequence
    core::outB(MASTER_COMMAND, 0x10 | 0x01);
    wait();
    core::outB(SLAVE_COMMAND, 0x10 | 0x01);
    wait();

    // Set master offset
    core::outB(MASTER_DATA, OFFSET);
    wait();
    // Set slave offset
    core::outB(SLAVE_DATA, OFFSET + 8);
    wait();

    // Tell master PIC that there is a slave PIC at IRQ2 (0x04)
    core::outB(MASTER_DATA, 0x04);
    wait();
    // Tell slave PIC its cascade identity (0x02)
    core::outB(SLAVE_DATA, 0x02);
    wait();

    // Set 8086 mode (don't ask me why, I don't know either)
    core::outB(MASTER_DATA, 0x01);
    wait();
    core::outB(SLAVE_DATA, 0x01);
    wait();
}


} // namespace pic