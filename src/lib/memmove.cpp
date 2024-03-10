/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 20:47:02 by etran             #+#    #+#             */
/*   Updated: 2024/02/09 20:47:22 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

namespace lib {

void* memmove(void *dest, void const *src, u32 n) noexcept {
    u8* d = (u8*)dest;
    u8* s = (u8*)src;
    if (d < s) {
        for (u32 i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else {
        for (u32 i = n; i > 0; i--) {
            d[i - 1] = s[i - 1];
        }
    }
    return dest;
}

} // namespace lib
