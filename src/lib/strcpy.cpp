/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcpy.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:08:10 by etran             #+#    #+#             */
/*   Updated: 2024/02/09 16:07:09 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

namespace lib {

u8* strcpy(u8* dest, const u8* src) noexcept {
    u32 i = 0;
    while (*src) {
        dest[i] = *src++;
        ++i;
    }
    dest[i] = '\0';
    return dest;
}

} // namespace lib
