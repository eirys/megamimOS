/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:17:41 by etran             #+#    #+#             */
/*   Updated: 2024/02/13 22:24:23 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "core.h"
# include "vga.h"
# include "lib.h"

#include "debug.h"

namespace ui {

class CommandHandler final {
public:
    /* ---------------------------------------- */
    /*                   ENUMS                  */
    /* ---------------------------------------- */

    enum class Command: u8 {
        Unknown,

        Clear,
        Help,
        Panic,
        Reboot,
        Halt,

        Version,
        Echo,
        Env,

        First = Unknown,
        Last = Env
    };

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
    void execute(Command cmd) {
        switch (cmd) {
            case Command::Clear:
            case Command::Help:
            case Command::Panic:    return _panic();
            case Command::Reboot:
            case Command::Halt:     return _halt();

            case Command::Unknown:
            default:                break;
        }
    }

    /* ---------------------------------------- */

    void parse(const vga::Char* buf, const u32 len) {
        char buff[vga::WIDTH + 1];

        lib::memcpy(buff, buf, len);

        LOG(buff);
        LOG_C('\n');
    }

private:
    /* ---------------------------------------- */
    /*                  METHODS                 */
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