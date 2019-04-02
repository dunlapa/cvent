#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdbool.h>
#include <cmocka.h>
#include <stdio.h>
#include "../event-table.h"

// TODO: add more tests
///////////////////////////////////////////////////////////////////////////////
static void should_return_int_from_char_array(void **state)
{
	KeyString string = "EventA";
	int hash = hash_key(string);
	assert_true(hash > 0);
}

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(should_return_int_from_char_array)
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
