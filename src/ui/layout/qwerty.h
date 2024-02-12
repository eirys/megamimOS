/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwerty.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:44:59 by etran             #+#    #+#             */
/*   Updated: 2024/02/12 00:27:06 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "key_event.h"
#include "ilayout.h"
#include "vga.h"

namespace ui {

/**
 * @brief Scancode interpreter for the US-QWERTY layout.
 */
class QwertyLayout final: public ILayout {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    QwertyLayout() = default;
    ~QwertyLayout() = default;

    QwertyLayout(QwertyLayout&& other) = delete;
    QwertyLayout(const QwertyLayout& other) = delete;
    QwertyLayout& operator=(QwertyLayout&& other) = delete;
    QwertyLayout& operator=(const QwertyLayout& other) = delete;

    /* ---------------------------------------- */

    /**
     * @brief Given a scancode, translates it to a KeyEvent.
     * @param input The scancode to translate.
     * @param out The output KeyEvent.
     */
    TranslateResult translate(const u8 input, KeyEvent& out) override {
        out.m_character = vga::Char::Empty;
        out.m_action = isPressed(input);

        if (input == 0xE0) {
            // The scancode is part of an escape sequence.
            m_isExtended = true;
            return TranslateResult::Ignore;
        }

        const bool isExtended = m_isExtended;
        m_isExtended = false;

        if (!_translateKey(input & 0x7F, isExtended, out.m_key)) {
            return TranslateResult::Invalid;
        }

        if (_setModifiers(out, isExtended)) {
            return TranslateResult::Ignore;
        }

        if (out.m_action == Action::Released) {
            return TranslateResult::Ignore;
        }

        out.m_uppercase = isUppercase(m_modifiers);

        switch (out.m_key) {
            /* -------------------------------- */
            /*       PRINTABLE CHARACTERS       */
            /* -------------------------------- */

            case Key::Key1:         out.m_character = out.m_uppercase ? '!' : '1'; break;
            case Key::Key2:         out.m_character = out.m_uppercase ? '@' : '2'; break;
            case Key::Key3:         out.m_character = out.m_uppercase ? '#' : '3'; break;
            case Key::Key4:         out.m_character = out.m_uppercase ? '$' : '4'; break;
            case Key::Key5:         out.m_character = out.m_uppercase ? '%' : '5'; break;
            case Key::Key6:         out.m_character = out.m_uppercase ? '^' : '6'; break;
            case Key::Key7:         out.m_character = out.m_uppercase ? '&' : '7'; break;
            case Key::Key8:         out.m_character = out.m_uppercase ? '*' : '8'; break;
            case Key::Key9:         out.m_character = out.m_uppercase ? '(' : '9'; break;
            case Key::Key0:         out.m_character = out.m_uppercase ? ')' : '0'; break;

            case Key::Minus:        out.m_character = out.m_uppercase ? '_' : '-'; break;
            case Key::Equals:       out.m_character = out.m_uppercase ? '+' : '='; break;

            case Key::LBracket:     out.m_character = out.m_uppercase ? '{' : '['; break;
            case Key::RBracket:     out.m_character = out.m_uppercase ? '}' : ']'; break;
            case Key::Semicolon:    out.m_character = out.m_uppercase ? ':' : ';'; break;
            case Key::Quote:        out.m_character = out.m_uppercase ? '"' : '\''; break;
            case Key::Comma:        out.m_character = out.m_uppercase ? '<' : ','; break;
            case Key::Dot:          out.m_character = out.m_uppercase ? '>' : '.'; break;
            case Key::Slash:        out.m_character = out.m_uppercase ? '?' : '/'; break;
            case Key::Backslash:    out.m_character = out.m_uppercase ? '|' : '\\'; break;
            case Key::Grave:        out.m_character = out.m_uppercase ? '~' : '`'; break;

            case Key::A:            out.m_character = out.m_uppercase ? 'A' : 'a'; break;
            case Key::B:            out.m_character = out.m_uppercase ? 'B' : 'b'; break;
            case Key::C:            out.m_character = out.m_uppercase ? 'C' : 'c'; break;
            case Key::D:            out.m_character = out.m_uppercase ? 'D' : 'd'; break;
            case Key::E:            out.m_character = out.m_uppercase ? 'E' : 'e'; break;
            case Key::F:            out.m_character = out.m_uppercase ? 'F' : 'f'; break;
            case Key::G:            out.m_character = out.m_uppercase ? 'G' : 'g'; break;
            case Key::H:            out.m_character = out.m_uppercase ? 'H' : 'h'; break;
            case Key::I:            out.m_character = out.m_uppercase ? 'I' : 'i'; break;
            case Key::J:            out.m_character = out.m_uppercase ? 'J' : 'j'; break;
            case Key::K:            out.m_character = out.m_uppercase ? 'K' : 'k'; break;
            case Key::L:            out.m_character = out.m_uppercase ? 'L' : 'l'; break;
            case Key::M:            out.m_character = out.m_uppercase ? 'M' : 'm'; break;
            case Key::N:            out.m_character = out.m_uppercase ? 'N' : 'n'; break;
            case Key::O:            out.m_character = out.m_uppercase ? 'O' : 'o'; break;
            case Key::P:            out.m_character = out.m_uppercase ? 'P' : 'p'; break;
            case Key::Q:            out.m_character = out.m_uppercase ? 'Q' : 'q'; break;
            case Key::R:            out.m_character = out.m_uppercase ? 'R' : 'r'; break;
            case Key::S:            out.m_character = out.m_uppercase ? 'S' : 's'; break;
            case Key::T:            out.m_character = out.m_uppercase ? 'T' : 't'; break;
            case Key::U:            out.m_character = out.m_uppercase ? 'U' : 'u'; break;
            case Key::V:            out.m_character = out.m_uppercase ? 'V' : 'v'; break;
            case Key::W:            out.m_character = out.m_uppercase ? 'W' : 'w'; break;
            case Key::X:            out.m_character = out.m_uppercase ? 'X' : 'x'; break;
            case Key::Y:            out.m_character = out.m_uppercase ? 'Y' : 'y'; break;
            case Key::Z:            out.m_character = out.m_uppercase ? 'Z' : 'z'; break;

            case Key::Space:        out.m_character = ' '; break;

            case Key::Numpad0:      out.m_character = '0'; break;
            case Key::Numpad1:      out.m_character = '1'; break;
            case Key::Numpad2:      out.m_character = '2'; break;
            case Key::Numpad3:      out.m_character = '3'; break;
            case Key::Numpad4:      out.m_character = '4'; break;
            case Key::Numpad5:      out.m_character = '5'; break;
            case Key::Numpad6:      out.m_character = '6'; break;
            case Key::Numpad7:      out.m_character = '7'; break;
            case Key::Numpad8:      out.m_character = '8'; break;
            case Key::Numpad9:      out.m_character = '9'; break;
            case Key::NumpadDot:    out.m_character = '.'; break;
            case Key::NumpadSlash:  out.m_character = '/'; break;
            case Key::NumpadMinus:  out.m_character = '-'; break;
            case Key::NumpadPlus:   out.m_character = '+'; break;

            /* -------------------------------- */
            /*               OTHER              */
            /* -------------------------------- */

            case Key::Enter:
            case Key::Delete:
            case Key::NumpadEnter:
            case Key::Backspace:
            case Key::Tab:
            case Key::CursorUp:
            case Key::CursorDown:
            case Key::CursorLeft:
            case Key::CursorRight:
            case Key::Home:
            case Key::End:
            case Key::PageUp:
            case Key::PageDown:
                return TranslateResult::Command;

            case Key::Escape:
                return TranslateResult::Exit;

            default:
                return TranslateResult::Invalid;
        }
        return TranslateResult::Print;
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    Modifier    m_modifiers = Modifier::None;
    bool        m_isExtended = false;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    /**
     * @brief Translates a scancode to a key.
     * @param makecode The input scancode.
     * @param isExtended Whether the scancode is part of an escape sequence.
     * @param out The output key.
     */
    bool _translateKey(u8 makecode, const bool isExtended, Key& out) {
        bool numlock = isNumlock(m_modifiers);

        switch (makecode) {
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

            case 0x52: out = numlock ? Key::Numpad0 : Key::Insert; break;
            case 0x4F: out = numlock ? Key::Numpad1 : Key::End; break;
            case 0x50: out = isExtended ? Key::CursorDown : (numlock ? Key::Numpad2 : Key::CursorDown); break;
            case 0x51: out = numlock ? Key::Numpad3 : Key::PageDown ; break;
            case 0x4B: out = isExtended ? Key::CursorLeft : (numlock? Key::Numpad4 : Key::CursorLeft); break;
            case 0x4C: out = Key::Numpad5; break;
            case 0x4D: out = isExtended ? Key::CursorRight : (numlock ? Key::Numpad6 : Key::CursorRight); break;
            case 0x47: out = numlock ? Key::Numpad7 : Key::Home; break;
            case 0x48: out = isExtended ? Key::CursorUp : (numlock ? Key::Numpad8 : Key::CursorUp); break;
            case 0x49: out = numlock ? Key::Numpad9 : Key::PageUp; break;

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
            case 0x28: out = Key::Quote; break;
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

            default: return false;
        }
        return true;
    }

    inline
    void _setMod(const Modifier mod, const bool pressed) {
        if (pressed) { m_modifiers |= mod; }
        else         { m_modifiers &= ~mod; }
    }

    inline
    void _setLock(const Modifier mod, const bool pressed) {
        if (pressed) { m_modifiers ^= mod; }
    }

    inline
    bool _setModifiers(const KeyEvent& out, const bool isExtended) {
        const bool pressed = out.m_action == Action::Pressed;
        switch (out.m_key) {
            case Key::LShift:   _setMod(Modifier::LShift, pressed); break;
            case Key::RShift:   _setMod(Modifier::RShift, pressed); break;
            case Key::LCtrl:    isExtended ? _setMod(Modifier::RCtrl, pressed): _setMod(Modifier::LCtrl, pressed); break;
            case Key::LAlt:     isExtended ? _setMod(Modifier::RAlt, pressed): _setMod(Modifier::LAlt, pressed); break;
            case Key::Caps:     _setLock(Modifier::Caps, pressed); break;
            case Key::NumLock:  _setLock(Modifier::Num, pressed); break;

            default: return false;
        }
        return true;
    }

}; // class QwertyLayout

} // namespace ui