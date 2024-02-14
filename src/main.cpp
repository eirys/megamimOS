/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 19:02:33 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps2.h"
#include "vga.h"
#include "window_manager.h"
#include "qwerty.h"
#include "idt.h"
#include "gdt.h"

/* -------------------------------------------- */

/**
 * @todo :P)
*/
struct MultibootInfo {
};

/* -------------------------------------------- */

static
void _init() {
    cpu::gdt::init();
    cpu::idt::init();
    pic::init();
    pic::setMask((pic::IRQMask)~((u8)pic::IRQMask::Keyboard | (u8)pic::IRQMask::Timer));
    vga::clearBuffer();
    ps2::readData();
#ifdef _DEBUG
    serial::init();
#endif

    core::sti();
}

static
void _exit(ui::WindowManager& winManager) {
    winManager.newLine();
    winManager << (i8*)"Good bye!";
    vga::disableCursor();
}

static
void _panic(ui::WindowManager& winManager) {
    core::cli();
    winManager.newLine();
    winManager << (i8*)"PANIC KERNEL PANIC! ABORTING!";
    // vga::disableCursor();
}

static
void _handleCommand(ui::WindowManager& winManager, const ui::KeyEvent& event) {
    switch (event.m_key) {
        case ui::Key::Enter:
        case ui::Key::NumpadEnter:  return winManager.prompt();
        case ui::Key::Backspace:    return event.m_control ? winManager.eraseLine() : winManager.eraseChar();
        case ui::Key::CursorLeft:   return event.m_control ? winManager.moveCursorToBeginningOfWord() : winManager.moveCursorLeft();
        case ui::Key::CursorRight:  return event.m_control ? winManager.moveCursorToEndOfWord() : winManager.moveCursorRight();
        case ui::Key::CursorUp:     return winManager.scrollUp();
        case ui::Key::CursorDown:   return winManager.scrollDown();
        case ui::Key::Delete:       return winManager.deleteChar();
        case ui::Key::Home:         return winManager.moveCursorToBeginning();
        case ui::Key::End:          return winManager.moveCursorToEnd();
        case ui::Key::PageUp:       return winManager.scrollPageUp();
        case ui::Key::PageDown:     return winManager.scrollPageDown();
        case ui::Key::Tab:
            return
            event.m_control ? (event.m_uppercase ? winManager.switchToPrevious() : winManager.switchToNext()) :
            void() /* winManager.completeCommand() */;

        default:
            break;
    }
}

/* -------------------------------------------- */

// using signalFn = void (*)(void);

// static signalFn signals[10] = {}

// bool hasScabcide;
// u8 scancode;

// static
// void handleInput() {
//         // Check if new signals have been registered.
//         // Calls signals

//         // Check
//         if (hasKeyEvent)
//         {
//             kasKeyEvent = false;

//         }

//         hlt();
// }

extern "C"
void megamimOS_cpp(const MultibootInfo& info) {
    _init();

    ui::WindowManager   winManager;
    ui::QwertyLayout    layout;

   vga::enableCursor(0xe, 0xe);

    for (;;) {
        ui::KeyEvent event;
        ui::TranslateResult result = layout.translate(ps2::poll(), event);

        switch (result) {
            case ui::TranslateResult::Print:    winManager << event.m_character; break;
            case ui::TranslateResult::Exit:     return _exit(winManager);
            case ui::TranslateResult::Command:  _handleCommand(winManager, event); break;
            case ui::TranslateResult::Invalid:
            case ui::TranslateResult::Ignore:   break;
        }
        winManager.draw();
    }
}