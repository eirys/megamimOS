/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps2.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:40:56 by etran             #+#    #+#             */
/*   Updated: 2024/02/04 22:42:19 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

namespace ps2 {

constexpr const uint8_t DATA_PORT = 0x60;
constexpr const uint8_t COMMAND_PORT = 0x64;

static inline
uint8_t in_b(uint16_t port)
{
    uint8_t ret;

    asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

static inline
void pause()
{
	asm volatile ("pause");
}

static inline
uint8_t readStatus() {
    return in_b(COMMAND_PORT);
}

static inline
uint8_t readData() {
    return in_b(DATA_PORT);
}

static inline
bool isOutputFull() {
    uint8_t status = readStatus();

    // check bit de buffer full
    return status & 0x01;
}

} // namespace ps2
