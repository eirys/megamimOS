/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 21:12:28 by etran            ###   ########.fr       */
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
#include "layout_handler.h"

// State
#include "signal.h"
#include "time.h"

// CPU
#include "idt.h"
#include "gdt.h"

// Other
#include "panic.h"
#include "debug.h"

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
    pit::init(1000); // 100Hz
    vga::init();
    ps2::init();
    kfs::SignalManager::init();
#ifdef _DEBUG
    serial::init();
#endif
    ui::EventHandler::init();
    ui::WindowManager::init();
    ui::LayoutHandler::init();

    core::sti();
}

/* -------------------------------------------- */

extern "C"
void megamimOS_cpp(const MultibootInfo& info) {
    (void)info;
    _init();

    for (;;) {
        ui::Keyboard::handle(ui::LayoutHandler::getLayout());
        kfs::SignalManager::get().update();

        core::hlt();
    }
}
