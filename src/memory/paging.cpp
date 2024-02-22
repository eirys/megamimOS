/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paging.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:44:57 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 14:45:51 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "paging.h"
#include "address_space.h"
#include "panic.h"
#include "debug.h"

namespace mem {

extern "C"
void enable_paging(const u32 cr3);

void init(u32 upperBound) {
    AddressSpace s_kernelAddressSpace;

    upperBound = (upperBound + 0xFFF) & ~0xFFF;
    LOG("Creating the kernel address space ("); LOG_NUM(upperBound); LOG(" bytes)"); NL;

    if (!s_kernelAddressSpace.createMapping(0x00000000, 0x00000000, upperBound, AddressSpace::Flags::Writable))
        beginKernelPanic("mem::init: mapping failed");

    // Remap at 0x66666000 for testing purposes
    if (!s_kernelAddressSpace.createMapping4Kib(0x66666000, 0, AddressSpace::Flags::None))
        beginKernelPanic("mem::init: mapping failed");

    enable_paging(s_kernelAddressSpace.getCR3());
}

} // namespace mem