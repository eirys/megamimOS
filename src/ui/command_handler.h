/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:17:41 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 13:55:26 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "core.h"
# include "vga.h"
# include "lib.h"
# include "utils.h"

#include "debug.h"

namespace ui {

/* -------------------------------------------- */
/*                     ENUMS                    */
/* -------------------------------------------- */

enum class CommandResult: u8 {
    Success = 0,
    Failure = 1,
    Exit = 2
};

enum class Command: u8 {
    Clear   = 0,
    Help    = 1,
    Panic   = 2,
    Reboot  = 3,
    Halt    = 4,

    Version = 5,
    Echo    = 6,

    Empty   = 7,
    Unknown = 8,

    First = Clear,
    Last = Echo
};

class CommandHandler final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    CommandHandler() = default;
    CommandHandler(CommandHandler&& other) = default;
    CommandHandler(const CommandHandler& other) = default;
    CommandHandler& operator=(CommandHandler&& other) = default;
    CommandHandler& operator=(const CommandHandler& other) = default;
    ~CommandHandler() = default;

    /* ---------------------------------------- */

    static
    Command parse(const vga::Char* buf, const u32 len) {
        if (len == 0)
            return Command::Empty;

        const u32 wordLen = _getWordLen(buf, len);

        for (u8 cmdIndex = 0; cmdIndex < COMMAND_COUNT; cmdIndex++) {
            if (lib::memcmp(buf, COMMANDS[cmdIndex], wordLen) == 0)
                return (Command)cmdIndex;
        }

        return Command::Unknown;
    }

    static
    CommandResult execute(Command cmd) {
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

private:
    /* ---------------------------------------- */
    /*              STATIC MEMBERS              */
    /* ---------------------------------------- */

    static constexpr u32    MAX_CMD_LEN = 32;
    static constexpr u32    COMMAND_COUNT = enumSize<Command>();
    static constexpr i8     COMMANDS[COMMAND_COUNT][MAX_CMD_LEN] = {
        "clear",
        "help",
        "panic",
        "reboot",
        "halt",

        "version",
        "echo",
    };

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    static
    u32 _getWordLen(const vga::Char* buf, const u32 len) {
        u32 wordLen = 0;
        while (wordLen < len && buf[wordLen].isAlphanum())
            wordLen++;
        return wordLen;
    }

    /* ---------------------------------------- */

    static
    void _halt() {
        while (true)
            core::hlt();
    }

    inline static
    void _panic() {
        _halt();
    }

}; // class CommandHandler

} // namespace ui