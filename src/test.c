#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdbool.h>
#include <cmocka.h>
#include "cvent.h"

bool Called = false;

void mock_callback()
{
	function_called();
}

void mock_callback_with_global_value()
{
	Called = true;
}

///////////////////////////////////////////////////////////////////////////////
static void should_execute_callback_on_event(void **state)
{
	init();
	sub(EventA, mock_callback);
	expect_function_call(mock_callback);
	pub(EventA);
}

///////////////////////////////////////////////////////////////////////////////
static void should_execute_all_callbacks_on_event(void **state)
{
	init();
	sub(EventA, mock_callback);
	sub(EventA, mock_callback);
	sub(EventA, mock_callback);
	expect_function_calls(mock_callback, 3);
	pub(EventA);
}

///////////////////////////////////////////////////////////////////////////////
static void should_not_callback_on_different_event(void **state)
{
	init();
	sub(EventA, mock_callback);
	pub(EventB);
	assert_false(Called);
}

///////////////////////////////////////////////////////////////////////////////
int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(should_execute_callback_on_event),
		cmocka_unit_test(should_execute_all_callbacks_on_event),
		cmocka_unit_test(should_not_callback_on_different_event)
	};

	return cmocka_run_group_tests(tests, NULL, NULL);
}
