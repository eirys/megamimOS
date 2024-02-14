/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serial.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 21:05:27 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 21:11:41 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serial.h"
#include "core.h"

namespace serial {

/* -------------------------------------------- */
/*                 SERIAL PORTS                 */
/* -------------------------------------------- */

/// The I/O port used by the serial communication driver.
static constexpr const u16 PORT = 0x3F8;

/* -------------------------------------------- */
/*                   FUNCTION                   */
/* -------------------------------------------- */

/// Initializes the serial port driver.
///
/// This function should be called once before starting to use the serial port.
void init() {
    // Disable all interrupts. This is necessary because this driver is intended to be
    // poll-based instead of interrupt based. This is necssary because it will mainly
    // be used to log stuff to the outside world, meaning that we need to rely on
    // as little stuff as possible.
    core::outB(PORT + 1, 0x00);

    // Set the baud rate to 38400 bps. This is the most common baud rate for serial
    // communication.
    core::outB(PORT + 3, 0x80);
    core::outB(PORT + 0, 0x03);
    core::outB(PORT + 1, 0x00);

    // Configure the line to use 8 bits, no parity, and one stop bit.
    core::outB(PORT + 3, 0x03);
    core::outB(PORT + 2, 0xC7);

    // Set to normal operation mode.
    core::outB(PORT + 4, 0x0F);
}

/* -------------------------------------------- */

/// Writes a byte to the serial port.
///
/// If the transmit buffer of the serial port is full, this function will wait until it is
/// emptied before writing the byte.
void write_byte(u8 byte) {
    // Wait until the transmit buffer of the serial port is empty.
    while ((core::inB(PORT + 5) & 0x20) == 0) {
        core::pause();
    }

    // Write the byte.
    core::outB(PORT, byte);
}

/// Writes a slice of bytes to the serial port.
void write_str(i8 const *bytes, u32 count) {
    while (count && *bytes) {
        write_byte(*bytes);
        bytes += 1;
        count -= 1;
    }
}

void write_nbr(u32 value) {
    i8 buf[32];
    u32 cur = 32;

    if (value == 0) {
        write_byte('0');
        return;
    }
    while (value) {
        --cur;
        buf[cur] = '0' + (value % 10);
        value /= 10;
    }

    write_str(buf + cur, 32 - cur);
}

} // namespace serial