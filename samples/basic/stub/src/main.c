/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

volatile int a = 0;

void main(void)
{
	int ret;

	while (1) {
		k_msleep(SLEEP_TIME_MS);
		a++;
	}
}
