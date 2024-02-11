/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:40:29 by etran             #+#    #+#             */
/*   Updated: 2024/02/11 03:07:34 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "types.h"

namespace lib
{
	extern "C" i32 memCmp(void const *s0, void const *s1, usize n) __attribute__((nonnull));
	extern "C" i32 strCmp(char const *s0, char const *s1) __attribute__((nonnull));

	extern "C" usize strLen(char const *s) __attribute__((nonnull));

	extern "C" void *memCpy(void *dst, void const *src, usize n) __attribute__((nonnull));
	extern "C" void *memSet(void *dst, u8 c, usize n) __attribute__((nonnull));

	extern "C" char *strCpy(char *dst, char const *src) __attribute__((nonnull));
} // namespace lib
