/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps2.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:40:56 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 19:11:54 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

namespace ps2 {

/* -------------------------------------------- */
/*             PS/2 CONTROLLER PORTS            */
/* -------------------------------------------- */

/**
 * @brief The data port of the PS/2 controller.
 * Used to interpret scancodes and commands.
*/
static constexpr const uint8_t DATA_PORT = 0x60;

/**
 * @brief The command port of the PS/2 controller.
 * Used to send commands to the PS/2 controller.
*/
static constexpr const uint8_t COMMAND_PORT = 0x64;

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

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

/**
 * @brief Read the status of the PS/2 controller.
 * This is used to check if the output buffer is full,
 * aka if there is data to read.
*/
static inline
uint8_t readStatus() {
    return inB(COMMAND_PORT);
}

/**
 * @brief Read data from the PS/2 controller.
 * The returned value can be a scancode or a command.
 * They should be interpreted according to the PS/2
 * protocol, which can be found here:
 * https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
 *
 * @note Empty the output buffer.
 */
static inline
uint8_t readData() {
    return inB(DATA_PORT);
}

/**
 * @brief Checks if the output buffer is full,
 * aka if the first bit of the status register is set.
*/
static inline
bool isOutputFull() {
    uint8_t status = readStatus();
    return status & 0x01;
}

/**
 * @brief Pause the CPU until the user presses a key.
*/
static inline
bool poll() {
    while (!isOutputFull()) {
        pause();
    }
    return true;
}

static inline
void read() {
    // uint8_t data = ps2::readData();

    // Interpret the scancode
}

} // namespace ps2
