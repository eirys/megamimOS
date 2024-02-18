/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balloc.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:33:13 by etran             #+#    #+#             */
/*   Updated: 2024/02/18 21:52:05 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "balloc.h"

namespace mem {

static u32 g_ballocTop;
static u32 g_ballocBase;

/**
 * @brief Initialize the bump allocator.
 */
void ballocInit(u32 top, u32 base) {
    g_ballocTop = top;
    g_ballocBase = base;
}

/**
 * @brief Bump allocator.
 */
void *balloc(u32 size, u32 align) {
    if (size < g_ballocTop - g_ballocBase) {
        return nullptr;
    }

    const u32 mask = align - 1;
    const u32 addr = (g_ballocTop - size) & ~mask;

    if (addr < g_ballocBase) {
        return nullptr;
    }

    g_ballocTop = addr;
    return (void*)addr;
}

} // namespace mem