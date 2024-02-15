/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:48:02 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 13:08:28 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "idt.h"
#include "exception.h"
#include "pic.h"
#include "pic_handler.h"

namespace cpu::idt {

static constexpr u32 GATE_COUNT = 256;

/**
 * @brief The Interrupt Descriptor Table.
 * @note The IDT is an array of 256 interrupt handlers, each of which is a GateDescriptor.
 */
GateDescriptor  IDT[GATE_COUNT] = { 0 };

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

/**
 * @brief ASM function to load the IDT.
*/
extern "C"
void load_idt(const IDTR* reg);

/**
 * @brief Creates a gate descriptor that can be loaded into the IDT.
 *
 * @param offset The function pointer to the interrupt handler.
 * @param disableInterrupt Whether to disable interrupts when the interrupt is called.
 * @param dpl The privilege level of the interrupt (ring 0, 1, 2, or 3).
 */
static
GateDescriptor _createGateDescriptor(
    void* offset,
    bool disableInterrupt,
    Ring dpl
) {
    GateDescriptor desc = 0;

    // offset
    desc |= (u64)((u64)offset & 0x0000FFFF);
    desc |= (u64)((u64)offset & 0xFFFF0000) << 32;

    // segment selector
    desc |= (u64)0x08 << 16;

    // gate type
    desc |= (u64)(disableInterrupt ? 0xE : 0xF) << 40;

    // DPL
    desc |= (u64)dpl << 45;

    // present
    desc |= (u64)0x1 << 47;

    return desc;
}

/**
 * @brief Fill the IDT with the default interrupt handlers.
 */
static
void _load() {
    // TODO
    constexpr const bool enableInt = true;
    constexpr const bool disableInt = false;

    IDT[(u8)Exception::DivisionError] = _createGateDescriptor((void*)divisionError, enableInt, Ring::Kernel);
    IDT[(u8)Exception::Debug] = _createGateDescriptor((void*)debug, enableInt, Ring::Kernel);
    IDT[(u8)Exception::NonMaskableInterrupt] = _createGateDescriptor((void*)nonMaskableInterrupt, enableInt, Ring::Kernel);
    IDT[(u8)Exception::Breakpoint] = _createGateDescriptor((void*)breakpoint, enableInt, Ring::Kernel);
    IDT[(u8)Exception::Overflow] = _createGateDescriptor((void*)overflow, enableInt, Ring::Kernel);
    IDT[(u8)Exception::BoundRangeExceeded] = _createGateDescriptor((void*)boundRangeExceeded, enableInt, Ring::Kernel);
    IDT[(u8)Exception::InvalidOpcode] = _createGateDescriptor((void*)invalidOpcode, enableInt, Ring::Kernel);
    IDT[(u8)Exception::DeviceNotAvailable] = _createGateDescriptor((void*)deviceNotAvailable, enableInt, Ring::Kernel);
    IDT[(u8)Exception::DoubleFault] = _createGateDescriptor((void*)doubleFault, disableInt, Ring::Kernel);
    IDT[(u8)Exception::InvalidTSS] = _createGateDescriptor((void*)invalidTss, enableInt, Ring::Kernel);
    IDT[(u8)Exception::SegmentNotPresent] = _createGateDescriptor((void*)segmentNotPresent, enableInt, Ring::Kernel);
    IDT[(u8)Exception::StackSegmentFault] = _createGateDescriptor((void*)stackSegmentFault, enableInt, Ring::Kernel);
    IDT[(u8)Exception::GeneralProtectionFault] = _createGateDescriptor((void*)generalProtectionFault, enableInt, Ring::Kernel);
    IDT[(u8)Exception::PageFault] = _createGateDescriptor((void*)pageFault, enableInt, Ring::Kernel);
    IDT[(u8)Exception::x87FPUError] = _createGateDescriptor((void*)x87FloatingPoint, enableInt, Ring::Kernel);
    IDT[(u8)Exception::AlignmentCheck] = _createGateDescriptor((void*)alignmentCheck, enableInt, Ring::Kernel);
    IDT[(u8)Exception::MachineCheck] = _createGateDescriptor((void*)machineCheck, enableInt, Ring::Kernel);
    IDT[(u8)Exception::SimdFloatingPoint] = _createGateDescriptor((void*)simdFloatingPoint, enableInt, Ring::Kernel);
    IDT[(u8)Exception::Virtualization] = _createGateDescriptor((void*)virtualization, enableInt, Ring::Kernel);
    IDT[(u8)Exception::ControlProtection] = _createGateDescriptor((void*)controlProtection, enableInt, Ring::Kernel);
    IDT[(u8)Exception::HypervisorInjection] = _createGateDescriptor((void*)hypervisorInjection, enableInt, Ring::Kernel);
    IDT[(u8)Exception::VMMCommunication] = _createGateDescriptor((void*)vmmCommunication, enableInt, Ring::Kernel);
    IDT[(u8)Exception::Security] = _createGateDescriptor((void*)security, enableInt, Ring::Kernel);

    IDT[pic::OFFSET + (u8)pic::IRQ::Timer] = _createGateDescriptor((void*)timerInterrupt, disableInt, Ring::Kernel);
    IDT[pic::OFFSET + (u8)pic::IRQ::Keyboard] = _createGateDescriptor((void*)keyboardInterrupt, disableInt, Ring::Kernel);

}

void init() {
    _load();

    constexpr u16 IDT_SIZE = GATE_COUNT * sizeof(GateDescriptor);

    IDTR idtr = {
        .m_limit = IDT_SIZE - 1,
        .m_base = (u64)IDT };

    load_idt(&idtr);
}

} // namespace cpu::idt