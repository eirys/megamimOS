/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/12 01:36:06 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps2.h"
#include "vga.h"
#include "window_manager.h"
#include "qwerty.h"
#include "serial.h"

#define LOG_NUM serial::write_nbr
#define LOG serial::write_str

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
void _handleCommand(ui::WindowManager& winManager, const ui::KeyEvent& event) {
    switch (event.m_key) {
        case ui::Key::Backspace:    return winManager.eraseChar();
        case ui::Key::NumpadEnter:
        case ui::Key::Enter:        return winManager.prompt();
        case ui::Key::Tab:          return event.m_uppercase ? winManager.switchToPrevious() : winManager.switchToNext();
        case ui::Key::CursorUp:     return winManager.scrollUp();
        case ui::Key::CursorDown:   return winManager.scrollDown();
        case ui::Key::CursorLeft:   return winManager.moveCursorLeft();
        case ui::Key::CursorRight:  return winManager.moveCursorRight();
        case ui::Key::Delete:       return winManager.deleteChar();
        case ui::Key::Home:         return winManager.moveCursorToBeginning();
        case ui::Key::End:          return winManager.moveCursorToEnd();
        default:
            break;
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
            case ui::TranslateResult::Print:    winManager << event.m_character; break;
            case ui::TranslateResult::Invalid:
            LOG_NUM((u32)event.m_key);
            /* return */ /* _panic(winManager); */ break;
            case ui::TranslateResult::Exit:     return _exit(winManager);
            case ui::TranslateResult::Ignore:   break;
            case ui::TranslateResult::Command:  _handleCommand(winManager, event); break;
        }

        winManager.draw();
    }
}