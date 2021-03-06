#!/usr/bin/make

all:	build test

build:
	$(MAKE) -C eclib all
	$(MAKE) -C calendar all
	$(MAKE) -C fsm all
	$(MAKE) -C eclib_test all
	$(MAKE) -C calendar_test all
	$(MAKE) -C fsm_test all

test:
	$(MAKE) -C eclib_test test
	$(MAKE) -C calendar_test test
	$(MAKE) -C fsm_test test

clean:
	-$(MAKE) -C eclib clean
	-$(MAKE) -C calendar clean
	-$(MAKE) -C fsm clean
	-$(MAKE) -C eclib_test clean
	-$(MAKE) -C calendar_test clean
	-$(MAKE) -C fsm_test clean

