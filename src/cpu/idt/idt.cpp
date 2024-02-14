/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:48:02 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 20:55:50 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "idt.h"
#include "exception.h"
#include "pic_handler.h"

namespace cpu::idt {

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
    IDT[(u8)Exception::Breakpoint] = _createGateDescriptor((void*)breakpoint, enableInt, Ring::Kernel);

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