/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:20:26 by jodufour          #+#    #+#             */
/*   Updated: 2024/02/14 09:29:54 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

struct Parameters
{
	char const *const s;
};

typedef usize return_type;

struct Test
{
	Parameters const parameters;
	return_type const expected;
};

static constexpr Test TESTS[] = {
	{{""}, 0},
	{{"A"}, 1},
	{{"42"}, 2},
	{{"etran & jodufour"}, 16},
	{{"foo \x7F bar \x80 \xFF"}, 13},
	{{"We are all being used\n"
	  "Our lives have been abused\n"
	  "Still no one resists\n"
	  "I guess there 's nothing to lose\n"
	  "I am no longer confused\n"
	  "You' re killing my dreams\n"},
	 153},
};
static constexpr usize TESTS_LEN = sizeof(TESTS) / sizeof(*TESTS);

/**
 * @brief Test the lib::strLen function.
 *
 * @return `true` if the test was passed successfully, `false` otherwise.
 */
bool testStrLen(void)
{
	for (usize i = 0; i < TESTS_LEN; ++i)
	{
		Parameters const &p = TESTS[i].parameters;
		return_type const ret = lib::strLen(p.s);

		if (ret != TESTS[i].expected)
			return false;
	}
	return true;
}
