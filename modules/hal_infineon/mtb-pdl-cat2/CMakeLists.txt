# Copyright (c) 2022 Cypress Semiconductor Corporation.
#
# SPDX-License-Identifier: Apache-2.0

set(pdl_dir             ${ZEPHYR_HAL_INFINEON_MODULE_DIR}/mtb-pdl-cat2)
set(pdl_drv_dir         ${ZEPHYR_HAL_INFINEON_MODULE_DIR}/mtb-pdl-cat2/drivers)
set(pdl_dev_dir   ${ZEPHYR_HAL_INFINEON_MODULE_DIR}/mtb-pdl-cat2/devices)

zephyr_compile_definitions(${CONFIG_SOC_PART_NUMBER})

# Add mtb-pdl-cat1
zephyr_include_directories(${pdl_drv_dir}/include)
zephyr_include_directories(${pdl_dev_dir}/include)
zephyr_include_directories(${pdl_dev_dir}/include/ip)
zephyr_include_directories(${pdl_dev_dir}/templates/COMPONENT_MTB)

zephyr_library_sources_ifdef(CONFIG_CPU_CORTEX_M0
  ${pdl_drv_dir}/source/COMPONENT_CM0/TOOLCHAIN_GCC_ARM/cy_syslib_gcc.S)
zephyr_library_sources_ifdef(CONFIG_CPU_CORTEX_M0PLUS
  ${pdl_drv_dir}/source/COMPONENT_CM0P/TOOLCHAIN_GCC_ARM/cy_syslib_gcc.S)

zephyr_library_sources(${pdl_dev_dir}/templates/COMPONENT_MTB/system_cat2.c)

# Peripheral drivers
zephyr_library_sources_ifdef(CONFIG_USE_INFINEON_UART     ${pdl_drv_dir}/source/cy_scb_uart.c)
zephyr_library_sources_ifdef(CONFIG_USE_INFINEON_ADC      ${pdl_drv_dir}/source/cy_sar.c)
zephyr_library_sources_ifdef(CONFIG_USE_INFINEON_I2C      ${pdl_drv_dir}/source/cy_scb_i2c.c)
zephyr_library_sources_ifdef(CONFIG_USE_INFINEON_SPI      ${pdl_drv_dir}/source/cy_scb_spi.c)
zephyr_library_sources_ifdef(CONFIG_USE_INFINEON_TIMER    ${pdl_drv_dir}/source/cy_tcpwm_counter.c)
zephyr_library_sources_ifdef(CONFIG_USE_INFINEON_PWM      ${pdl_drv_dir}/source/cy_tcpwm_pwm.c)
#zephyr_library_sources_ifdef(CONFIG_USE_INFINEON_LPTIMER  ${pdl_drv_dir}/source/cy_mcwdt.c) -- no mcwdt in cat2? replace with cy_wdc??
#zephyr_library_sources_ifdef(CONFIG_USE_INFINEON_RTC      ${pdl_drv_dir}/source/cy_rtc.c) -- no rtc in cat2?
#zephyr_library_sources_ifdef(CONFIG_USE_INFINEON_SDIO     ${pdl_drv_dir}/source/cy_sd_host.c)
zephyr_library_sources_ifdef(CONFIG_SOC_FAMILY_PSOC6      ${pdl_drv_dir}/source/cy_sysint.c)

if(CONFIG_USE_INFINEON_TRNG)
  zephyr_library_sources(${pdl_drv_dir}/source/cy_crypto.c)
  zephyr_library_sources(${pdl_drv_dir}/source/cy_crypto_core_trng.c)
endif()

if(CONFIG_USE_INFINEON_UART OR CONFIG_USE_INFINEON_I2C OR CONFIG_USE_INFINEON_SPI)
  zephyr_library_sources(${pdl_drv_dir}/source/cy_scb_common.c)
endif()

#this doesn't exist for cat2, see what cy_sar depends on.
# if(CONFIG_USE_INFINEON_ADC)
#   zephyr_library_sources(${pdl_drv_dir}/source/cy_sysanalog.c)
# endif()

# Common part
zephyr_library_sources(${pdl_drv_dir}/source/cy_flash.c)
zephyr_library_sources(${pdl_drv_dir}/source/cy_gpio.c)
# zephyr_library_sources(${pdl_drv_dir}/source/cy_ipc_drv.c)
# zephyr_library_sources(${pdl_drv_dir}/source/cy_ipc_pipe.c)
# zephyr_library_sources(${pdl_drv_dir}/source/cy_ipc_sema.c)
# zephyr_library_sources(${pdl_drv_dir}/source/cy_prot.c)
zephyr_library_sources(${pdl_drv_dir}/source/cy_sysclk.c)
zephyr_library_sources(${pdl_drv_dir}/source/cy_syslib.c)
zephyr_library_sources(${pdl_drv_dir}/source/cy_syspm.c)
zephyr_library_sources(${pdl_drv_dir}/source/cy_systick.c)
zephyr_library_sources(${pdl_drv_dir}/source/cy_trigmux.c)
zephyr_library_sources(${pdl_drv_dir}/source/cy_wdt.c)


#want to add a kconfig option for cy_seglcd.c !!
