/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:06:45 by etran             #+#    #+#             */
/*   Updated: 2024/02/16 14:27:36 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * This file is necessary for inheritance, and other obscure reasons...
 */
#include "lib.h"

// Inheritance
extern "C" void __cxa_pure_virtual() { asm volatile("hlt"); }

// Static initialization
extern "C" void __cxa_guard_acquire() {}

extern "C" void __cxa_guard_release() {}
extern "C" void __dso_handle() {}
extern "C" void __cxa_atexit() {}

void operator delete(void *) {}
void operator delete(void *, long unsigned int) {}
void operator delete(void *, unsigned int) {}
