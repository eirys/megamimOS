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

u32 tick_duration_ns;

static
u32 divide_rounded(u32 num, u32 denom) {
    return (num + denom / 2) / denom;
}

static
u32 freq_to_reload_value(u32 freq) {
    if (freq <= 10)
        return 0x10000;
    else if (freq >= 1193181)
        return 1;
    else
        return divide_rounded(3579545, 3 * freq);
}

static
u32 reload_value_to_ns(u32 reload_value) {
    return divide_rounded(3 * reload_value * 1000000000, 3579545);
}

void init(u32 frequency) {
    u32 reload_value = freq_to_reload_value(frequency);
    tick_duration_ns = reload_value_to_ns(reload_value);
    core::outB(0x43, 0b110100);
    core::outB(0x40, (u8)reload_value);
    core::outB(0x40, (u8)(reload_value >> 8));
}

}
