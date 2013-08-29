/*
 * eclib_test_main.c
 *
 *  Created on: 2008-7-24
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <eclib/eclib_types.h>
#include <stdio.h>

/* test functions */
uint16_t eclib_test_queue(void);
uint16_t eclib_test_queue2(void);
uint16_t eclib_test_array(void);
uint16_t eclib_test_set(void);
uint16_t eclib_test_set_2(void);
uint16_t eclib_test_button(void);

int main()
{
	uint16_t	nErrorsFound = 0;

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	fprintf(stdout, "%s\n", "dT\terrors\t\tdT\terrors\t");
#if 0
	nErrorsFound += eclib_test_queue();
	nErrorsFound += eclib_test_queue2();
	nErrorsFound += eclib_test_array();
	nErrorsFound += eclib_test_set();
	nErrorsFound += eclib_test_set_2();
#endif

	nErrorsFound += eclib_test_button();

	return 0;
}
