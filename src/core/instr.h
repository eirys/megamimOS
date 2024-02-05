/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:11:04 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 21:13:32 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

/**
 * @brief Write a byte to a port.
 * This is used to send commands to the PS/2 controller.
*/
static inline
uint8_t inB(uint16_t port) {
    uint8_t ret;

    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

static inline
void outB(uint16_t port, uint8_t data) {
    asm volatile ("outb %0, %1" : : "a" (data), "dN" (port));
}


/**
 * @brief Pause the CPU until the next interrupt.
 * This allows the CPU to save power and reduce heat.
*/
static inline
void pause() {
	asm volatile ("pause");
}
