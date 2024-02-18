/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiboot.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 20:25:46 by etran             #+#    #+#             */
/*   Updated: 2024/02/18 21:46:29 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"

namespace multiboot {

enum class MemoryType {
    Available       = 1,
    Reserved        = 2,
    AcpiReclaimable = 3,
    AcpiNvs         = 4,
    BadMemory       = 5
};

struct MemoryMap {
    u32 size;
    u32 base_addr_low;
    u32 base_addr_high;
    u32 length_low;
    u32 length_high;
    u32 type;
};

class MmapIterator {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    MmapIterator(u32 mmapAddr, u32 mmapLength):
        m_remainingLength(mmapLength),
        m_currentAddr((MemoryMap*)mmapAddr) {}

    MmapIterator() = delete;

    /* ------------------------------------ */

    bool next(MemoryMap& memMap) {
        if (m_remainingLength == 0) {
            return false;
        }

        memMap = *m_currentAddr;
        m_currentAddr = (MemoryMap*)((u32)m_currentAddr + m_currentAddr->size + 4);
        m_remainingLength -= m_currentAddr->size + 4;
        return true;
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    u32         m_remainingLength;
    MemoryMap*  m_currentAddr;

};

struct Info {
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    u32 m_flags;
    u32 m_mem_lower;
    u32 m_mem_upper;
    u32 m_boot_device;
    u32 m_cmdline;
    u32 m_mods_count;
    u32 m_mods_addr;
    u32 m_syms[4];

    u32 m_mmap_length;
    u32 m_mmap_addr;

    u32 m_drives_length;
    u32 m_drives_addr;
    u32 m_config_table;
    u32 m_boot_loader_name;
    u32 m_apm_table;
    u32 m_vbe_control_info;
    u32 m_vbe_mode_info;
    u32 m_vbe_mode;
    u32 m_vbe_interface_seg;
    u32 m_vbe_interface_off;
    u32 m_vbe_interface_len;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    inline
    MmapIterator mmapIterator() const {
        return MmapIterator(m_mmap_addr, m_mmap_length);
    }

    bool getLargestMemoryRegion(MemoryMap& largest) const {
        MmapIterator iter = mmapIterator();

        MemoryMap memMap;
        if (!iter.next(largest)) {
            return false;
        }

        while (iter.next(memMap)) {
            if (memMap.type == (u32)MemoryType::Available) {
                if (memMap.length_low > largest.length_low) {
                    largest = memMap;
                }
            }
        }
        return true;
    }

};

struct Module {
    u32 mod_start;
    u32 mod_end;
    u32 string;
    u32 reserved;
};


} // namespace multiboot