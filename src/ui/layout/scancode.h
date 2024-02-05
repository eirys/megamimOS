/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scancode.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:14:41 by etran             #+#    #+#             */
/*   Updated: 2024/02/06 00:50:37 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"
#include "keys.h"
#include "utils.h"

namespace ui {

struct KeyEvent {
    Key         key;
    vga::Char   character;
    bool        pressed;
};

enum class Modifier: u8 {
    None    = 0,
    LShift  = 1 << 0,
    LAlt    = 1 << 1,
    LCtrl   = 1 << 2,

    RShift  = 1 << 3,
    RAlt    = 1 << 4,
    RCtrl   = 1 << 5,

    Caps    = 1 << 6,
    Num     = 1 << 7
};

// class Modifier final {
// public:
//     /* ---------------------------------------- */
//     /*                  METHODS                 */
//     /* ---------------------------------------- */

//     Modifier() = default;
//     Modifier(Modifier&& rhs) = default;
//     Modifier(const Modifier& rhs) = default;
//     Modifier& operator=(Modifier&& rhs) = default;
//     Modifier& operator=(const Modifier& rhs) = default;
//     ~Modifier() = default;

//     /* ---------------------------------------- */

//     inline
//     bool operator&(const ModifierFlag mod) const {
//         return hasFlag<ModifierFlag>(m_flags, mod);
//     }

//     inline
//     void operator&=(const ModifierFlag mod) {
//         m_flags = static_cast<ModifierFlag>(static_cast<u8>(m_flags) & ~static_cast<u8>(mod));
//     }

//     inline
//     ModifierFlag operator|(const ModifierFlag mod) const {
//         return addFlag<ModifierFlag>(m_flags, mod);
//     }

//     inline
//     void operator|=(const ModifierFlag mod) {
//         m_flags = addFlag<ModifierFlag>(m_flags, mod);
//     }

// private:
//     /* ---------------------------------------- */
//     /*                   DATA                   */
//     /* ---------------------------------------- */

//     ModifierFlag  m_flags = ModifierFlag::None;

// }; // class Modifier

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

static inline
bool isShifted(const Modifier mods) {
    // return (mod & Modifier::LShift) || (mod & Modifier::RShift);
    return  hasFlag<Modifier>(mods, Modifier::LShift) ||
            hasFlag<Modifier>(mods, Modifier::RShift);
}

static inline
bool isUppercase(const Modifier mods) {
    // return (mods & Modifier::Caps) ^ isShifted(mods);
    return  hasFlag<Modifier>(mods, Modifier::Caps) ^
            isShifted(mods);
}

static inline
bool isPressed(const u8 scancode) {
    return (scancode & 0x80) == 0;
}

static inline
u8 toPressed(const u8 scancode) {
    return scancode & 0x7F;
}

} // namespace ui