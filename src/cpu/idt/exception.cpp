/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:52:05 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 14:29:58 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exception.h"
#include "debug.h"
#include "core.h"
#include "panic.h"
#include "idt_decl.h"

namespace cpu::idt {

# define _DECL_INTERNAL     __attribute__ ((no_caller_saved_registers)) static
# define _DECL_INTERRUPT    __attribute__ ((interrupt))

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

_DECL_INTERNAL
void divisionErrorInternal() {
    beginKernelPanic("Received an unexpected #DE exception.");
}

_DECL_INTERRUPT
void divisionError(InterruptFrame* frame) {
    (void)frame;
    divisionErrorInternal();
}

_DECL_INTERNAL
void debugInternal() {
    beginKernelPanic("Received an unexpected #DB exception.");
}

_DECL_INTERRUPT
void debug(InterruptFrame *frame) {
    (void)frame;
    debugInternal();
}

_DECL_INTERNAL
void nonMaskableInterruptInternal() {
    beginKernelPanic("Received an unexpected NON MASKABLE INTERRUPT.");
}

_DECL_INTERRUPT
void nonMaskableInterrupt(InterruptFrame *frame) {
    (void)frame;
    nonMaskableInterruptInternal();
}

_DECL_INTERNAL
void breakpointInternal() {
    beginKernelPanic("Received an unexpected #BP exception.");
}

_DECL_INTERRUPT
void breakpoint(InterruptFrame *frame) {
    (void)frame;
    breakpointInternal();
}

_DECL_INTERNAL
void overflowInternal() {
    beginKernelPanic("Received an unexpected #OF exception.");
}

_DECL_INTERRUPT
void overflow(InterruptFrame *frame) {
    (void)frame;
    overflowInternal();
}

_DECL_INTERNAL
void boundRangeExceededInternal() {
    beginKernelPanic("Received an unexpected #BR exception.");
}

_DECL_INTERRUPT
void boundRangeExceeded(InterruptFrame *frame) {
    (void)frame;
    boundRangeExceededInternal();
}

_DECL_INTERNAL
void invalidOpcodeInternal() {
    beginKernelPanic("Received an unexpected #UD exception.");
}

_DECL_INTERRUPT
void invalidOpcode(InterruptFrame *frame) {
    (void)frame;
    invalidOpcodeInternal();
}

_DECL_INTERNAL
void deviceNotAvailableInternal() {
    beginKernelPanic("Received an unexpected #NM exception.");
}

_DECL_INTERRUPT
void deviceNotAvailable(InterruptFrame *frame) {
    (void)frame;
    deviceNotAvailableInternal();
}

_DECL_INTERNAL
void doubleFaultInternal() {
    beginKernelPanic("Received an unexpected #DF exception.");
}

_DECL_INTERRUPT
void doubleFault(InterruptFrame *frame, ErrorCode code) {
    (void)frame;
    (void)code;
    doubleFaultInternal();
}

_DECL_INTERNAL
void invalidTssInternal() {
    beginKernelPanic("Received an unexpected #TS exception.");
}

_DECL_INTERRUPT
void invalidTss(InterruptFrame *frame, ErrorCode code) {
    (void)frame;
    (void)code;
    invalidTssInternal();
}

_DECL_INTERNAL
void segmentNotPresentInternal() {
    beginKernelPanic("Received an unexpected #NP exception.");
}

_DECL_INTERRUPT
void segmentNotPresent(InterruptFrame *frame, ErrorCode code) {
    (void)frame;
    (void)code;
    segmentNotPresentInternal();
}

_DECL_INTERNAL
void stackSegmentFaultInternal() {
    beginKernelPanic("Received an unexpected #SS exception.");
}

_DECL_INTERRUPT
void stackSegmentFault(InterruptFrame *frame, ErrorCode code) {
    (void)frame;
    (void)code;
    stackSegmentFaultInternal();
}

_DECL_INTERNAL
void generalProtectionFaultInternal() {
    beginKernelPanic("Received an unexpected #GP exception.");
}

_DECL_INTERRUPT
void generalProtectionFault(InterruptFrame *frame, ErrorCode code) {
    (void)frame;
    (void)code;
    generalProtectionFaultInternal();
}

_DECL_INTERNAL
void pageFaultInternal(InterruptFrame *frame, ErrorCode code) {
    LOG("PAGE FAULT!"); NL;

    // REad the CR2 register
    u32 cr2;
    asm volatile("mov %%cr2, %0" : "=r"(cr2));


    LOG("Instr="); LOG_NUM(frame->m_ip); NL;
    LOG("Addr="); LOG_NUM(cr2); NL;

    if (code & 0x1) {
        LOG("Page-protection violation"); NL;
    } else {
        LOG("Non-present page"); NL;
    }
    if (code & 0x2) {
        LOG("Write access"); NL;
    } else {
        LOG("Read access"); NL;
    }
    if (code & 0x4) {
        LOG("User-mode access"); NL;
    } else {
        LOG("Supervisor-mode access"); NL;
    }

    beginKernelPanic("Received an unexpected #PF exception.");
}

_DECL_INTERRUPT
void pageFault(InterruptFrame *frame, ErrorCode code) {
    (void)frame;
    (void)code;
    pageFaultInternal(frame, code);
}

_DECL_INTERNAL
void x87FloatingPointInternal() {
    beginKernelPanic("Received an unexpected #MF exception.");
}

_DECL_INTERRUPT
void x87FloatingPoint(InterruptFrame *frame) {
    (void)frame;
    x87FloatingPointInternal();
}

_DECL_INTERNAL
void alignmentCheckInternal() {
    beginKernelPanic("Received an unexpected #AC exception.");
}

_DECL_INTERRUPT
void alignmentCheck(InterruptFrame *frame, ErrorCode code) {
    (void)frame;
    (void)code;
    alignmentCheckInternal();
}

_DECL_INTERNAL
void machineCheckInternal() {
    beginKernelPanic("Received an unexpected #MC exception.");
}

_DECL_INTERRUPT
void machineCheck(InterruptFrame *frame) {
    (void)frame;
    machineCheckInternal();
}

_DECL_INTERNAL
void simdFloatingPointInternal() {
    beginKernelPanic("Received an unexpected #XF exception.");
}

_DECL_INTERRUPT
void simdFloatingPoint(InterruptFrame *frame) {
    (void)frame;
    simdFloatingPointInternal();
}

_DECL_INTERNAL
void virtualizationInternal() {
    beginKernelPanic("Received an unexpected #VE exception.");
}

_DECL_INTERRUPT
void virtualization(InterruptFrame *frame) {
    (void)frame;
    virtualizationInternal();
}

_DECL_INTERNAL
void controlProtectionInternal() {
    beginKernelPanic("Received an unexpected #CP exception.");
}

_DECL_INTERRUPT
void controlProtection(InterruptFrame *frame, ErrorCode code) {
    (void)frame;
    (void)code;
    controlProtectionInternal();
}

_DECL_INTERNAL
void hypervisorInjectionInternal() {
    beginKernelPanic("Received an unexpected #HV exception.");
}

_DECL_INTERRUPT
void hypervisorInjection(InterruptFrame *frame) {
    (void)frame;
    hypervisorInjectionInternal();
}

_DECL_INTERNAL
void vmmCommunicationInternal() {
    beginKernelPanic("Received an unexpected #VC exception.");
}

_DECL_INTERRUPT
void vmmCommunication(InterruptFrame *frame, ErrorCode code) {
    (void)frame;
    (void)code;
    vmmCommunicationInternal();
}


_DECL_INTERNAL
void securityInternal() {
    beginKernelPanic("Received an unexpected #SX exception.");
}

_DECL_INTERRUPT
void security(InterruptFrame *frame, ErrorCode code) {
    (void)frame;
    (void)code;
    securityInternal();
}


# undef _DECL_INTERNAL
# undef _DECL_INTERRUPT

} // namespace cpu::idt