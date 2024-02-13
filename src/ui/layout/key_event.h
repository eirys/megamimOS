/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:13:09 by etran             #+#    #+#             */
/*   Updated: 2024/02/13 00:07:31 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"
# include "keys.h"
# include "utils.h"

namespace ui {

enum class Action: u8 {
    Released    = 0,
    Pressed     = 1,
    Repeat      = 2, // Not used

    First       = Released,
    Last        = Repeat
};

/**
 * @brief Represents a key event.
 * Used to store the state of a key and the translater character it represents.
*/
struct KeyEvent {
    Action      m_action;
    Key         m_key;
    vga::Char   m_character;

    bool        m_uppercase;
    bool        m_control;
    bool        m_alt;
};

/**
 * @brief Bitmask of modifier keys.
*/
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

/**
 * @brief Checks if the modifier contains the Shift key.
 */
static inline
bool isShifted(const Modifier mods) {
    return (bool)(mods & (Modifier::LShift | Modifier::RShift));
}

/**
 * @brief Verifies that either the Caps or the Shift modifier is set.
 */
static inline
bool isUppercase(const Modifier mods) {
    return  (bool)(mods & Modifier::Caps) ^
            isShifted(mods);
}

/**
 * @brief Returns whether the input is pressed or released.
 */
static inline
Action isPressed(const u8 input) {
    return (input & 0x80) ? Action::Released : Action::Pressed;
}

/**
 * @brief Verifies that numlock is set.
 */
static inline
bool isNumlock(const Modifier mods) {
    return (bool)(mods & Modifier::Num);
}

static inline
bool isControl(const Modifier mods) {
    return (bool)(mods & (Modifier::LCtrl | Modifier::RCtrl));
}

static inline
bool isAlt(const Modifier mods) {
    return (bool)(mods & (Modifier::LAlt | Modifier::RAlt));
}

} // namespace ui