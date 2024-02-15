/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 01:24:31 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 01:30:48 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_handler.h"
#include "debug.h"
#include "vga.h"
#include "core.h"
#include "lib.h"
#include "panic.h"

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

CommandResult CommandHandler::execute(Command cmd) {
    switch (cmd) {
        case Command::Clear:
        case Command::Help:
        case Command::Panic:    _panic(); break;
        case Command::Reboot:
        case Command::Halt:     _halt(); break;
        case Command::Empty:    break;

        case Command::Unknown:
        default:                return CommandResult::Failure;
    }
    return CommandResult::Success;
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

void CommandHandler::_halt() {
    while (true)
        core::hlt();
}

void CommandHandler::_panic() {
    beginKernelPanic();
}

} // namespace ui