/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:17:41 by etran             #+#    #+#             */
/*   Updated: 2024/02/15 17:43:41 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"
# include "utils.h"

namespace vga {
class Char;
}

namespace ui {

/* -------------------------------------------- */
/*                     ENUMS                    */
/* -------------------------------------------- */

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

    static Command      parse(const vga::Char* buf, const u32 len);
    static void         execute(Command cmd);

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

    static u32              _getWordLen(const vga::Char* buf, const u32 len);

    static void             _clear();
    static void             _help();
    static void             _reboot();
    static void             _panic();
    static void             _halt();

    // static void             _echo(const vga::Char* buf, const u32 len);

}; // class CommandHandler

} // namespace ui