/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:25:02 by etran             #+#    #+#             */
/*   Updated: 2024/02/13 18:50:55 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"
# include "debug.h"
# include "lib.h"
# include "utils.h"

namespace cpu::gdt {

/**
 * @brief This will be the address of the Global Descriptor Table.
 */
static constexpr const u32 ADDRESS = 0x00000800;

/**
 * @brief The Global Descriptor Table Register.
 * Limit is the (size - 1) of the GDT, and base is the address of the GDT.
 */
struct GDTR {
    u16 m_limit;
    u64 m_base;
} __attribute__((packed));

/**
 * @brief Segments of the GDT.
 * For now, we only have kernel and user segments.
 */
enum class Segment: u8 {
    Null        = 0,
    KernelCode  = 1,
    KernelData  = 2,
    KernelStack = 3,
    UserCode    = 4,
    UserData    = 5,
    UserStack   = 6,

    First = Null,
    Last = UserStack
};

static constexpr const u32 SEGMENT_COUNT = enumSize<Segment>();

/**
 * @brief The Segment Descriptor: a packed structure for the GDT.
 * @note The detailed structure is described here: https://wiki.osdev.org/Global_Descriptor_Table#Segment_Descriptor
 */
enum class SegmentDescriptor: u64 {
    // Null Segment. Don't ask.
    Null        = 0x0,

    // Kernel
    KernelCode  = 0x00cf9a000000ffff,
    KernelData  = 0x00cf92000000ffff,
    KernelStack = 0x00cf92000000ffff,

    // User
    UserCode    = 0x00cffa000000ffff,
    UserData    = 0x00cff2000000ffff,
    UserStack   = 0x00cff2000000ffff
};

/* -------------------------------------------- */

/**
 * @brief ASM function to load the GDT.
 */
extern "C"
void load_gdt(const GDTR* reg);

/**
 * @brief Loads the Global Descriptor Table.
 */
static
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