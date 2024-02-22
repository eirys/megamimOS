/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:57:21 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 14:12:23 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gdt.h"
#include "debug.h"
#include "lib.h"
#include "utils.h"

namespace cpu::gdt {

static constexpr const u32 ADDRESS = 0x00000800;
static constexpr const u32 SEGMENT_COUNT = enumSize<Segment>();

/**
 * @brief ASM function to load the GDT.
 */
extern "C"
void load_gdt(const GDTR* reg);

/**
 * @brief Loads the Global Descriptor Table.
 */
void init() {
    constexpr const SegmentDescriptor gdt[SEGMENT_COUNT] = {
        SegmentDescriptor::Null,
        SegmentDescriptor::KernelCode,
        SegmentDescriptor::KernelData,
        SegmentDescriptor::KernelStack,
        SegmentDescriptor::UserCode,
        SegmentDescriptor::UserData,
        SegmentDescriptor::UserStack
    };

    constexpr u16 GDT_SIZE = SEGMENT_COUNT * sizeof(SegmentDescriptor);

    GDTR gdtr = {
        .m_limit = GDT_SIZE - 1,
        .m_base = ADDRESS };

    // Set GDT to ADDRESS
    lib::memcpy((void*)ADDRESS, gdt, GDT_SIZE);

    load_gdt(&gdtr);
}

}  // namespace cpu::gdt