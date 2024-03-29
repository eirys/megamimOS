/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 04:12:54 by jodufour          #+#    #+#             */
/*   Updated: 2024/02/14 20:40:09 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <iostream>

struct Test
{
	char const *name;
	bool (*fn)(void);
};

bool testStrLen(void);
bool testStrCmp(void);
bool testStrCpy(void);
bool testMemCmp(void);
bool testMemCpy(void);
bool testMemSet(void);
bool testMemMov(void);

static constexpr Test TESTS[] = {
	{"strLen", testStrLen},
	{"strCmp", testStrCmp},
	{"strCpy", testStrCpy},
	{"memCmp", testMemCmp},
	{"memCpy", testMemCpy},
	{"memSet", testMemSet},
	{"memMov", testMemMov},
};
static constexpr usize TESTS_LEN = sizeof(TESTS) / sizeof(*TESTS);

#define OK "\033[32mok\033[0m\n"
#define FAILED "\033[31mfailed\033[0m\n"

int main(void)
{
	for (usize i = 0; i < TESTS_LEN; ++i)
		std::cout << "Testing " << TESTS[i].name << "... " << (TESTS[i].fn() ? OK : FAILED);
	return 0;
}
