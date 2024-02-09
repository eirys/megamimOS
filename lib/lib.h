/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:40:29 by etran             #+#    #+#             */
/*   Updated: 2024/02/09 16:43:44 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"

namespace lib {

u32     strlen(const u8* str) noexcept;
u8*     strcpy(u8* dest, const u8* src) noexcept;

i32*    memcpy(i32* dest, const i32* src, u32 n) noexcept;
i32*    memset(i32* dest, i32 value, u32 n) noexcept;
void*   memmove(void *dest, void const *src, u32 n) noexcept;

} // namespace lib