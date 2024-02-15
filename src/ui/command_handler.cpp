/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 01:24:31 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 19:39:50 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_handler.h"
#include "debug.h"
#include "vga.h"
#include "core.h"
#include "lib.h"
#include "panic.h"
#include "window_manager.h"

namespace ui {

/* -------------------------------------------- */
/*                    PUBLIC                    */
/* -------------------------------------------- */

Command  CommandHandler::parse(const vga::Char* buf, u32 len) {
    while (!buf->isAlphanum() && len > 0) {
        --len;
        ++buf;
    }

    if (_getWordLen(buf, len) == 0)
        return Command::Empty;

    for (u8 cmdIndex = 0; cmdIndex < COMMAND_COUNT; cmdIndex++) {
        if (lib::memcmp(buf, COMMANDS_NAME[cmdIndex], lib::strlen(COMMANDS_NAME[cmdIndex])) == 0)
            return (Command)cmdIndex;
    }

    return Command::Unknown;
}

void CommandHandler::execute(Command cmd) {
    switch (cmd) {
        case Command::Clear:    _clear(); break;
        case Command::Help:     _help(); break;
        case Command::Reboot:   _reboot(); break;
        case Command::Panic:    _panic(); break;
        case Command::Halt:     _halt(); break;
        case Command::Version:  _version(); break;
        case Command::Unknown:  _unknown(); break;
        case Command::Empty:
        default:
            break;
    }
}

/* -------------------------------------------- */
/*                    PRIVATE                   */
/* -------------------------------------------- */

u32 CommandHandler::_getWordLen(const vga::Char* buf, const u32 len) {
    u32 wordLen = 0;

    while (wordLen < len && buf[wordLen].isAlphanum())
        ++wordLen;
    return wordLen;
}

/* ---------------------------------------- */

void CommandHandler::_clear() {
    WindowManager::clearScreen();
}

void CommandHandler::_help() {
    WindowManager::write("Available commands:");
    WindowManager::newLine();
    for (u8 cmdIndex = (u8)Command::First; cmdIndex < COMMAND_COUNT; cmdIndex++) {
        WindowManager::write(' ');
        WindowManager::write(COMMANDS_NAME[cmdIndex]);
        if (cmdIndex != (u8)Command::Last)
            WindowManager::newLine();
    }
}

void CommandHandler::_panic() {
    ui::WindowManager::newLine();
    beginKernelPanic("Explicit panic.");
}

void CommandHandler::_halt() {
    while (true)
        core::hlt();
}

void CommandHandler::_reboot() {
    constexpr const u8 RESTART = 0x0E;
    core::outB(0xCF9, RESTART);
}

void CommandHandler::_version() {
    WindowManager::write("KFS pre-alpha 0.0.1 (jk just a school project lol)");
}

/* -------------------------------------------- */

void CommandHandler::_unknown() {
    WindowManager::write("Unknown command. Type 'help' for a list of available commands.");
}

} // namespace ui