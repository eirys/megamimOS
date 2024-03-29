/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:41:49 by etran             #+#    #+#             */
/*   Updated: 2024/02/22 16:49:35 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Boot
#include "multiboot.h"

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

// Memory
#include "paging.h"
#include "balloc.h"
#include "kalloc.h"

// Other
#include "panic.h"
#include "debug.h"

/* -------------------------------------------- */

template<typename F>
void forEachFreePage(const multiboot::Info& info, F callback) {
    multiboot::MemoryMap memMap;
    multiboot::MmapIterator iter = info.mmapIterator();
    while (iter.next(memMap)) {
        if (memMap.type != (u32)multiboot::MemoryType::Available)
            continue;
        for (u32 i = 0; i < memMap.length_low; i += 0x1000)
        {
            u32 addr = memMap.base_addr_low + i;
            if (mem::ballocIsConsumed(addr))
                continue;
            callback(addr);
        }
    }
}

static
void _init(const multiboot::Info& info) {
#ifdef _DEBUG
    serial::init();
#endif
    multiboot::MemoryMap memMap;
    if (!info.getLargestMemoryRegion(memMap))
        return beginKernelPanic("No memory available");
    mem::ballocInit(memMap.base_addr_low + memMap.length_low, memMap.base_addr_low);

    mem::init(info.upperBound());

    u32 maxFreePages = 0;
    forEachFreePage(info, [&maxFreePages](u32 addr) { (void)addr; maxFreePages++; });
    mem::kinit(maxFreePages);
    forEachFreePage(info, [](u32 addr) { mem::kfree(addr); });

    cpu::gdt::init();
    cpu::idt::init();
    pic::init();
    pit::init(1000); // 100Hz
    vga::init();
    ps2::init();
    kfs::SignalManager::init();
    ui::EventHandler::init();
    ui::WindowManager::init();
    ui::LayoutHandler::init();

    core::sti();
}

/* -------------------------------------------- */

extern "C"
void megamimOS_cpp(const multiboot::Info& info) {
    _init(info);

    for (;;) {
        ui::Keyboard::handle(ui::LayoutHandler::getLayout());
        kfs::SignalManager::update();

        core::hlt();
    }
}
