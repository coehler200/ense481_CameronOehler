# Lab 3

Cameron Oehler (200384643)

The objective of this lab was to implement and test sin and cos functions which take in integer values and use a taylor series to aproximate the real values of sin() and cos().

## Setup
Assembler Flags: `-mcpu=cortex-m3 -g3 -DDEBUG -c -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb`

Compiler Flags: `-mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity --specs=nano.specs -mfloat-abi=soft -mthumb`

Linker Flags: `-mcpu=cortex-m3 -T"C:\Users\coehl\Documents\C++\ense481\lab3\STM32F103RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="${BuildArtifactFileBaseName}.map" -Wl,--gc-sections -static -u _printf_float --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group`

## Results
The following times were recorded using the internal TIM2 of the STM32F103RB

| Test | Avg Ticks | WCET Ticks |
| -------- | ------- | ------ |
| normal sin | 3075 | 3668 |
| normal cos | 3102 | 3952 |
| taylor sin | 350 | 354 |
| taylor cos | 311 | 314 |

The taylor series functions run much faster

Unfortunatly there is some sort of bug in my code as the functions do not output values that are consistant with the real sin() and cos() functions. The results are listed below.

With an input of 5deg=0.0872665rad
| Variable | Value |
| -------- | ------- |
| rad | 0.087266 |
| bam | 0x38E |
| rad_to_bam_to_rad | 0.087245 |
| normal sin | 0.087156 |
| normal cos | 0.996195 |
| taylor sin | 0.273720 |
| taylor cos | 3.129608 |