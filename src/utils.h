/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:17:25 by etran             #+#    #+#             */
/*   Updated: 2024/02/07 00:55:36 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define STR(X) #X

template <class Enum>
static inline
constexpr u32 enumSize() {
    return static_cast<u32>(Enum::Last) - static_cast<u32>(Enum::First) + 1;
}

template <class Enum>
static inline
constexpr bool hasFlag(const Enum value, const Enum flag) {
    return (static_cast<u32>(value) & static_cast<u32>(flag)) != 0;
}

template <class Enum>
static inline
constexpr Enum addFlag(const Enum value, const Enum flag) {
    return static_cast<Enum>(static_cast<u32>(value) | static_cast<u32>(flag));
}

template <class Enum>
static inline
constexpr Enum removeFlag(const Enum value, const Enum flag) {
    return static_cast<Enum>(static_cast<u32>(value) & ~static_cast<u32>(flag));
}

static inline
constexpr u32 strlen(const i8* str) {
    u32 len = 0;
    while (str[len]) ++len;
    return len;
}