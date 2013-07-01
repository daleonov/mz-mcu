SET PATH=C:\Program Files\Keil\ARM\BIN40\;C:\Program Files\Common Files\Microsoft Shared\Windows Live;C:\Program Files\PC Connectivity Solution\;C:\PROGRA~1\Borland\CBUILD~1\Bin;C:\PROGRA~1\Borland\CBUILD~1\Projects\Bpl;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\MKVtoolnix;C:\Program Files\Windows Live\Shared;C:\Program Files\MATLAB\R2010a\bin;C:\Program Files\Toshiba\Bluetooth Toshiba Stack\sys\;C:\Program Files\TortoiseGit\bin;C:\Program Files\QuickTime\QTSystem\
SET ARMCC41INC=C:\Program Files\Keil\ARM\RV31\INC
SET ARMCC41LIB=C:\Program Files\Keil\ARM\RV31\LIB
SET CPU_TYPE=STM32F100RB
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x007A1200
"C:\Program Files\Keil\ARM\BIN40\ArmAsm" --Via ".\output\startup_stm32f10x_hd_vl._ia"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\core_cm3.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\system_stm32f10x.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\main.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\periph_low.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\fifo.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\time.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\packethandler.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\stm32f10x_gpio.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\stm32f10x_rcc.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\stm32f10x_usart.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\misc.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\stm32f10x_flash.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmCC" --Via ".\output\stm32f10x_tim.__i"
"C:\Program Files\Keil\ARM\BIN40\ArmLink" --Via ".\Output\Firmware.lnp"
C:\Program Files\Keil\ARM\BIN40\fromelf.exe ".\Output\Firmware.axf" --i32combined --output ".\Output\Firmware.hex"
