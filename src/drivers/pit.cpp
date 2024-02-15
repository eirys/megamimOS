/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pit.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmathieu <nmathieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:41:36 by nmathieu          #+#    #+#             */
/*   Updated: 2024/02/15 14:54:55 by nmathieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "core.h"

namespace pit  {

constexpr u16 DATA_PORT = 0x40;
constexpr u16 COMMAND_PORT = 0x43;

constexpr u32 MAX_FREQUENCY = 1193181;
constexpr u32 MIN_FREQUENCY = 10;

/// @brief The frequency of the PIT, multiplied by 3.
///
/// Using a value multiplied by 3 allows us to avoid floating point
/// and rounding errors during computations.
constexpr u32 PIC_FREQ_TIMES_3 = 3579545;

/// @brief The number of microseconds in a tick sent by the PIT. Note that
/// this value may drift over time due to the PIT's lack of precision (usually
/// a couple seconds per day);
u32 tickDurationMicros;

/// @brief Divides two numbers and rounds the result to the nearest integer (rather
/// than simply returning the closest integer to 0 as a simple division would when
/// using the `/` operator).
static
u32 divideRounded(u32 num, u32 denom) {
    return (num + denom / 2) / denom;
}

/// @brief Converts a frequency in Hertz to a reload value for the PIT.
static
u32 freqToReloadValue(u32 freq) {
    if (freq <= MIN_FREQUENCY)
        return 0x10000;
    else if (freq >= MAX_FREQUENCY)
        return 1;
    else
        return divideRounded(PIC_FREQ_TIMES_3, 3 * freq);
}

/// @brief Converts a reload value understood by the PIT to a period in
/// microseconds.
static
u32 reloadValueToMicros(u32 reloadValue) {
    constexpr u32 microsecsPerSecond = 1000000;
    return divideRounded(3 * reloadValue * microsecsPerSecond, PIC_FREQ_TIMES_3);
}

/// @brief Initializes the PIT to send ticks at the given frequency.
void init(u32 frequency) {
    u32 reloadValue = freqToReloadValue(frequency);
    tickDurationMicros = reloadValueToMicros(reloadValue);
    core::outB(COMMAND_PORT, 0b110100);
    core::outB(DATA_PORT, (u8)reloadValue);
    core::outB(DATA_PORT, (u8)(reloadValue >> 8));
}

}
