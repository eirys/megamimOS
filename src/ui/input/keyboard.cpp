/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 01:57:59 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 03:13:41 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"
#include "window_manager.h"
#include "command_handler.h"
#include "lib.h"
#include "ilayout.h"
#include "key_event.h"
#include "event_handler.h"

#include "debug.h"

namespace ui {

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

void Keyboard::handle(ILayout& layout) {
    u8 scancodes[EventHandler::MAX_SCANCODES];
    u8 scancodeCount = 0;

    // Prevent a race condition with the keyboard interrupt.
    core::cli();
    EventHandler::copyTo(scancodes, scancodeCount);
    core::sti();

    // Translate the received scan-codes.
    for(u8 i = 0; i < scancodeCount; ++i) {
        KeyEvent        event;
        TranslateResult result = layout.translate(scancodes[i], event);

        switch (result) {
            case TranslateResult::Success:  _handleInput(event); break;
            case TranslateResult::Continue:
            case TranslateResult::Invalid:  break;
        }
    }
    WindowManager::draw();
}

/* -------------------------------------------- */
/*                    PRIVATE                   */
/* -------------------------------------------- */

void Keyboard::_handleCommand() {
    const Command cmd = WindowManager::getCommand();

    if (cmd != Command::Empty) {
        WindowManager::newLine();
        CommandHandler::execute(cmd);
    }
    WindowManager::prompt();
}

void Keyboard::_handleInput(const KeyEvent& event) {
    if (event.m_action == Action::Released)
        return;

    switch (event.m_key) {
        case Key::Enter:
        case Key::NumpadEnter:  return _handleCommand();
        case Key::Backspace:    return event.m_control ? WindowManager::eraseLine() : WindowManager::eraseChar();
        case Key::CursorLeft:   return event.m_control ? WindowManager::moveCursorToBeginningOfWord() : WindowManager::moveCursorLeft();
        case Key::CursorRight:  return event.m_control ? WindowManager::moveCursorToEndOfWord() : WindowManager::moveCursorRight();
        case Key::CursorUp:     return WindowManager::scrollUp();
        case Key::CursorDown:   return WindowManager::scrollDown();
        case Key::Delete:       return WindowManager::deleteChar();
        case Key::Home:         return WindowManager::moveCursorToBeginning();
        case Key::End:          return WindowManager::moveCursorToEnd();
        case Key::PageUp:       return WindowManager::scrollPageUp();
        case Key::PageDown:     return WindowManager::scrollPageDown();
        case Key::Tab:          if (event.m_control) { event.m_uppercase ? WindowManager::switchToPrevious() : WindowManager::switchToNext(); }
                                break;

        default:                if (event.m_character != vga::Char::Empty) WindowManager::get() << event.m_character;
                                break;
    }
}

} // namespace ui