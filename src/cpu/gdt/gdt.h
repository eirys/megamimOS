/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gdt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:25:02 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 01:02:41 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace cpu::gdt {

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

/**
 * @brief The Segment Descriptor: a packed structure for the GDT.
 * @note The detailed structure is described here: https://wiki.osdev.org/Global_Descriptor_Table#Segment_Descriptor
 */
enum class SegmentDescriptor: u64 {
    // Null Segment. Don't ask.
    Null                = 0x0,

    // Kernel
    KernelCode          = 0x00cf9a000000ffff,
    KernelData          = 0x00cf92000000ffff,
    KernelStack         = 0x00cf92000000ffff,

    // User
    UserCode            = 0x00cffa000000ffff,
    UserData            = 0x00cff2000000ffff,
    UserStack           = 0x00cff2000000ffff
};

/* -------------------------------------------- */
/*                   FUNCTION                   */
/* -------------------------------------------- */

void init();

}  // namespace cpu::gdt