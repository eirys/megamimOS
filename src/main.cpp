/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/06 00:10:42 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps2.h"
#include "vga.h"
#include "window_manager.h"
#include "qwerty.h"

// #define KERNEL_NAME
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
}

/* -------------------------------------------- */

extern "C"
void megamimOS_cpp(const MultibootInfo& info) {
    WindowManager       winManager;
    ui::QwertyLayout    layout;

    _init();

    winManager << STR(KERNEL_NAME);

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