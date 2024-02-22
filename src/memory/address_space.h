/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   address_space.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:23:18 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 13:37:26 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace mem {

class AddressSpace final {
public:
    /* ---------------------------------------- */
    /*                   ENUMS                  */
    /* ---------------------------------------- */

    enum class Flags: u32 {
        // Present      = 1 << 0, // Not available for users
        Writable        = 1 << 1,
        User            = 1 << 2,
        WriteThrough    = 1 << 3,
        CacheDisable    = 1 << 4,
        Dirty           = 1 << 6,
        // HugePage     = 1 << 7, // Not available for users
        Global          = 1 << 8,
    };

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    AddressSpace();

    ~AddressSpace() = default;

    AddressSpace(AddressSpace&& other) = delete;
    AddressSpace(const AddressSpace& other) = delete;
    AddressSpace& operator=(AddressSpace&& other) = delete;
    AddressSpace& operator=(const AddressSpace& other) = delete;

    /* ---------------------------------------- */

    // Creates a mapping from `virtualAddress` to `physicalAddress` with a
    // 4K page. `virtualAddress` and `physicalAddress` must be aligned to 4K.
    //
    // ### Returns
    //
    // Returns `true` if the mapping was created successfully, `false` if the
    // page was already mapped to some other physical address.
    bool createMapping4Kib(u32 virtualAddress, u32 physicalAddress, Flags flags);

    // Creates a mapping from `virtualAddress` to `physicalAddress` with a
    // 2M page. `virtualAddress` and `physicalAddress` must be aligned to 2M.
    //
    // ### Returns
    //
    // Returns `true` if the mapping was created successfully, `false` if the
    // page was already mapped to some other physical address.
    bool createMapping4Mib(u32 virtualAddress, u32 physicalAddress, Flags flags);

    // `virtualBase` and `physicalBase` must be aligned to 4K.
    bool createMapping(u32 virtualBase, u32 physicalBase, u32 size, Flags flags);

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    u32 m_cr3;

}; // class AddressSpace

} // namespace mem
