/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:54:18 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 20:56:55 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace cpu::idt {

# define _DECL_INTERRUPT    __attribute__ ((interrupt))

/**
 * @brief Exception codes: Interrupts triggered by the CPU when an error occurs.
 * @note https://wiki.osdev.org/Exception
 */
enum class Exception: u8 {
    DivisionError                   = 0,
    Debug                           = 1,
    NonMaskableInterrupt            = 2,
    Breakpoint                      = 3,
    Overflow                        = 4,
    BoundRangeExceeded              = 5,
    InvalidOpcode                   = 6,
    DeviceNotAvailable              = 7,
    DoubleFault                     = 8,
    CoprocessorSegmentOverrun       = 9,
    InvalidTSS                      = 10,
    SegmentNotPresent               = 11,
    StackSegmentFault               = 12,
    GeneralProtectionFault          = 13,
    PageFault                       = 14,

    Reserved0                       = 15,

    x87FPUError                     = 16,
    AlignmentCheck                  = 17,
    MachineCheck                    = 18,
    SIMDException                   = 19,
    VirtualizationException         = 20,
    ControlProtectionException      = 21,

    Reserved1                       = 22,
    Reserved2                       = 23,
    Reserved3                       = 24,
    Reserved4                       = 25,
    Reserved5                       = 26,
    Reserved6                       = 27,

    HypervisorInjectionException    = 28,
    VMMCommunicationException       = 29,
    SecurityException               = 30,

    Reserved7                       = 31,

    First = DivisionError,
    Last = Reserved7
};

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

struct InterruptFrame;

_DECL_INTERRUPT void    divisionError(InterruptFrame* frame);
_DECL_INTERRUPT void    breakpoint(InterruptFrame* frame);

# undef _DECL_INTERRUPT

} // namespace cpu::idt