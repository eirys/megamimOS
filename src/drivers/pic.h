/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:55:52 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 21:04:14 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

/**
 * @brief The PIC (Programmable Interrupt Controller) is a chip that
 * manages the interrupts of the CPU.
 * It is used to manage the IRQs (Interrupt Requests) and
 * to send them to the CPU.
*/
namespace pic {

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

void    init();

/* -------------------------------------------- */

void    sendEOI(IRQ irq);
void    setMask(IRQMask irqMask);

} // namespace pic