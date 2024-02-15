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

/// @brief The number of nanoseconds in a tick sent by the PIT. Note that
/// this value may drift over time due to the PIT's lack of precision (usually
/// a couple seconds per day);
u32 tick_duration_ns;

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
    if (freq <= 10)
        return 0x10000;
    else if (freq >= 1193181)
        return 1;
    else
        return divideRounded(3579545, 3 * freq);
}

/// @brief Converts a reload value understood by the PIT to a period in
/// nanoseconds.
static
u32 reloadValueToNs(u32 reload_value) {
    return divideRounded(3 * reload_value * 1000000000, 3579545);
}

/// @brief Initializes the PIT to send ticks at the given frequency.
void init(u32 frequency) {
    u32 reload_value = freqToReloadValue(frequency);
    tick_duration_ns = reloadValueToNs(reload_value);
    core::outB(0x43, 0b110100);
    core::outB(0x40, (u8)reload_value);
    core::outB(0x40, (u8)(reload_value >> 8));
}

}
