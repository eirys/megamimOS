/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scancode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:40:41 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 17:01:32 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scancode.h"

namespace ui {

/* -------------------------------------------- */
/*                   SCANCODE                   */
/* -------------------------------------------- */

/**
 * @brief Scancode interpreter for a QWERTY keyboard layout.
 * @param input The input scancode.
 * @param isExtended Whether the scancode is part of an escape sequence.
 * @param modifiers The current modifier state.
 */
Key translateScancode(
    const u8 input,
    const bool isExtended,
    const Modifier modifiers
) {
    Key     out = Key::Unknown;
    bool    numlock = isNumlock(modifiers);

    switch (input) {
        /* --------- MISCELLANEOUS -------- */
        case 0x01: out = Key::Escape; break;

        /* --------- ALPHANUMERICS -------- */
        case 0x02: out = Key::Key1; break;
        case 0x03: out = Key::Key2; break;
        case 0x04: out = Key::Key3; break;
        case 0x05: out = Key::Key4; break;
        case 0x06: out = Key::Key5; break;
        case 0x07: out = Key::Key6; break;
        case 0x08: out = Key::Key7; break;
        case 0x09: out = Key::Key8; break;
        case 0x0A: out = Key::Key9; break;
        case 0x0B: out = Key::Key0; break;

        case 0x52: out = numlock ?      Key::Numpad0 : Key::Insert; break;
        case 0x4F: out = numlock ?      Key::Numpad1 : Key::End; break;
        case 0x50: out = isExtended ?   Key::CursorDown : (numlock ? Key::Numpad2 : Key::CursorDown); break;
        case 0x51: out = numlock ?      Key::Numpad3 : Key::PageDown ; break;
        case 0x4B: out = isExtended ?   Key::CursorLeft : (numlock? Key::Numpad4 : Key::CursorLeft); break;
        case 0x4C: out = Key::Numpad5; break;
        case 0x4D: out = isExtended ?   Key::CursorRight : (numlock ? Key::Numpad6 : Key::CursorRight); break;
        case 0x47: out = numlock ?      Key::Numpad7 : Key::Home; break;
        case 0x48: out = isExtended ?   Key::CursorUp : (numlock ? Key::Numpad8 : Key::CursorUp); break;
        case 0x49: out = numlock ?      Key::Numpad9 : Key::PageUp; break;

        case 0x10: out = Key::Q; break;
        case 0x11: out = Key::W; break;
        case 0x12: out = Key::E; break;
        case 0x13: out = Key::R; break;
        case 0x14: out = Key::T; break;
        case 0x15: out = Key::Y; break;
        case 0x16: out = Key::U; break;
        case 0x17: out = Key::I; break;
        case 0x18: out = Key::O; break;
        case 0x19: out = Key::P; break;

        case 0x1E: out = Key::A; break;
        case 0x1F: out = Key::S; break;
        case 0x20: out = Key::D; break;
        case 0x21: out = Key::F; break;
        case 0x22: out = Key::G; break;
        case 0x23: out = Key::H; break;
        case 0x24: out = Key::J; break;
        case 0x25: out = Key::K; break;
        case 0x26: out = Key::L; break;

        case 0x2C: out = Key::Z; break;
        case 0x2D: out = Key::X; break;
        case 0x2E: out = Key::C; break;
        case 0x2F: out = Key::V; break;
        case 0x30: out = Key::B; break;
        case 0x31: out = Key::N; break;
        case 0x32: out = Key::M; break;

        /* ------ SPECIAL CHARACTERS ------ */
        case 0x29: out = Key::Grave; break;
        case 0x27: out = Key::Semicolon; break;
        case 0x28: out = Key::Apostrophe; break;
        case 0x33: out = Key::Comma; break;
        case 0x34: out = Key::Dot; break;
        case 0x53: out = numlock ? Key::NumpadDot : Key::Delete; break;
        case 0x35: out = isExtended ? Key::NumpadSlash : Key::Slash; break;
        case 0x2B: out = Key::Backslash; break;

        case 0x0C: out = Key::Minus; break;
        case 0x4A: out = Key::NumpadMinus; break;
        case 0x4E: out = Key::NumpadPlus; break;
        case 0x37: out = Key::NumpadStar; break;
        case 0x0D: out = Key::Equals; break;
        case 0x1A: out = Key::LBracket; break;
        case 0x1B: out = Key::RBracket; break;

        case 0x39: out = Key::Space; break;
        case 0x1C: out = isExtended ? Key::NumpadEnter : Key::Enter; break;
        case 0x0E: out = Key::Backspace; break;
        case 0x0F: out = Key::Tab; break;

        /* ----------- MODIFIERS ---------- */
        case 0x3A: out = Key::Caps; break;
        case 0x45: out = Key::NumLock; break;

        case 0x2A: out = Key::LShift; break;
        case 0x36: out = Key::RShift; break;
        case 0x38: out = isExtended ? Key::RAlt : Key::LAlt; break;
        case 0x1D: out = isExtended ? Key::RCtrl : Key::LCtrl; break;

        default: break;
    }
    return out;
}

/* -------------------------------------------- */

static
void _setMod(Modifier& modifiers, const Modifier newMod, const bool pressed) {
    if (pressed) { modifiers |= newMod; }
    else         { modifiers &= ~newMod; }
}

static
void _setLock(Modifier& modifiers, const Modifier newMod, const bool pressed) {
    if (pressed) { modifiers ^= newMod; }
}

bool setModifiers(
    Modifier& modifiers,
    const Key key,
    const bool isPressed
) {
    switch (key) {
        case Key::LShift:   _setMod(modifiers, Modifier::LShift, isPressed); break;
        case Key::LAlt:     _setMod(modifiers, Modifier::LAlt, isPressed); break;
        case Key::LCtrl:    _setMod(modifiers, Modifier::LCtrl, isPressed); break;
        case Key::RShift:   _setMod(modifiers, Modifier::RShift, isPressed); break;
        case Key::RAlt:     _setMod(modifiers, Modifier::RAlt, isPressed); break;
        case Key::RCtrl:    _setMod(modifiers, Modifier::RCtrl, isPressed); break;
        case Key::Caps:     _setLock(modifiers, Modifier::Caps, isPressed); break;
        case Key::NumLock:  _setLock(modifiers, Modifier::Num, isPressed); break;

        default: return false;
    }
    return true;
}

} // namespace ui