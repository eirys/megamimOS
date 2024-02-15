/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 19:14:01 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Drivers
#include "ps2.h"
#include "vga.h"
#include "pic.h"
#include "pit.h"

// UI
#include "window_manager.h"
#include "qwerty.h"

// State
#include "signal.h"

// CPU
#include "idt.h"
#include "gdt.h"

// Other
#include "panic.h"

/* -------------------------------------------- */

/**
 * @todo :P)
*/
struct MultibootInfo {
};

/* -------------------------------------------- */

static
void _basicSignalHandler() {
    ui::WindowManager::currentTerminal() << "Signal received!";
}

static
void _init() {
    cpu::gdt::init();
    cpu::idt::init();
    pic::init();
    pit::init(100); // 100Hz
    vga::init();
    ps2::init();
    kfs::SignalManager::get().registerHandler(kfs::Signal::User1, _basicSignalHandler);
#ifdef _DEBUG
    serial::init();
#endif

    core::sti();

    ui::WindowManager::init();
}

static
void _handleCommand() {
    const ui::Command cmd = ui::WindowManager::getCommand();

    if (cmd != ui::Command::Empty) {
        ui::WindowManager::newLine();
        ui::CommandHandler::execute(cmd);
    }
    ui::WindowManager::prompt();
}

static
void _handleInput(const ui::KeyEvent& event) {
    if (event.m_action == ui::Action::Released)
        return;

    switch (event.m_key) {
        case ui::Key::Enter:
        case ui::Key::NumpadEnter:  return _handleCommand();
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

        case ui::Key::Escape:       break;
        default:                    *ui::WindowManager::get() << event.m_character; break;
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
    (void)info;
    _init();

    ui::QwertyLayout    layout;

    for (;;) {
        kfs::SignalManager::get().update();

        ui::KeyEvent event{};
        ui::TranslateResult result = layout.translate(ps2::poll(), event);

        switch (result) {
            case ui::TranslateResult::Success:  _handleInput(event); break;
            case ui::TranslateResult::Continue:
            case ui::TranslateResult::Invalid:  break;
        }

        ui::WindowManager::draw();
    }
}
