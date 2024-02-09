/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:34:43 by etran             #+#    #+#             */
/*   Updated: 2024/02/09 09:54:18 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"

namespace core {

/**
 * @brief Read a byte from a port.
 */
static inline
u8 inB(u16 port) {
    u8 ret;

    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

/**
 * @brief Write a byte to a port.
 * This is used to send commands to the PS/2 controller.
 */
static inline
void outB(u16 port, u8 data) {
    asm volatile ("outb %0, %1" : : "a" (data), "dN" (port));
}

/**
 * @brief Pause the CPU for a short period of time.
 * This allows the CPU to save power and reduce heat.
*/
static inline
void pause() {
	asm volatile ("pause");
}

/**
 * @brief Halt the CPU and stop all interrupts.
*/
static inline
void panic() {
    asm volatile ("cli");
}

/**
 * @brief Pause the CPU until the next interrupt.
*/
static inline
void hlt() {
    asm volatile ("hlt");
}

} // namespace core