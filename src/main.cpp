/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 03:05:13 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Drivers
#include "ps2.h"
#include "vga.h"
#include "pic.h"
#include "pit.h"

// UI
#include "keyboard.h"
#include "event_handler.h"
#include "window_manager.h"
#include "qwerty.h"

// CPU
#include "idt.h"
#include "gdt.h"

#include "debug.h"
#include "panic.h"

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
    pit::init(100); // 100Hz
    vga::init();
    ps2::init();
#ifdef _DEBUG
    serial::init();
#endif
    ui::EventHandler::init();
    ui::WindowManager::init();

    core::sti();
}

/* -------------------------------------------- */

extern "C"
void megamimOS_cpp(const MultibootInfo& info) {
    (void)info;
    _init();

    ui::QwertyLayout layout;

    for (;;) {
        ui::Keyboard::handle(layout);
        core::hlt();
    }
}
