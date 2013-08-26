/*
 * fsm_demo_actions.c
 *
 *  Created on: May 3, 2011
 *      Author: mitko <Dimitar.Peikov@gmail.com>
 */

#include <stdio.h>

void action_one() {
	printf("%s\n", __PRETTY_FUNCTION__);
}

void action_two() {
	printf("%s\n", __PRETTY_FUNCTION__);
}

void action_three() {
	printf("%s\n", __PRETTY_FUNCTION__);
}

void action_four() {
	printf("%s\n", __PRETTY_FUNCTION__);
}

void action_onEnter() {
	printf("%s\n", __PRETTY_FUNCTION__);
}

void action_onExit() {
	printf("%s\n", __PRETTY_FUNCTION__);
}

void action_doStart() {
	printf("%s\n", __PRETTY_FUNCTION__);
}

void action_doEnd() {
	printf("%s\n", __PRETTY_FUNCTION__);
}
