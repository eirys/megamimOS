/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:40:29 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 18:57:20 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace lib {

u32     strlen(const i8* str) noexcept;
u8*     strcpy(u8* dest, const u8* src) noexcept;
i32     strcmp(const i8* s1, const i8* s2) noexcept;

void*   memcpy(void* dest, const void* src, u32 n) noexcept;
void*   memset(void* dest, i32 value, u32 n) noexcept;
void*   memmove(void *dest, void const *src, u32 n) noexcept;
i32     memcmp(const void* s1, const void* s2, u32 n) noexcept;

} // namespace lib
