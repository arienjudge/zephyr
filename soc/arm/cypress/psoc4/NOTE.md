TODO:

Introduce psoc 4 support by slowly following file changes as in
1. https://github.com/zephyrproject-rtos/zephyr/pull/8408/files#diff-a55ad1981fb33ce7ef7a25180649ec42c72414b047c801b06c8a25fcfa06184d
    * Check soc.c/soc.h are suitable for psoc4
    * add psoc4 pdl driver code to external cypress lib
2. https://github.com/zephyrproject-rtos/zephyr/pull/28527/files#diff-46bc441a559f89a487640912dc545156f52dfd2c7e6dd427a6f6d1bd273a18f5
3. Anything else useful @ https://github.com/zephyrproject-rtos/zephyr/pulls?q=psoc
4. Keep track of https://github.com/zephyrproject-rtos/zephyr/pull/44211


----------------------------------------
24/6/2022
----------------------------------------
Added mtb-pdl-cat2 to hal_infineon repo. Started building necessary build scripts in `zephyr/modules/hal_infineon`.
Some key differences. No `cy_device.c` in mtb-pdl-cat2, so might need to do this device bring up/init elsewhere if needed.
Some variations in peripheral sets. See comments in mtb-pdl-cat2 CMake file.
Added `SOC_FAMILY_PSOC4` entry to  `zephyr/modules/hal_infineon/KConfig` (see comment about best if-else approach). Now need to go through zephyr driver hals and create `KConfig.psoc4` where necessary.
Search for `KConfig.psoc6` for examples.

Also need to add `SOC_FAMILY_PSOC4` to `soc/arm/cypress` as done for `SOC_FAMILY_PSOC6`, and any relevant `KConfig.series` files.


----------------------------------------
31/7/2022
----------------------------------------
Noticed no device header for CY8C4247AZI..... will need to assemble and confirm functionality of existing driver files with this part.

Added KConfig.soc, KConfig.series and KConfig.defconfig.series to `soc/arm/cypress/psoc4`.
Modified `soc/arm/cypress/KConfig` to enable psoc4
Started adding `boards/arm/cy8ckit_042`. Some files incomplete

TODO:
  * Need to check `soc/arm/cypress/psoc4/soc.c` implementation is valid.
  * Need to implement `soc/arm/cypress/common/cypress_psoc6_dt.h` equivalent for psoc4 and review soc_gpio.c entries
  * Need to pull up board schematics to define board devicetree. Focus on selecting an appropriate UART for hello world example.
  * Need to build psoc4 specific dtsi files in `dts/arm/cypress/`
  * Check openocd configuration for board -- looks like there's a psoc4.cfg availalbe. Trusting it works
  * Test build
  * Assemble Zephyr UART driver for psoc4
  * Set up vector table?



-----------------------------------------
10/8/2022
-----------------------------------------
Added the following KConfig.psoc4 entries to zephyr driver hals.
  * "drivers/spi/Kconfig.psoc4"
  * "drivers/serial/Kconfig.psoc4"
  * "drivers/spi/Kconfig.psoc4"
  * "drivers/hwinfo/Kconfig"
Started adding relevant driver .c files.
  * gpio -- added `gpio_psoc4.c`, modified from psoc6 flavour.
  * spi
  * serial
  * hwinfo -- added. Doesn't look like psoc6 flavour does anything useful??

-----------------------------------------
14/8/2022
-----------------------------------------
Sarted adding `psoc4200m_config.h`. Some issues around not having relevant cyip files for the right block versions - eg whichever version of the CSD IP is used for the 4200M doesn't have a file in the cat2 pdl. Need to check each peripheral register set 1 by 1.
  * Updated clock connection settings

-----------------------------------------
17/8/2022
-----------------------------------------
Started adding cy8c4247azi-m485.h


-----------------------------------------
19/9/2022
-----------------------------------------
Experimented with kitprog debug interface on openocd and gdb. May switch approach to working on codebase to getting zephyr compiling for the chip first.
Needed Zadig to install an appropriate WinUSB driver for the kitprog bulk interface.
Run `openocd -f interface/kitprog.cfg -f target/psoc4.cfg`.
Run gdb in C:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2020-q4-major\bin as
* `arm-none-eabi-gdb.exe`
* `file C:/Users/Arien/Documents/PSoC\ Creator/PSOC4200M_Test/Software_Transmit_UART01.cydsn/CortexM0/ARM_GCC_541/Debug/Software_Transmit_UART01.elf`
* `target extended-remote 127.0.0.1:3333`

