/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scancode.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:14:41 by etran             #+#    #+#             */
/*   Updated: 2024/02/06 16:08:10 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"
#include "keys.h"
#include "utils.h"

namespace ui {

enum class Action: u8 {
    Released    = 0,
    Pressed     = 1,
    Repeat      = 2,

    First       = Released,
    Last        = Repeat
};

struct KeyEvent {
    Action      action;
    Key         key;
    vga::Char   character;
};

enum class Modifier: u8 {
    None    = 0,

    // Press state
    LShift  = 1 << 0,
    LAlt    = 1 << 1,
    LCtrl   = 1 << 2,

    RShift  = 1 << 3,
    RAlt    = 1 << 4,
    RCtrl   = 1 << 5,

    // Lock state
    Caps    = 1 << 6,
    Num     = 1 << 7
};

static inline
Modifier operator|(const Modifier lhs, const Modifier rhs) {
    return static_cast<Modifier>(static_cast<u8>(lhs) | static_cast<u8>(rhs));
}

static inline
Modifier& operator|=(Modifier& lhs, const Modifier rhs) {
    lhs = static_cast<Modifier>(static_cast<u8>(lhs) | static_cast<u8>(rhs));
    return lhs;
}

static inline
Modifier operator^(const Modifier lhs, const Modifier rhs) {
    return static_cast<Modifier>(static_cast<u8>(lhs) ^ static_cast<u8>(rhs));
}

static inline
Modifier& operator^=(Modifier& lhs, const Modifier rhs) {
    lhs = static_cast<Modifier>(static_cast<u8>(lhs) ^ static_cast<u8>(rhs));
    return lhs;
}

static inline
Modifier operator&(const Modifier lhs, const Modifier rhs) {
    return static_cast<Modifier>(static_cast<u8>(lhs) & static_cast<u8>(rhs));
}

static inline
Modifier& operator&=(Modifier& lhs, const Modifier rhs) {
    lhs = static_cast<Modifier>(static_cast<u8>(lhs) & static_cast<u8>(rhs));
    return lhs;
}

static inline
Modifier operator~(const Modifier value) {
    return static_cast<Modifier>(~static_cast<u8>(value));
}

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

static inline
bool isShifted(const Modifier mods) {
    return (bool)(mods & (Modifier::LShift | Modifier::RShift));
}

static inline
bool isUppercase(const Modifier mods) {
    return  (bool)(mods & Modifier::Caps) ^
            isShifted(mods);
}

static inline
Action isPressed(const u8 input) {
    return (input & 0x80) ? Action::Pressed : Action::Released;
}

/**
 * @brief Removes the RELEASED bit from the input.
 */
static inline
u8 toReleased(const u8 input) {
    return input & 0x7F;
}

/**
 * @brief Adds the pressed byte to the input.
*/
static inline
bool isExtend(const u8 input) {
    return input == 0xE0;
}

} // namespace ui