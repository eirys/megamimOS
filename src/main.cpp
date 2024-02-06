/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/06 16:30:06 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps2.h"
#include "vga.h"
#include "window_manager.h"
#include "qwerty.h"

#ifndef KERNEL_NAME
# define KERNEL_NAME "undefined kernel name :("
#endif

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
    _init();

    ui::WindowManager   winManager;
    ui::QwertyLayout    layout;

    winManager << KERNEL_NAME << ' ' << vga::Char::Heart;

    for (;;) {
        ui::KeyEvent event;
        ui::TranslateResult result = layout.translate(ps2::poll(), event);

        if (result == ui::TranslateResult::Invalid)
            // kernel panic
            continue;
        else if (result == ui::TranslateResult::Escape)
            break;
        else if (result == ui::TranslateResult::Ignore)
            continue;
        else if (result == ui::TranslateResult::SpecialAction)
            // handle special action
            continue;
        else
            winManager << event.character;
    }
}