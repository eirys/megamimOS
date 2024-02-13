/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/13 20:39:21 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps2.h"
#include "vga.h"
#include "window_manager.h"
#include "qwerty.h"
#include "gdt.h"
#include "debug.h"

/* -------------------------------------------- */

/**
 * @todo :P)
*/
struct MultibootInfo {
};

/* -------------------------------------------- */

static inline
void _init() {
#ifdef _DEBUG
    serial::init();
#endif
    cpu::gdt::init();
    vga::init();
    ps2::init();
    ui::WindowManager::init();
}

static inline
void _exit() {
    ui::WindowManager::newLine();
    *ui::WindowManager::get() << (i8*)"Good bye!";
    vga::disableCursor();
}

static
void _handleCommand(const ui::KeyEvent& event) {
    switch (event.m_key) {
        case ui::Key::Enter:
        case ui::Key::NumpadEnter:  return ui::WindowManager::handleInput();
        case ui::Key::Backspace:    return event.m_control ? ui::WindowManager::eraseLine() : ui::WindowManager::eraseChar();
        case ui::Key::CursorLeft:   return event.m_control ? ui::WindowManager::moveCursorToBeginningOfWord() : ui::WindowManager::moveCursorLeft();
        case ui::Key::CursorRight:  return event.m_control ? ui::WindowManager::moveCursorToEndOfWord() : ui::WindowManager::moveCursorRight();
        case ui::Key::CursorUp:     return ui::WindowManager::scrollUp();
        case ui::Key::CursorDown:   return ui::WindowManager::scrollDown();
        case ui::Key::Delete:       return ui::WindowManager::deleteChar();
        case ui::Key::Home:         return ui::WindowManager::moveCursorToBeginning();
        case ui::Key::End:          return ui::WindowManager::moveCursorToEnd();
        case ui::Key::PageUp:       return ui::WindowManager::scrollPageUp();
        case ui::Key::PageDown:     return ui::WindowManager::scrollPageDown();
        case ui::Key::Tab:
            return
            event.m_control ? (event.m_uppercase ? ui::WindowManager::switchToPrevious() : ui::WindowManager::switchToNext()) :
            void() /* winManager.completeCommand() */;

        default:
            break;
    }
}

/* -------------------------------------------- */

extern "C"
void megamimOS_cpp(const MultibootInfo& info) {
    (void)info;
    _init();

    ui::QwertyLayout    layout;

    for (;;) {
        ui::KeyEvent event;
        ui::TranslateResult result = layout.translate(ps2::poll(), event);

        switch (result) {
            case ui::TranslateResult::Print:    *ui::WindowManager::get() << event.m_character; break;
            case ui::TranslateResult::Exit:     return _exit();
            case ui::TranslateResult::Command:  _handleCommand(event); break;
            case ui::TranslateResult::Invalid:
            case ui::TranslateResult::Ignore:   break;
        }

        ui::WindowManager::draw();
    }
}