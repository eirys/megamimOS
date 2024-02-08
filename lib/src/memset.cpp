/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:57:23 by etran             #+#    #+#             */
/*   Updated: 2024/02/08 20:59:18 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../types.h"

namespace lib {

i32* memset(i32* dest, i32 value, u32 n) noexcept {
    for (u32 i = 0; i < n; i++) {
        dest[i] = value;
    }
    return dest;
}

} // namespace lib
