/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 21:12:21 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps2.h"
#include "vga.h"
#include "history.h"
#include "window_manager.h"
#include "scancode.h"

#define KERNEL_NAME         "megamimOS"
#define KERNEL_NAME_LEN     9

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
    // vga::g_cursor.update();
}

/* -------------------------------------------- */

extern "C"
void megamimOS_cpp(const MultibootInfo& info) {
    WindowManager winManager;

    _init();

    winManager << KERNEL_NAME;
    // vga::putString(KERNEL_NAME, 0, 0);
    // vga::putChar(vga::Char::Heart, KERNEL_NAME_LEN + 1, 0, vga::Color::Cherry);

    ui::QwertyLayout layout;

    for (;;) {
        ui::KeyEvent event;
        if (!layout.translate(ps2::poll(), event))
            continue;

        if (!event.pressed)
            continue;

        if (event.character != vga::Char::Empty)
            winManager << event.character;
    }
}