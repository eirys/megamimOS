/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paging.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:44:57 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 14:56:58 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paging.h"
#include "address_space.h"
#include "panic.h"
#include "debug.h"
#include "balloc.h"

namespace mem {

static u32 *s_freePages;
static u32 s_maxFreePages;
static u32 s_totalFreePages;

u32 kalloc(void) {
    if (s_totalFreePages == 0)
        return 0;

    s_totalFreePages--;
    return s_freePages[s_totalFreePages];
}

void kfree(u32 physicalFrame) {
    if (s_totalFreePages == s_maxFreePages)
        beginKernelPanic("kfree: freed more pages than possible");

    s_freePages[s_totalFreePages] = physicalFrame;
    s_totalFreePages++;
}

void kinit(u32 maxFreePages) {
    s_freePages = (u32*)balloc(maxFreePages * sizeof(u32), alignof(u32));
    s_totalFreePages = 0;
    s_maxFreePages = maxFreePages;
}

extern "C"
void enable_paging(const u32 cr3);

void init(u32 upperBound) {
    AddressSpace kernelAddressSpace;

    upperBound = (upperBound + 0xFFF) & ~0xFFF;
    LOG("Creating the kernel address space ("); LOG_NUM(upperBound); LOG(" bytes)"); NL;

    if (!kernelAddressSpace.createMapping(0x00000000, 0x00000000, upperBound, AddressSpace::Flags::Writable))
        beginKernelPanic("mem::init: mapping failed");

    // Remap at 0x66666000 for testing purposes
    if (!kernelAddressSpace.createMapping4Kib(0x66666000, 0, AddressSpace::Flags::None))
        beginKernelPanic("mem::init: mapping failed");

    enable_paging(kernelAddressSpace.getCR3());
}

} // namespace mem