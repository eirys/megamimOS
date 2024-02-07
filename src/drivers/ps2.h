/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps2.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:40:56 by etran             #+#    #+#             */
/*   Updated: 2024/02/07 00:41:44 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"
#include "core.h"

namespace ps2 {

/* -------------------------------------------- */
/*             PS/2 CONTROLLER PORTS            */
/* -------------------------------------------- */

/**
 * @brief The data port of the PS/2 controller.
 * Used to interpret scancodes and commands.
*/
static constexpr const u8 DATA_PORT = 0x60;

/**
 * @brief The command port of the PS/2 controller.
 * Used to send commands to the PS/2 controller.
*/
static constexpr const u8 COMMAND_PORT = 0x64;

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

/**
 * @brief Read the status of the PS/2 controller.
 * This is used to check if the output buffer is full,
 * aka if there is data to read.
*/
static inline
u8 readStatus() {
    return core::inB(COMMAND_PORT);
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
u8 readData() {
    return core::inB(DATA_PORT);
}

/**
 * @brief Checks if the output buffer is full,
 * aka if the first bit of the status register is set.
*/
static inline
bool isOutputFull() {
    u8 status = readStatus();
    return status & 0x01;
}

/**
 * @brief Pause the CPU until the user presses a key.
*/
static inline
u8 poll() {
    while (!isOutputFull()) {
        core::pause();
    }
    return readData();
}

} // namespace ps2
