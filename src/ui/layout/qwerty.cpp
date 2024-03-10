/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwerty.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:01:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 17:02:49 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qwerty.h"
#include "scancode.h"

namespace ui {

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

QwertyLayout& QwertyLayout::get() {
    static QwertyLayout instance;
    return instance;
}

/* -------------------------------------------- */

/**
 * @brief Given a scancode, translates it to a KeyEvent.
 * @param input The scancode to translate.
 * @param out The output KeyEvent.
 */
TranslateResult QwertyLayout::translate(const u8 input, KeyEvent& out) {
    if (input == 0xE0) {
        // The scancode is part of an escape sequence.
        m_isExtended = true;
        return TranslateResult::Continue;
    }

    out.m_action = isPressed(input);

    const bool extended = m_isExtended;
    m_isExtended = false;

    out.m_key = translateScancode(input & 0x7F, extended, m_modifiers);
    if (out.m_key == Key::Unknown) {
        return TranslateResult::Invalid;
    }

    const bool pressed = out.m_action == Action::Pressed;
    if (setModifiers(m_modifiers, out.m_key, pressed)) {
        return TranslateResult::Success;
    }

    if (out.m_action == Action::Released) {
        return TranslateResult::Success;
    }

    out.m_uppercase = isUppercase(m_modifiers);
    out.m_control = isControl(m_modifiers);
    out.m_alt = isAlt(m_modifiers);

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
        case Key::Apostrophe:   out.m_character = out.m_uppercase ? '"' : '\''; break;
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
        case Key::Escape:
            return TranslateResult::Success;

        default:
            return TranslateResult::Invalid;
    }
    return TranslateResult::Success;
}

} // namespace ui