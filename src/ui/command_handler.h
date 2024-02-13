/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 00:17:41 by etran             #+#    #+#             */
/*   Updated: 2024/02/13 19:03:15 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "core.h"
# include "vga.h"

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

private:
    /* ---------------------------------------- */
    /*                ATTRIBUTES                */
    /* ---------------------------------------- */

    u8              m_cmdLine[vga::WIDTH] = { vga::Char::Empty };
    u8              m_lineLength = 0U;

    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    void _halt() const {
        while (true)
            core::hlt();
    }

    inline
    void _panic() const {
        _halt();
    }

}; // class CommandHandler

} // namespace ui