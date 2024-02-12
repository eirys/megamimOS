/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodufour <jodufour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:20:26 by jodufour          #+#    #+#             */
/*   Updated: 2024/02/12 22:05:18 by jodufour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

struct Parameters
{
	char const *const s0;
	char const *const s1;
};

typedef i32 return_type;

struct Test
{
	Parameters const parameters;
	return_type const expected;
};

static constexpr Test TESTS[] = {
	{{"", ""}, 0},
	{{"", "A"}, -1},
	{{"b", ""}, 1},
	{{"+", "+"}, 0},
	{{"4", "2"}, 1},
	{{"foo", "foolish"}, -1},
	{{"Google", "Go"}, 1},
	{{"Kamehameha", "Kamehameha"}, 0},
	{{"What is this character?", "What is this character!"}, 1},
	{{"What those \x01 ?", "What those \x7F ?"}, -1},
	{{"Those \x92 are not even ASCII", "Those are \x80 are not even ASCII"}, 1},
	{{"Do you find the right \xDE\xAD diff?", "Do you find the right \xBE\xEF diff?"}, 1},
	{{"And if the first is not", "the same?"}, -1},
};
static constexpr usize TESTS_LEN = sizeof(TESTS) / sizeof(*TESTS);

/**
 * @brief Test the lib::strCmp function.
 *
 * @return true if the test was passed successfully, false otherwise.
 */
bool testStrCmp(void)
{
	for (usize i = 0; i < TESTS_LEN; ++i)
	{
		Parameters const &p = TESTS[i].parameters;
		return_type const ret = lib::strCmp(p.s0, p.s1);

		switch (TESTS[i].expected)
		{
		case 0:
			if (ret != 0)
				return false;
			break;
		case 1:
			if (ret <= 0)
				return false;
			break;
		case -1:
			if (ret >= 0)
				return false;
			break;
		}
	}
	return true;
}
