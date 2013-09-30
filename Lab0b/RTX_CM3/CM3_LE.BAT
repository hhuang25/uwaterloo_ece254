SET PATH=C:\Keil\ARM\ARMCC\bin\;C:\Program Files\Common Files\Microsoft Shared\Windows Live;C:\Python33\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x86;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x64;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x86;C:\Program Files (x86)\Intel\OpenCL SDK\2.0\bin\x64;C:\cygwin\bin;D:\Programming\Android\adt-bundle-windows-x86_64-20130522\adt-bundle-windows-x86_64-20130522\sdk\platform-tools;C:\Program Files\Common Files\Microsoft Shared\Windows Live
SET CPU_TYPE=Cortex-M3
SET CPU_VENDOR=ARM
SET UV2_TARGET=CM3_LE
SET CPU_CLOCK=0x00B71B00
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_task.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_system.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_event.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_list.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_mailbox.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_semaphore.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_time.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_timer.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_mutex.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_robin.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\rt_membox.__i"
"C:\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\cm3_le\svc_table._ia"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\cm3_le\hal_cm3.__i"
"C:\Keil\ARM\ARMCC\bin\ArmAr" --Via "ArInp.Scr"
cmd.exe /C copy ArInp.Scr CM3_LE\BuildLib.scr
