/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:43:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 15:52:52 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"
# include "exception.h"

namespace cpu::idt {

/**
 * @brief The Interrupt Descriptor Table Register.
 * Limit is the (size - 1) of the IDT, and base is the address of the IDT.
 */
struct IDTR {
    u16 m_limit;
    u64 m_base;
} __attribute__((packed));

/**
 * @brief The Gate Descriptor: a packed structure for the IDT.
 * @note The detailed structure is described here: https://wiki.osdev.org/IDT#Gate_Descriptor
 */
using GateDescriptor = u64;

/**
 * @brief The privilege level of the interrupt (ring 0, 1, 2, or 3).
 */
enum class Ring: u8 {
    Kernel = 0,
    User = 3
};

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

/* -------------------------------------------- */

/**
 * @brief ASM function to load the IDT.
*/
extern "C"
void load_idt(const IDTR* reg);

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
}

static
void init() {
    _load();

    constexpr u16 IDT_SIZE = GATE_COUNT * sizeof(GateDescriptor);

    IDTR idtr = {
        .m_limit = IDT_SIZE - 1,
        .m_base = (u64)IDT };

    load_idt(&idtr);
}

} // namespace cpu::idt