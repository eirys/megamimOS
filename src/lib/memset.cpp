/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:57:23 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 15:55:22 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

namespace lib {

void* memset(void* dest, i32 value, u32 n) noexcept {
    i32* d = (i32*)dest;
    for (u32 i = 0; i < n; i++) {
        d[i] = value;
    }
    return dest;
}

} // namespace lib

extern "C" void* memset(void *dst, i32 value, u32 n)  {
    return lib::memset(dst, value, n);
}