-----------------------------------------
21/9/2022
-----------------------------------------
Renamed CY8CKIT_042 instances to CY8CKIT_044
Repaired jlink

-----------------------------------------
29/9/2022
-----------------------------------------
added boards\arm\cy8ckit_044\cy8ckit_044_m0.dts
<!-- added dts\bindings\interrupt-controller\cypress,psoc4-intmux.yaml
added dts\bindings\interrupt-controller\cypress,psoc4-intmux-ch.yaml -->
added dts\arm\cypress\psoc4.dtsi WIP

-----------------------------------------
3/10/2022
-----------------------------------------
modified soc.c for stub implementation. Should consider clock settings later.

-----------------------------------------
11/10/2022
-----------------------------------------
started adding cyip_srsslt_m.h - up to PWR_KEY_DELAY
need to figure out what to do with wdt

Ongoing TODO:
  * Check required definitions for gpio files and create a startup_psoc4200m.c to add a vectortable definition.
    * may want to consider "zephyr-ising" the _RAM_VECTOR_TABLE. check what happened with psoc6, likely just needs defs in soc.c
  * Finish dts\arm\cypress\psoc4.dtsi. Compare psoc6.dtsi to TRM and RRM
  * `drivers/gpio`
    * Need to complete psoc4200*_config.h file to pull in necessary cyip_gpio.h file in pdl2 for GPIO_PRT_Type type definition
      * Need to go through peripheral configuration as appropriate for 4200M. CSD is wrong version
    * This config will should be included by relevant cy8c42***.h file, which is selected by the definition check in cy_device_headers.h, selected by the KConfig.soc in the `soc/arm/cypress/psoc4` folder.
  * `drivers/spi`
  * `drivers/serial`
  * Need to check `soc/arm/cypress/psoc4/soc.c` implementation is valid.
  * Need to implement `soc/arm/cypress/common/cypress_psoc6_dt.h` equivalent for psoc4 and review soc_gpio.c entries
  * Need to pull up board schematics to define board devicetree. Focus on selecting an appropriate UART for hello world example.
  * Should lead into fixing up `boards/arm/cy8ckit_042`
  * Need to build psoc4 specific dtsi files in `dts/arm/cypress/`
  * Test build
  * Assemble Zephyr UART driver for psoc4
  * Set up vector table?






  Checking cypress ip blocks:

cyip_can.h
cyip_cpuss_v3.h?? - missing protection-wounding + priv_ram-> mtb_ctl only 3 SL_CTL
cyip_ctbm.h - missing dft_ctrl
cyip_dmac_v3.h
cyip_gpio.h - no SIO, no DS, no FILT_CONFIG, no VREFGEN
cyip_hsiom.h - no pump_ctl, 
cyip_lcd_v2.h
cyip_lpcomp_v2.h
cyip_pass.h - no dft_ctrl no pass_ctrl no dsab_dft
cyip_peri.h - no div_8 no div_24_5
cyip_sar.h - no dft_ctrl  no mux_switch1
cyip_scb_v2.h - no cmd_resp
cyip_spcif_v3.h - no nvl_wr_data
cyip_tcpwm_v2.h
cyip_wco.h - missing status, wdt_*




cyip_srsslt is a very different beast. this driver will need to be remade for the psoc4200m

* DFT_SELECT appears to be missing. PSOC_Creator generated code indicates DFT_SELECT at undocumented register (0x400b0110u)
  * confirm values for DFT_SELECT in PSOC_CREATOR


clk_dft_select actually exists
no wdt_disable_key, wdt_counter or srss_intr*
pwr_bg_trim1 exists 0x400bff10 and pwr_bg_trim2 at 0x400bff14
no clk_imo_select reg
pwr_pwrsys_trim1 exists at 0x400bff00
clk_imo_trim3 exists
tst_mode appears to exist, documented as a separate "block", but uses the same address as the 4100s.


wdt_disable_key used by cy_wdt.h in Cy_WDT_IsEnabled, Cy_WDT_Enable, Cy_WDT_Disable. Easily replaced.
wdt_counter used once in cy_wdt.h for Cy_WDT_GetCount. This is used in mcuboot\boot\cypress\libs\watchdog\watchdog.c
srss_intr_mask used in cy_Wdt.h Cy_WDT_MaskInterrupt and Cy_WDT_UnmaskInterrupt and cy_wdt.c Cy_WDT_ClearInterrupt
clk_imo_select used heavily in cy_sysclk.c - need an alternative clock driver? or disable certain imo related funcs.
