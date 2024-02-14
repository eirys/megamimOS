/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:57:21 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 21:00:33 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gdt.h"
#include "debug.h"
#include "lib.h"

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
    constexpr const SegmentDescriptor gdt[] = {
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

#ifdef _DEBUG
    // read stack pointer
    u64 sp;
    asm volatile ("mov %%esp, %0" : "=m" (sp));
    LOG_NUM((u32)sp);
    LOG_C('\n');

    // display stack content (16 first bytes)
    u8* stack = (u8*)sp;
    for (u32 i = 0; i < 16; ++i) {
        LOG_NUM((u32)stack[i]);
        LOG_C('\n');
    }
#endif
}

}  // namespace cpu::gdt