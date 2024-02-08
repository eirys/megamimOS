/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/08 13:43:04 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps2.h"
#include "vga.h"
#include "window_manager.h"
#include "qwerty.h"
#include "serial.h"

/* -------------------------------------------- */

/**
 * @todo :P)
*/
struct MultibootInfo {
};

/* -------------------------------------------- */

static inline
void _init() {
    vga::clearBuffer();
    ps2::readData();
    serial::init();
}

static inline
void _exit(ui::WindowManager& winManager) {
    winManager.newLine();
    winManager << (i8*)"Good bye!";
    vga::disableCursor();
}

static
void _print(ui::WindowManager& winManager, const ui::KeyEvent& event) {
    switch (event.m_key) {
        case ui::Key::Backspace:    return winManager.eraseChar();
        case ui::Key::Enter:        return winManager.newLine();
        case ui::Key::Tab:          return event.m_uppercase ? winManager.switchToPrevious() : winManager.switchToNext();
        // case ui::Key::CursorUp:
        // case ui::Key::CursorDown:
        // case ui::Key::CursorLeft:
        // case ui::Key::CursorRight:
        default:                    winManager << event.m_character; break;
    }
}

static inline
void _panic(ui::WindowManager& winManager) {
    core::panic();
    winManager.newLine();
    winManager << (i8*)"PANIC KERNEL PANIC! ABORTING!";
    // vga::disableCursor();
}
/* -------------------------------------------- */

extern "C"
void megamimOS_cpp(const MultibootInfo& info) {
    _init();

    ui::WindowManager   winManager;
    ui::QwertyLayout    layout;

   vga::enableCursor(0xe, 0xf);

    for (;;) {
        ui::KeyEvent event;
        ui::TranslateResult result = layout.translate(ps2::poll(), event);

        switch (result) {
            case ui::TranslateResult::Print:    _print(winManager, event); break;
            case ui::TranslateResult::Invalid:  /* return */ _panic(winManager); break;
            case ui::TranslateResult::Exit:     return _exit(winManager);
            case ui::TranslateResult::Ignore:   break;
        }
    }
}