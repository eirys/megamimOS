/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:11:22 by etran             #+#    #+#             */
/*   Updated: 2024/02/05 16:22:52 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

#include "utils.h"

enum class TerminalID: uint8_t {
    User0 = 0,
    User1,
    User2,
    User3,
    User4,
    User5,
    User6,
    User7,
    User8,

    First = User0,
    Last = User8
};

class Terminal {
public:

private:
}; // class Terminal