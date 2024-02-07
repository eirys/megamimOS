/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwerty.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:44:59 by etran             #+#    #+#             */
/*   Updated: 2024/02/07 19:46:54 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "scancode.h"
#include "layout.h"
#include "vga.h"
#include "debug.h"


namespace ui {

/**
 * @brief Scancode interpreter for the US-QWERTY layout.
 */
class QwertyLayout final: public Layout {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    ~QwertyLayout() = default;

    /* ---------------------------------------- */

    TranslateResult translate(const u8 input, KeyEvent& out) override {
        out.character = vga::Char::Empty;
        out.action = isPressed(input);

        if (input == 0xE0) {
            // The scancode is part of an escape sequence.
            m_isExtended = true;
            return TranslateResult::Ignore;
        }

        const bool isExtended = m_isExtended;
        m_isExtended = false;

        if (!_translateKey(input & 0x7F, isExtended, out.key)) {
            return TranslateResult::Invalid;
        }

        _setModifiers(out, isExtended);

        if (out.action == Action::Released) {
            return TranslateResult::Ignore;
        }

        bool uppercase = isUppercase(m_modifiers);

        switch (out.key) {
            case Key::Key1:         out.character = uppercase ? '!' : '1'; break;
            case Key::Key2:         out.character = uppercase ? '@' : '2'; break;
            case Key::Key3:         out.character = uppercase ? '#' : '3'; break;
            case Key::Key4:         out.character = uppercase ? '$' : '4'; break;
            case Key::Key5:         out.character = uppercase ? '%' : '5'; break;
            case Key::Key6:         out.character = uppercase ? '^' : '6'; break;
            case Key::Key7:         out.character = uppercase ? '&' : '7'; break;
            case Key::Key8:         out.character = uppercase ? '*' : '8'; break;
            case Key::Key9:         out.character = uppercase ? '(' : '9'; break;
            case Key::Key0:         out.character = uppercase ? ')' : '0'; break;

            case Key::Minus:        out.character = uppercase ? '_' : '-'; break;
            case Key::Equals:       out.character = uppercase ? '+' : '='; break;

            case Key::LBracket:     out.character = uppercase ? '{' : '['; break;
            case Key::RBracket:     out.character = uppercase ? '}' : ']'; break;
            case Key::Semicolon:    out.character = uppercase ? ':' : ';'; break;
            case Key::Quote:        out.character = uppercase ? '"' : '\''; break;
            case Key::Comma:        out.character = uppercase ? '<' : ','; break;
            case Key::Dot:          out.character = uppercase ? '>' : '.'; break;
            case Key::Slash:        out.character = uppercase ? '?' : '/'; break;
            case Key::Backslash:    out.character = uppercase ? '|' : '\\'; break;
            case Key::Grave:        out.character = uppercase ? '~' : '`'; break;

            case Key::A:            out.character = uppercase ? 'A' : 'a'; break;
            case Key::B:            out.character = uppercase ? 'B' : 'b'; break;
            case Key::C:            out.character = uppercase ? 'C' : 'c'; break;
            case Key::D:            out.character = uppercase ? 'D' : 'd'; break;
            case Key::E:            out.character = uppercase ? 'E' : 'e'; break;
            case Key::F:            out.character = uppercase ? 'F' : 'f'; break;
            case Key::G:            out.character = uppercase ? 'G' : 'g'; break;
            case Key::H:            out.character = uppercase ? 'H' : 'h'; break;
            case Key::I:            out.character = uppercase ? 'I' : 'i'; break;
            case Key::J:            out.character = uppercase ? 'J' : 'j'; break;
            case Key::K:            out.character = uppercase ? 'K' : 'k'; break;
            case Key::L:            out.character = uppercase ? 'L' : 'l'; break;
            case Key::M:            out.character = uppercase ? 'M' : 'm'; break;
            case Key::N:            out.character = uppercase ? 'N' : 'n'; break;
            case Key::O:            out.character = uppercase ? 'O' : 'o'; break;
            case Key::P:            out.character = uppercase ? 'P' : 'p'; break;
            case Key::Q:            out.character = uppercase ? 'Q' : 'q'; break;
            case Key::R:            out.character = uppercase ? 'R' : 'r'; break;
            case Key::S:            out.character = uppercase ? 'S' : 's'; break;
            case Key::T:            out.character = uppercase ? 'T' : 't'; break;
            case Key::U:            out.character = uppercase ? 'U' : 'u'; break;
            case Key::V:            out.character = uppercase ? 'V' : 'v'; break;
            case Key::W:            out.character = uppercase ? 'W' : 'w'; break;
            case Key::X:            out.character = uppercase ? 'X' : 'x'; break;
            case Key::Y:            out.character = uppercase ? 'Y' : 'y'; break;
            case Key::Z:            out.character = uppercase ? 'Z' : 'z'; break;

            case Key::Space:        out.character = ' '; break;

            case Key::Escape:
                return TranslateResult::Exit;
            case Key::Enter:
            case Key::Backspace:
            case Key::Tab:
                return TranslateResult::SpecialAction;

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
        switch (makecode) {
            case 0x01: out = Key::Escape; break;

            case 0x29: out = Key::Grave; break;
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
            case 0x27: out = Key::Semicolon; break;
            case 0x28: out = Key::Quote; break;

            case 0x2C: out = Key::Z; break;
            case 0x2D: out = Key::X; break;
            case 0x2E: out = Key::C; break;
            case 0x2F: out = Key::V; break;
            case 0x30: out = Key::B; break;
            case 0x31: out = Key::N; break;
            case 0x32: out = Key::M; break;
            case 0x33: out = Key::Comma; break;
            case 0x34: out = Key::Dot; break;
            case 0x35: out = Key::Slash; break;

            case 0x39: out = Key::Space; break;

            case 0x1C: out = Key::Enter; break;
            case 0x0E: out = Key::Backspace; break;
            case 0x0F: out = Key::Tab; break;

            case 0x1A: out = Key::LBracket; break;
            case 0x1B: out = Key::RBracket; break;

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
        const bool pressed = out.action == Action::Pressed;
        switch (out.key) {
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