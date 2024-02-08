/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:02:25 by etran             #+#    #+#             */
/*   Updated: 2024/02/08 20:58:56 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../types.h"

namespace lib {

i32* memcpy(i32* dest, const i32* src, u32 n) noexcept {
    for (u32 i = 0; i < n; i++) {
        dest[i] = src[i];
    }
    return dest;
}

} // namespace lib
