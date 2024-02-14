/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:54:18 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 15:59:54 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"
# include "debug.h"

namespace cpu {

# define _DECL_INTERNAL     __attribute__ ((no_caller_saved_registers)) static
# define _DECL_INTERRUPT    __attribute__ ((interrupt)) static

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

/**
 * @brief The Interrupt Frame: the state of the CPU when an interrupt occurs.
 * @note It is pushed onto the stack when an interrupt occurs, so that
 * the CPU can resume execution after the interrupt handler returns (with an IRET instruction).
 */
struct InterruptFrame {
    u32 m_ip; // Instruction Pointer
    u32 m_cs; // Code Segment
    u32 m_flags;
    u32 m_sp; // Stack Pointer
    u32 m_ss; // Stack Segment
};

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

/* -------------- DIVISION ERROR -------------- */

_DECL_INTERNAL
void divisionErrorInternal() {
    LOG("division error");
    core::hlt();
}

_DECL_INTERRUPT
void divisionError(InterruptFrame* frame) {
    (void)frame;
    divisionErrorInternal();
}

/* ---------------- BREAKPOINT ---------------- */

_DECL_INTERNAL
void breakpointInternal() {
    LOG("breakpoint");
}

_DECL_INTERRUPT
void breakpoint(InterruptFrame* frame) {
    (void)frame;
    breakpointInternal();
}

# undef _DECL_INTERNAL
# undef _DECL_INTERRUPT

} // namespace cpu