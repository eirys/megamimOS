/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scancode.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 20:14:41 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 21:04:53 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ui {

enum class Key {
    Unknown,
    Escape,
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
    Minus,
    Equals,
    Backspace,
};

struct KeyEvent {
    Key         key;
    vga::Char   character;
    bool        pressed;
};

class Layout {
public:

    virtual ~Layout() = default;

    virtual
    bool translate(const uint8_t scancode, KeyEvent& out) = 0;

private:

};

enum Modifier: uint8_t {
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

static inline bool isShifted(const Modifier mod) {
    return (mod & Modifier::LShift) || (mod & Modifier::RShift);
}

static inline bool isUppercase(const Modifier mod) {
    return (mod & Modifier::Caps) ^ isShifted(mod);
}

class QwertyLayout: public Layout {
public:

    virtual
    ~QwertyLayout() = default;

    virtual
    bool translate(uint8_t scancode, KeyEvent& out) override {
        out.pressed = (scancode & 0x80) == 0;
        if (!out.pressed)
            scancode &= 0x7F;

        switch (scancode) {
            case 0x01:
                out.key = Key::Escape;
                out.character = vga::Char::Empty;
                return true;
            case 0x02:
                out.key = Key::Key1;
                out.character = isUppercase(modifiers) ? '!' : '1';
                return true;
            case 0x03:
                out.key = Key::Key2;
                out.character = isUppercase(modifiers) ? '@' : '2';
                return true;
            case 0x04:
                out.key = Key::Key3;
                out.character = isUppercase(modifiers) ? '#' : '3';
                return true;
            case 0x05:
                out.key = Key::Key4;
                out.character = isUppercase(modifiers) ? '$' : '4';
                return true;
            case 0x06:
                out.key = Key::Key5;
                out.character = isUppercase(modifiers) ? '%' : '5';
                return true;
            case 0x07:
                out.key = Key::Key6;
                out.character = isUppercase(modifiers) ? '^' : '6';
                return true;
            case 0x08:
                out.key = Key::Key7;
                out.character = isUppercase(modifiers) ? '&' : '7';
                return true;
            case 0x09:
                out.key = Key::Key8;
                out.character = isUppercase(modifiers) ? '*' : '8';
                return true;
            case 0x0A:
                out.key = Key::Key9;
                out.character = isUppercase(modifiers) ? '(' : '9';
                return true;
            case 0x0B:
                out.key = Key::Key0;
                out.character = isUppercase(modifiers) ? ')' : '0';
                return true;
            case 0x0C:
                out.key = Key::Minus;
                out.character = isUppercase(modifiers) ? '_' : '-';
                return true;
            case 0x0D:
                out.key = Key::Equals;
                out.character = isUppercase(modifiers) ? '+' : '=';
                return true;
            case 0x0E:
                out.key = Key::Backspace;
                out.character = vga::Char::Empty;
                return true;

            default:
                return false;
        }
    }

private:
    Modifier modifiers = Modifier::None;
};

} // namespace ui