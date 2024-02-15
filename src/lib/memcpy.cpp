/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:02:25 by etran             #+#    #+#             */
/*   Updated: 2024/02/09 20:46:50 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

namespace lib {

void* memcpy(void* dest, const void* src, u32 n) noexcept {
    u8* d = (u8*)dest;
    u8* s = (u8*)src;
    for (u32 i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

} // namespace lib
