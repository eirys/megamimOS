/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   balloc.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:33:13 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 15:00:02 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "balloc.h"
#include "panic.h"
#include "debug.h"

namespace mem {

static u32 g_ballocTop;
static u32 g_ballocBase;
static u32 g_ballocInitialTop;

bool ballocIsConsumed(u32 physicalFrame) {
    return physicalFrame >= g_ballocTop && physicalFrame < g_ballocInitialTop;
}

/**
 * @brief Initialize the bump allocator.
 */
void ballocInit(u32 top, u32 base) {
    g_ballocTop = top;
    g_ballocInitialTop = top;
    g_ballocBase = base;
    LOG("Initialized balloc with "); LOG_NUM(g_ballocTop - g_ballocBase); LOG(" bytes"); NL;
}

/**
 * @brief Bump allocator.
 */
void *balloc(u32 size, u32 align) {
    LOG("Allocating: "); LOG_NUM(size); LOG(" bytes with alignment "); LOG_NUM(align); NL;
    if (size > g_ballocTop - g_ballocBase) {
        beginKernelPanic("balloc: too big size");
        return nullptr;
    }

    const u32 mask = align - 1;
    const u32 addr = (g_ballocTop - size) & ~mask;

    if (addr < g_ballocBase) {
        beginKernelPanic("balloc: too big align");
        return nullptr;
    }

    g_ballocTop = addr;
    return (void*)addr;
}

} // namespace mem