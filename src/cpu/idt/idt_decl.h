/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idt_decl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:37:56 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 19:01:05 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace cpu::idt {

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

/**
 * @brief The error code received by an exception.
*/
using ErrorCode = unsigned long;

}
