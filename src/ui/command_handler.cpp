/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 01:24:31 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 17:45:54 by etran            ###   ########.fr       */
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

Command  CommandHandler::parse(const vga::Char* buf, const u32 len) {
    if (len == 0)
        return Command::Empty;

    const u32 wordLen = _getWordLen(buf, len);

    for (u8 cmdIndex = 0; cmdIndex < COMMAND_COUNT; cmdIndex++) {
        if (lib::memcmp(buf, COMMANDS[cmdIndex], wordLen) == 0)
            return (Command)cmdIndex;
    }

    return Command::Unknown;
}

void CommandHandler::execute(Command cmd) {
    switch (cmd) {
        case Command::Clear:    _clear(); break;
        case Command::Panic:    _panic(); break;
        case Command::Halt:     _halt(); break;
        case Command::Reboot:   _reboot(); break;

        case Command::Unknown:
        // TODO: indication
        case Command::Help:     _help(); break;

        // TODO
        case Command::Version:
        case Command::Echo:
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
        wordLen++;
    return wordLen;
}

/* ---------------------------------------- */

void CommandHandler::_clear() {
    WindowManager::clearScreen();
}

void CommandHandler::_help() {
    WindowManager::currentTerminal() << (i8*)"Available commands:";
    WindowManager::newLine();
    for (u8 cmdIndex = (u8)Command::First; cmdIndex <= (u8)Command::Last; cmdIndex++) {
        WindowManager::currentTerminal() << COMMANDS[cmdIndex];
        WindowManager::newLine();
    }
}

void CommandHandler::_halt() {
    while (true)
        core::hlt();
}

void CommandHandler::_panic() {
    beginKernelPanic("Explicit panic.");
}

void CommandHandler::_reboot() {
    constexpr const u8 RESTART = 0x0E;
    core::outB(0xCF9, RESTART);
}

} // namespace ui