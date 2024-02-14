/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etran <etran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:52:05 by etran             #+#    #+#             */
/*   Updated: 2024/02/14 20:56:42 by etran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exception.h"
#include "debug.h"
# include "idt_decl.h"

namespace cpu::idt {

# define _DECL_INTERNAL     __attribute__ ((no_caller_saved_registers)) static
# define _DECL_INTERRUPT    __attribute__ ((interrupt))

/* -------------------------------------------- */
/*                   FUNCTIONS                  */
/* -------------------------------------------- */

/* -------------- DIVISION ERROR -------------- */

_DECL_INTERNAL
void divisionErrorInternal() {
    LOG("division error");
    core::hlt();
}

_DECL_INTERRUPT
void divisionError(InterruptFrame* frame) {
    (void)frame;
    divisionErrorInternal();
}

/* ---------------- BREAKPOINT ---------------- */

_DECL_INTERNAL
void breakpointInternal() {
    LOG("breakpoint");
}

_DECL_INTERRUPT
void breakpoint(InterruptFrame* frame) {
    (void)frame;
    breakpointInternal();
}

# undef _DECL_INTERNAL
# undef _DECL_INTERRUPT

} // namespace cpu::idt