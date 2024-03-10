/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kalloc.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:33:04 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 16:42:27 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kalloc.h"
#include "balloc.h"
#include "panic.h"

namespace mem {

static u32 *s_freePages;
static u32 s_maxFreePages;
static u32 s_totalFreePages;

/**
 * @brief Initialize the kernel allocator.
*/
void kinit(u32 maxFreePages) {
    s_freePages = (u32*)balloc(maxFreePages * sizeof(u32), alignof(u32));
    s_totalFreePages = 0;
    s_maxFreePages = maxFreePages;
}

/**
 * @brief Allocate a page.
*/
u32 kalloc() {
    if (s_totalFreePages == 0)
        return 0;

    --s_totalFreePages;
    return s_freePages[s_totalFreePages];
}

/**
 * @brief Free a page.
*/
void kfree(u32 physicalFrame) {
    if (s_totalFreePages == s_maxFreePages)
        beginKernelPanic("kfree: freed more pages than possible");

    s_freePages[s_totalFreePages] = physicalFrame;
    ++s_totalFreePages;
}

/**
 * @brief Allocate a page with a valid pointer.
*/
void* valloc() {
    return (void*)kalloc();
}

} // namespace mem