TODO:

Introduce psoc 4 support by slowly following file changes as in
1. https://github.com/zephyrproject-rtos/zephyr/pull/8408/files#diff-a55ad1981fb33ce7ef7a25180649ec42c72414b047c801b06c8a25fcfa06184d
    * Check soc.c/soc.h are suitable for psoc4
    * add psoc4 pdl driver code to external cypress lib
2. https://github.com/zephyrproject-rtos/zephyr/pull/28527/files#diff-46bc441a559f89a487640912dc545156f52dfd2c7e6dd427a6f6d1bd273a18f5
3. Anything else useful @ https://github.com/zephyrproject-rtos/zephyr/pulls?q=psoc
4. Keep track of https://github.com/zephyrproject-rtos/zephyr/pull/44211



24/6/2022

Added mtb-pdl-cat2 to hal_infineon repo. Started building necessary build scripts in `zephyr/modules/hal_infineon`.
Some key differences. No `cy_device.c` in mtb-pdl-cat2, so might need to do this device bring up/init elsewhere if needed.
Some variations in peripheral sets. See comments in mtb-pdl-cat2 CMake file.
Added `SOC_FAMILY_PSOC4` entry to  `zephyr/modules/hal_infineon/KConfig` (see comment about best if-else approach). Now need to go through zephyr driver hals and create `KConfig.psoc4` where necessary.
Search for `KConfig.psoc6` for examples.

Also need to add `SOC_FAMILY_PSOC4` to `soc/arm/cypress` as done for `SOC_FAMILY_PSOC6`, and any relevant `KConfig.series` files.

