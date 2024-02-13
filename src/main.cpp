/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/13 11:06:40 by etran            ###   ########.fr       */
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
        case ui::Key::Enter:
        case ui::Key::NumpadEnter:  return winManager.handleInput();
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

static inline
void _panic(ui::WindowManager& winManager) {
    core::panic();
    winManager.newLine();
    winManager << (i8*)"PANIC KERNEL PANIC! ABORTING!";
    // vga::disableCursor();
}

struct GDTR {
    u16 limit;
    u64 base;
} __attribute__((packed));

extern "C"
void load_gdt(const GDTR* reg);

static
void _loadGDT() {
    u64 tablo[] = {
        // Null Segment. Don't ask.
        0x0,

        // Kernel Code Segment
        0x00cf9a000000ffff,
        // Kernel Data Segment
        0x00cf92000000ffff,
        // Kernel Stack Segment
        0x00cf92000000ffff,

        // User Code Segment
        0x00cffa000000ffff,
        // User Data Segment
        0x00cff2000000ffff,
        // User Stack Segment
        0x00cff2000000ffff
    };

    GDTR gdtr = {
        .limit = sizeof(tablo) - 1,
        .base = 0x00000800
    };
    lib::memcpy((void*)0x00000800, tablo, sizeof(tablo));

    load_gdt(&gdtr);
}

/* -------------------------------------------- */

extern "C"
void megamimOS_cpp(const MultibootInfo& info) {
    _loadGDT();
    _init();

    ui::WindowManager   winManager;
    ui::QwertyLayout    layout;

   vga::enableCursor(0xe, 0xe);

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