/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 01:55:59 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 02:58:50 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "types.h"

namespace ui {

class ILayout;
struct KeyEvent;

class Keyboard final {
public:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Keyboard(Keyboard&& other) = delete;
    Keyboard(const Keyboard& other) = delete;
    Keyboard& operator=(Keyboard&& other) = delete;
    Keyboard& operator=(const Keyboard& other) = delete;
    ~Keyboard() = default;

    /* ---------------------------------------- */

    static void     handle(ILayout& layout);

private:
    /* ---------------------------------------- */
    /*                  METHODS                 */
    /* ---------------------------------------- */

    Keyboard() = default;

    /* ---------------------------------------- */

    static void     _handleInput(const KeyEvent& event);
    static void     _handleCommand();

}; // class Keyboard

} // namespace ui