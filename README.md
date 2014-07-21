### ChibiOS/RT running on STM32F4Stick board

There are two options to program the board:

1. ST-Link via SWD pins using an external programmer
2. PX4 bootloader using USB cable

You can choose to generate binaries for each option by enabling/disabling(yes/no) `USE_PX4_BOOTLOADER` in the `Makefile`.
* Enabling `USE_PX4_BOOTLOADER` will generate a binary and `.px4` file that is downloadable with the PX4 uploader python script. This binary (`.bin` file) should not be downloaded with st-link since it has different addresses for some stuff
* Enabling `UPLOAD_PX4` will automatically attempt to download the binary using the PX4 uploader python script if `USE_PX4_BOOTLOADER` is enabled
* A0 and A1 pins are tied to LEDs, so they will be blinking when the bootloader is waiting for a binary

Tested on Windows 7 and Mac OS. Win 8 and Linux is not yet tested.

#### Instructions for setting up the PX4 bootloader

#### Windows

* Program the board with the `boot/px4stick_bl.bin` bootloader binary using ST-Link Utility software
* Download & extract ChibiStudio from http://sourceforge.net/projects/chibios/files/ChibiStudio/ under `C:\ChibiStudio\` directory
* Download & install Python from https://www.python.org/download/releases/2.7.8/ (Windows x86 MSI Installer (2.7.8)) Make sure to enable `Add to PATH` section in the installation
* Download & install PySerial from https://pypi.python.org/pypi/pyserial#downloads (pyserial-2.7.win32.exe)
* Plug in the USB cable to the board. Open Windows Device Manager and find the unknown device. Right click on properties and update/install the driver. You will need to point Windows to the `driver` directory in the project. Once the driver have finished installing, the STMStick board will show up as a PX4 STMSTICK COM port in Device Manager


* Download stmstick_blinky.zip and extract it under `C:\ChibiStudio\`
* Run eclipse. Hit File->Import then choose General->Existing Projects into Workspace hit Next
* In Select root directory, Browse and select `C:\ChibiStudio\stmstick_blinky` and leave the rest default and hit Finish.
* Now from Project Explorer, right click on Others and hit Properties
* Locate and enable `stmstick_blinky` from the list and hit OK
* stmstick_blinky now should show up under Others in Project Explorer
* You can now hit Build project, and see a `.bin` and `.px4` binaries are generated if python is installed successfully and added to the PATH
* You can also upload the px4 binary to the board by enabling `UPLOAD_PX4` in `Makefile`

#### Linux/Mac OS

* Program the board with the `px4stick_bl.bin` bootloader binary using [stlink](https://github.com/texane/stlink) software: `st-flash write boot/px4stmstick_bl.bin 0x08000000`
* Install Python 2.7 and PySerial
* OPTIONAL: Import the project to eclipse
* Plug-in the board, enable UPLOAD_PX4 in Makefile, and hit Build. This should upload the binary using the python script
