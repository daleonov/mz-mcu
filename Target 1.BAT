SET PATH=C:\Keil\ARM\ARMCC\bin\;C:\Program Files (x86)\AMD APP\bin\x86_64;C:\Program Files (x86)\AMD APP\bin\x86;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\ATI Technologies\ATI.ACE\Core-Static;C:\Program Files (x86)\QuickTime\QTSystem\;C:\Program Files (x86)\Toshiba\Bluetooth Toshiba Stack\sys\;C:\Program Files (x86)\Toshiba\Bluetooth Toshiba Stack\sys\x64\;C:\Program Files\TortoiseGit\bin;C:\Program Files\MiKTeX\miktex\bin\x64\
SET CPU_TYPE=STM32F100RB
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x007A1200
"C:\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\output\startup_stm32f10x_hd_vl._ia"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\core_cm3.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\system_stm32f10x.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\mcu_leds.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\mcu_main.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\mcu_system.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\stm32f10x_gpio.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\stm32f10x_rcc.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\stm32f10x_usart.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\misc.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\stm32f10x_flash.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\stm32f10x_tim.__i"
"C:\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\Output\Firmware.lnp"
C:\Keil\ARM\ARMCC\bin\fromelf.exe ".\Output\Firmware.axf" --i32combined --output ".\Output\Firmware.hex"
