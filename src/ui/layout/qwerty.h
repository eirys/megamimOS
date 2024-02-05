/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qwerty.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:44:59 by etran             #+#    #+#             */
/*   Updated: 2024/02/06 00:53:52 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "scancode.h"
#include "layout.h"
#include "vga.h"

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

    bool translate(const u8 scancode, KeyEvent& out) override {
        out.pressed = isPressed(scancode);
        // if (!out.pressed)
        //     scancode &= 0x7F;

        bool isUppercase = ui::isUppercase(m_modifiers);

        switch (scancode & 0x7F) {
            case 0x01:
                out.key = Key::Escape;
                out.character = vga::Char::Empty;
                break;
            case 0x02:
                out.key = Key::Key1;
                out.character = isUppercase ? '!' : '1';
                break;
            case 0x03:
                out.key = Key::Key2;
                out.character = isUppercase ? '@' : '2';
                break;
            case 0x04:
                out.key = Key::Key3;
                out.character = isUppercase ? '#' : '3';
                break;
            case 0x05:
                out.key = Key::Key4;
                out.character = isUppercase ? '$' : '4';
                break;
            case 0x06:
                out.key = Key::Key5;
                out.character = isUppercase ? '%' : '5';
                break;
            case 0x07:
                out.key = Key::Key6;
                out.character = isUppercase ? '^' : '6';
                break;
            case 0x08:
                out.key = Key::Key7;
                out.character = isUppercase ? '&' : '7';
                break;
            case 0x09:
                out.key = Key::Key8;
                out.character = isUppercase ? '*' : '8';
                break;
            case 0x0A:
                out.key = Key::Key9;
                out.character = isUppercase ? '(' : '9';
                break;
            case 0x0B:
                out.key = Key::Key0;
                out.character = isUppercase ? ')' : '0';
                break;
            case 0x0C:
                out.key = Key::Minus;
                out.character = isUppercase ? '_' : '-';
                break;
            case 0x0D:
                out.key = Key::Equals;
                out.character = isUppercase ? '+' : '=';
                break;
            case 0x0E:
                out.key = Key::Backspace;
                out.character = vga::Char::Empty;
                break;

            default:
                return false;
        }

        return true;
    }

private:
    /* ---------------------------------------- */
    /*                   DATA                   */
    /* ---------------------------------------- */

    Modifier    m_modifiers = Modifier::None;
};

} // namespace ui