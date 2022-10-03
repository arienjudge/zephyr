/*
 * Copyright (c) 2018, Cypress
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/init.h>
#include <zephyr/arch/cpu.h>
#include <zephyr/arch/arm/aarch32/cortex_m/cmsis.h>

void Cy_SystemInit(void)
{
	//stub
}

static int init_cycfg_platform_wraper(const struct device *arg)
{
	ARG_UNUSED(arg);
	SystemInit();
	return 0;
}

SYS_INIT(init_cycfg_platform_wraper, PRE_KERNEL_1, 0);
