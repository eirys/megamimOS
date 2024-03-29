/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:43:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 21:21:22 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

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

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

void init();

} // namespace cpu::idt