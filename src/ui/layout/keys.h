/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:47:51 by etran             #+#    #+#             */
/*   Updated: 2024/02/07 21:33:56 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"

namespace ui {

/**
 * @brief Corresponds to a key on a generic US keyboard layout.
 * @note The numpad keys are meant to be included.
 */
enum class Key: u8 {
    /* ---------------------------------------- */
    /*                REGULAR KEY               */
    /* ---------------------------------------- */

    /* ------------- SPECIAL KEYS ------------- */

    Escape = 0,

    /* ------------- ALPHANUMERIC ------------- */

    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    Key0,

    Q,
    W,
    E,
    R,
    T,
    Y,
    U,
    I,
    O,
    P,

    A,
    S,
    D,
    F,
    G,
    H,
    J,
    K,
    L,

    Z,
    X,
    C,
    V,
    B,
    N,
    M,

    /* ------------- MISCELLANEOUS ------------ */

    Space,

    Minus,
    Equals,

    Backspace,
    Tab,
    Enter,

    LBracket,
    RBracket,

    Dot,
    Comma,
    Semicolon,

    Grave,
    Quote,

    Backslash,
    Slash,

    /* --------------- MODIFIERS -------------- */

    LShift,
    LAlt,
    LCtrl,

    RShift,
    RAlt,
    RCtrl,

    Caps,

    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,

    /* ---------------------------------------- */
    /*                NUMPAD KEY                */
    /* ---------------------------------------- */

    NumLock,
    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad7,
    Numpad8,
    Numpad9,
    Numpad4,
    Numpad5,
    Numpad6,
    NumpadAdd,
    NumpadSubtract,
    NumpadMultiply,
    NumpadDot,
    NumpadEnter,
    NumpadSlash,

    /* ------------- ARROW KEYS --------------- */

    CursorUp,
    CursorDown,
    CursorLeft,
    CursorRight,

    First = Escape,
    Last  = CursorRight

}; // enum class Key

} // namespace ui
