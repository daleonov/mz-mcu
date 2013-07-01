SET PATH=C:\Program Files\Keil\ARM\ARMCC\bin\;C:\Program Files\CollabNet;C:\Program Files\Embarcadero\RAD Studio\11.0\bin;C:\Users\daniel\Documents\RAD Studio\11.0\Bpl;C:\Program Files\Embarcadero\RAD Studio\11.0\bin64;C:\Users\daniel\Documents\RAD Studio\11.0\Bpl\Win64;C:\Program Files\Python26\;C:\Program Files\Common Files\Microsoft Shared\Windows Live;C:\Program Files\PC Connectivity Solution\;C:\PROGRA~1\Borland\CBUILD~1\Bin;C:\PROGRA~1\Borland\CBUILD~1\Projects\Bpl;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\MKVtoolnix;C:\Program Files\Windows Live\Shared;C:\Program Files\MATLAB\R2010a\bin;C:\Program Files\Toshiba\Bluetooth Toshiba Stack\sys\;C:\Program Files\TortoiseGit\bin;C:\Program Files\QuickTime\QTSystem\;C:\Program Files\Delphi7SE\bin;C:\Program Files\Delphi7SE\Projects\BPL;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\;C:\FPC\2.6.2\bin\i386-Win32;C:\Program Files\CollabNet;C:\XE4\bin;C:\Users\Public\Documents\RAD Studio\11.0\Bpl;C:\XE4\bin64;C:\Users\Public\Documents\RAD Studio\11.0\Bpl\Win64;C:\Windows\system32;C:\WINDOWS;C:\Windows\system32\Wbem;C:\Windows\system32\WindowsPowerShell\v1.0
SET CPU_TYPE=STM32F100RB
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x007A1200
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\output\startup_stm32f10x_hd_vl._ia"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\core_cm3.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\system_stm32f10x.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\main.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\periph_low.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\fifo.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\time.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\periph_hal.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\stm32f10x_gpio.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\stm32f10x_rcc.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\stm32f10x_usart.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\misc.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\stm32f10x_flash.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\stm32f10x_tim.__i"
"C:\Program Files\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\Output\Firmware.lnp"
C:\Program Files\Keil\ARM\ARMCC\bin\fromelf.exe ".\Output\Firmware.axf" --i32combined --output ".\Output\Firmware.hex"
