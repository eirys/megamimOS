/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   azerty.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:23:13 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 17:04:48 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "azerty.h"
#include "scancode.h"

namespace ui {

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

AzertyLayout& AzertyLayout::get() {
    static AzertyLayout instance;
    return instance;
}

/* -------------------------------------------- */

/**
 * @brief Given a scancode, translates it to a KeyEvent.
 * @param input The scancode to translate.
 * @param out The output KeyEvent.
 */
TranslateResult AzertyLayout::translate(const u8 input, KeyEvent& out) {
    if (input == 0xE0) {
        // The scancode is part of an escape sequence.
        m_isExtended = true;
        return TranslateResult::Continue;
    }

    const bool extended = m_isExtended;
    m_isExtended = false;
    out.m_key = translateScancode(input & 0x7F, extended, m_modifiers);
    if (out.m_key == Key::Unknown) {
        return TranslateResult::Invalid;
    }

    out.m_action = isPressed(input);
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
    out.m_altGr = isAltGr(m_modifiers);

    if (_setAccent(out.m_key, out.m_uppercase, out.m_altGr)) {
        return TranslateResult::Success;
    }

    switch (out.m_key) {
        /* -------------------------------- */
        /*       PRINTABLE CHARACTERS       */
        /* -------------------------------- */

        case Key::Grave:        out.m_character = vga::Char::Square; break;
        case Key::Key1:         out.m_character = out.m_uppercase ? (vga::Char)'1' : vga::Char::Ampersand; break;
        case Key::Key2:         out.m_character = out.m_altGr ? vga::Char::Tilde : (out.m_uppercase ? (vga::Char)'2' : vga::Char::EAcute); break;
        case Key::Key3:         out.m_character = out.m_altGr ? vga::Char::Hash : (out.m_uppercase ? (vga::Char)'3' : vga::Char::Quote); break;
        case Key::Key4:         out.m_character = out.m_altGr ? vga::Char::BraceL : (out.m_uppercase ? (vga::Char)'4' : vga::Char::Apostrophe); break;
        case Key::Key5:         out.m_character = out.m_altGr ? vga::Char::BracketL : (out.m_uppercase ? (vga::Char)'5' : vga::Char::ParenthesisL); break;
        case Key::Key6:         out.m_character = out.m_altGr ? vga::Char::BrokenBar : (out.m_uppercase ? (vga::Char)'6' : vga::Char::Minus); break;
        case Key::Key7:         out.m_character = out.m_altGr ? vga::Char::Grave : (out.m_uppercase ? (vga::Char)'7' : vga::Char::EGrave); break;
        case Key::Key8:         out.m_character = out.m_altGr ? vga::Char::Backslash : (out.m_uppercase ? (vga::Char)'8' : vga::Char::Underscore); break;
        case Key::Key9:         out.m_character = out.m_altGr ? vga::Char::Caret : (out.m_uppercase ? (vga::Char)'9' : vga::Char::CCedilla); break;
        case Key::Key0:         out.m_character = out.m_altGr ? vga::Char::At : (out.m_uppercase ? (vga::Char)'0' : vga::Char::AGrave); break;

        case Key::Minus:        out.m_character = out.m_altGr ? vga::Char::BracketR : (out.m_uppercase ? vga::Char::Degree : vga::Char::ParenthesisR); break;
        case Key::Equals:       out.m_character = out.m_altGr ? vga::Char::BraceR : (out.m_uppercase ? vga::Char::Plus : vga::Char::Equal); break;

        case Key::Q:            out.m_character = out.m_uppercase ? 'A' : 'a'; break;
        case Key::W:            out.m_character = out.m_uppercase ? 'Z' : 'z'; break;
        case Key::E:            out.m_character = out.m_uppercase ? 'E' : 'e'; break;
        case Key::R:            out.m_character = out.m_uppercase ? 'R' : 'r'; break;
        case Key::T:            out.m_character = out.m_uppercase ? 'T' : 't'; break;
        case Key::Y:            out.m_character = out.m_uppercase ? 'Y' : 'y'; break;
        case Key::U:            out.m_character = out.m_uppercase ? 'U' : 'u'; break;
        case Key::I:            out.m_character = out.m_uppercase ? 'I' : 'i'; break;
        case Key::O:            out.m_character = out.m_uppercase ? 'O' : 'o'; break;
        case Key::P:            out.m_character = out.m_uppercase ? 'P' : 'p'; break;
        case Key::LBracket:     out.m_character = vga::Char::Caret; break;
        case Key::RBracket:     out.m_character = out.m_uppercase ? vga::Char::Pound : vga::Char::Dollar; break;

        case Key::A:            out.m_character = out.m_uppercase ? 'Q' : 'q'; break;
        case Key::S:            out.m_character = out.m_uppercase ? 'S' : 's'; break;
        case Key::D:            out.m_character = out.m_uppercase ? 'D' : 'd'; break;
        case Key::F:            out.m_character = out.m_uppercase ? 'F' : 'f'; break;
        case Key::G:            out.m_character = out.m_uppercase ? 'G' : 'g'; break;
        case Key::H:            out.m_character = out.m_uppercase ? 'H' : 'h'; break;
        case Key::J:            out.m_character = out.m_uppercase ? 'J' : 'j'; break;
        case Key::K:            out.m_character = out.m_uppercase ? 'K' : 'k'; break;
        case Key::L:            out.m_character = out.m_uppercase ? 'L' : 'l'; break;
        case Key::Semicolon:    out.m_character = out.m_uppercase ? 'M' : 'm'; break;
        case Key::Apostrophe:   out.m_character = out.m_uppercase ? vga::Char::Percent : vga::Char::UGrave; break;
        case Key::Backslash:    out.m_character = out.m_uppercase ? vga::Char::Star : vga::Char::Mu; break;

        case Key::Z:            out.m_character = out.m_uppercase ? 'W' : 'w'; break;
        case Key::X:            out.m_character = out.m_uppercase ? 'X' : 'x'; break;
        case Key::C:            out.m_character = out.m_uppercase ? 'C' : 'c'; break;
        case Key::V:            out.m_character = out.m_uppercase ? 'V' : 'v'; break;
        case Key::B:            out.m_character = out.m_uppercase ? 'B' : 'b'; break;
        case Key::N:            out.m_character = out.m_uppercase ? 'N' : 'n'; break;
        case Key::M:            out.m_character = out.m_uppercase ? vga::Char::Question : vga::Char::Comma; break;
        case Key::Comma:        out.m_character = out.m_uppercase ? vga::Char::Dot : vga::Char::SemiColon; break;
        case Key::Dot:          out.m_character = out.m_uppercase ? vga::Char::Slash : vga::Char::Colon; break;
        case Key::Slash:        out.m_character = out.m_uppercase ? vga::Char::Section : vga::Char::Exclamation; break;

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

    _updateAccent(out);

    return TranslateResult::Success;
}

/* -------------------------------------------- */
/*                    PRIVATE                   */
/* -------------------------------------------- */

bool AzertyLayout::_setAccent(
    const Key key,
    const bool isUppercase,
    const bool isAltGr
) {
    if (m_accent != Accent::None) {
        return false;
    }

    switch (key) {
        case Key::Key2:     if (isAltGr) m_accent = Accent::Tilde; break;
        case Key::Key7:     if (isAltGr) m_accent = Accent::Grave; break;
        case Key::LBracket: m_accent = isUppercase ? Accent::Umlaut : Accent::Circumflex; break;
        default:            return false;
    }
    return true;
}

static
void _putGrave(KeyEvent& out) {
    switch (out.m_key) {
        case Key::Q:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::AGrave; break;
        case Key::E:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::EGrave; break;
        case Key::I:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::IGrave; break;
        case Key::O:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::OGrave; break;
        case Key::U:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::UGrave; break;
        default:        break;
    }
}

static
void _putUmlaut(KeyEvent& out) {
    switch (out.m_key) {
        case Key::Q:    out.m_character = out.m_uppercase ? vga::Char::AMUmlaut : vga::Char::AUmlaut; break;
        case Key::E:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::EUmlaut; break;
        case Key::I:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::IUmlaut; break;
        case Key::O:    out.m_character = out.m_uppercase ? vga::Char::OMUmlaut : vga::Char::OUmlaut; break;
        case Key::U:    out.m_character = out.m_uppercase ? vga::Char::UMUmlaut : vga::Char::UUmlaut; break;
        case Key::Y:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::YUmlaut; break;
        default:        return;
    }
}

static
void _putCircumflex(KeyEvent& out) {
    switch (out.m_key) {
        case Key::Q:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::ACircumflex; break;
        case Key::E:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::ECircumflex; break;
        case Key::I:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::ICircumflex; break;
        case Key::O:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::OCircumflex; break;
        case Key::U:    out.m_character = out.m_uppercase ? out.m_character : vga::Char::UCircumflex; break;
        default:        break;
    }
}

static
void _putTilde(KeyEvent& out) {
    switch (out.m_key) {
        case Key::N:    out.m_character = out.m_uppercase ? vga::Char::NMTilde : vga::Char::NTilde; break;
        default:        break;
    }
}

void AzertyLayout::_updateAccent(KeyEvent& out) {
    switch (m_accent) {
        case Accent::Grave:         _putGrave(out); break;
        case Accent::Umlaut:        _putUmlaut(out); break;
        case Accent::Circumflex:    _putCircumflex(out); break;
        case Accent::Tilde:         _putTilde(out); break;
        default:                    break;
    }
    m_accent = Accent::None;
}

} // namespace ui