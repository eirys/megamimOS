/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcmp.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:06:57 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 11:08:38 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../types.h"

namespace lib {

i32 memcmp(const void* s1, const void* s2, u32 n) noexcept {
    const u8* p1 = (const u8*)s1;
    const u8* p2 = (const u8*)s2;

    for (u32 i = 0; i < n; i++) {
        if (p1[i] != p2[i]) {
            return p1[i] - p2[i];
        }
    }
    return 0;
}

} // namespace lib