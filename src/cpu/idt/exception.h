/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:54:18 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 13:08:13 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace cpu::idt {

# define _DECL_INTERRUPT    __attribute__ ((interrupt))
# define ErrorCode unsigned long

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
    SimdFloatingPoint               = 19,
    Virtualization                  = 20,
    ControlProtection               = 21,

    Reserved1                       = 22,
    Reserved2                       = 23,
    Reserved3                       = 24,
    Reserved4                       = 25,
    Reserved5                       = 26,
    Reserved6                       = 27,

    HypervisorInjection             = 28,
    VMMCommunication                = 29,
    Security                        = 30,

    Reserved7                       = 31,

    First = DivisionError,
    Last = Reserved7
};

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

struct InterruptFrame;

_DECL_INTERRUPT void    divisionError(InterruptFrame* frame);
_DECL_INTERRUPT void    debug(InterruptFrame* frame);
_DECL_INTERRUPT void    nonMaskableInterrupt(InterruptFrame* frame);
_DECL_INTERRUPT void    breakpoint(InterruptFrame* frame);
_DECL_INTERRUPT void    overflow(InterruptFrame* frame);
_DECL_INTERRUPT void    boundRangeExceeded(InterruptFrame* frame);
_DECL_INTERRUPT void    invalidOpcode(InterruptFrame* frame);
_DECL_INTERRUPT void    deviceNotAvailable(InterruptFrame* frame);
_DECL_INTERRUPT void    doubleFault(InterruptFrame* frame, ErrorCode code);
_DECL_INTERRUPT void    invalidTss(InterruptFrame* frame, ErrorCode code);
_DECL_INTERRUPT void    segmentNotPresent(InterruptFrame* frame, ErrorCode code);
_DECL_INTERRUPT void    stackSegmentFault(InterruptFrame* frame, ErrorCode code);
_DECL_INTERRUPT void    generalProtectionFault(InterruptFrame* frame, ErrorCode code);
_DECL_INTERRUPT void    pageFault(InterruptFrame* frame, ErrorCode code);
_DECL_INTERRUPT void    x87FloatingPoint(InterruptFrame* frame);
_DECL_INTERRUPT void    alignmentCheck(InterruptFrame* frame, ErrorCode code);
_DECL_INTERRUPT void    machineCheck(InterruptFrame* frame);
_DECL_INTERRUPT void    simdFloatingPoint(InterruptFrame* frame);
_DECL_INTERRUPT void    virtualization(InterruptFrame* frame);
_DECL_INTERRUPT void    controlProtection(InterruptFrame* frame, ErrorCode code);
_DECL_INTERRUPT void    hypervisorInjection(InterruptFrame* frame);
_DECL_INTERRUPT void    vmmCommunication(InterruptFrame* frame, ErrorCode code);
_DECL_INTERRUPT void    security(InterruptFrame* frame, ErrorCode code);


# undef _DECL_INTERRUPT
# undef ErrorCode

} // namespace cpu::idt