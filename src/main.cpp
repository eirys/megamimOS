/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/07 21:17:21 by etran            ###   ########.fr       */
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
void _handleSpecialEvent(ui::WindowManager& winManager, const ui::Key key) {
    switch (key) {
        case ui::Key::Backspace:    return winManager.eraseChar();
        case ui::Key::Enter:        return winManager.newLine();
        case ui::Key::Tab:          return winManager.switchToNext();
        default:                    break;
    }
}

static inline
void _exit(ui::WindowManager& winManager) {
    winManager.newLine();
    winManager << (i8*)"Good bye!";
    vga::disableCursor();
}

/* -------------------------------------------- */

extern "C"
void megamimOS_cpp(const MultibootInfo& info) {
    _init();

    ui::WindowManager   winManager;
    ui::QwertyLayout    layout;

   vga::enableCursor(0xb, 0xf);

    for (;;) {
        ui::KeyEvent event;
        ui::TranslateResult result = layout.translate(ps2::poll(), event);

        switch (result) {
            case ui::TranslateResult::Invalid:
                break; // kernel panic

            case ui::TranslateResult::SpecialAction:
                _handleSpecialEvent(winManager, event.key);
                break;

            case ui::TranslateResult::Print:
                winManager << event.character;
                break;

            case ui::TranslateResult::Exit:
                return _exit(winManager);

            case ui::TranslateResult::Ignore:
            default:
                break;
        }
    }
}