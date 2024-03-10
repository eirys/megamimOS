/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address_space.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:45:45 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 16:56:55 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "address_space.h"
#include "balloc.h"
#include "panic.h"
#include "lib.h"
#include "debug.h"

namespace mem {

/* -------------------------------------------- */
/*                STATIC MEMBERS                */
/* -------------------------------------------- */

static constexpr u32 HUGE_PAGE = 1 << 7;
static constexpr u32 PRESENT_FLAG = 1 << 0;

static constexpr u32 FOUR_KIB = 4096;
static constexpr u32 FOUR_MIB = 4096 * 1024;

static constexpr u32 PAGE_TABLE_SIZE = 1024;

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

AddressSpace::AddressSpace() {
    m_cr3 = (u32)balloc(PAGE_TABLE_SIZE * sizeof(u32), FOUR_KIB);
    lib::memset((void*)m_cr3, 0, PAGE_TABLE_SIZE * sizeof(u32));
}

/* -------------------------------------------- */

bool AddressSpace::createMapping4Kib(u32 virtualAddress, u32 physicalAddress, Flags flags) {
#ifdef _DEBUG
    if (physicalAddress & 0xFFF) {
        beginKernelPanic("createMapping4Kib: physicalAddress is not aligned to 4K");
        return false;
    }
#endif

    u32*        pagesDirectory = (u32*)m_cr3;
    const u32   pagesDirectoryEntryIndex = virtualAddress >> 22;
    u32*        pagesDirectoryEntry = pagesDirectory + pagesDirectoryEntryIndex;

    if (!(*pagesDirectoryEntry & PRESENT_FLAG)) {
        *pagesDirectoryEntry = (u32)balloc(PAGE_TABLE_SIZE * sizeof(u32), FOUR_KIB);
        lib::memset((void*)*pagesDirectoryEntry, 0, PAGE_TABLE_SIZE * sizeof(u32));
        *pagesDirectoryEntry |= PRESENT_FLAG | (u32)flags;
    }  else if (*pagesDirectoryEntry & HUGE_PAGE) {
        return false;
    } else {
        if ((*pagesDirectoryEntry & (u32)Flags::Writable) && !((u32)flags & (u32)Flags::Writable)) {
            *pagesDirectoryEntry &= ~(u32)Flags::Writable;
        }
    }

    u32*        pagesTable = (u32*)(*pagesDirectoryEntry & ~0xFFF);
    const u32   pagesTableEntryIndex = (virtualAddress >> 12) & 0x3FF;
    u32*        pagesTableEntry = pagesTable + pagesTableEntryIndex;

    if (*pagesTableEntry & PRESENT_FLAG)
        return false;

    *pagesTableEntry |= physicalAddress | PRESENT_FLAG | (u32)flags;

    return true;
}

bool AddressSpace::createMapping4Mib(u32 virtualAddress, u32 physicalAddress, Flags flags) {
#ifdef _DEBUG
    if (physicalAddress & 0x3FFFFF) {
        beginKernelPanic("createMapping4Mib: physicalAddress is not aligned to 4M");
        return false;
    }
#endif

    u32*        pagesDirectory = (u32*)m_cr3;
    const u32   pagesDirectoryEntryIndex = virtualAddress >> 22;
    u32*        pagesDirectoryEntry = pagesDirectory + pagesDirectoryEntryIndex;

    if (*pagesDirectoryEntry & PRESENT_FLAG) {
        return false;
    }

    *pagesDirectoryEntry = physicalAddress | PRESENT_FLAG | HUGE_PAGE | (u32)flags;

    return true;
}

bool AddressSpace::createMapping(u32 virtualBase, u32 physicalBase, u32 size, Flags flags) {
#ifdef _DEBUG
    if (virtualBase % FOUR_KIB != 0 || physicalBase != 0 || size % FOUR_KIB != 0) {
        beginKernelPanic("createMapping: invalid alignment or size");
        return false;
    }
#endif

    while (size) {
        if (virtualBase % FOUR_MIB == 0 &&
            physicalBase % FOUR_MIB == 0 &&
            size >= FOUR_MIB
        ) {
            if (!createMapping4Mib(virtualBase, physicalBase, flags))
                return false;
            virtualBase += FOUR_MIB;
            physicalBase += FOUR_MIB;
            size -= FOUR_MIB;
        } else {
            if (!createMapping4Kib(virtualBase, physicalBase, flags))
                return false;
            virtualBase += FOUR_KIB;
            physicalBase += FOUR_KIB;
            size -= FOUR_KIB;
        }
    }

    return true;
}

} // namespace mem
