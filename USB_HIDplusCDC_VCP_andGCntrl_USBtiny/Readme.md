To clone this repo with USBtiny use:
git clone --recursive https://github.com/trteodor/USB-Mastering-Device-and-Host-my-projects
or after normal clone use:
* git submodule init

And:

* git submodule update
If you want download all submodules in this repository use:
* git submodule update --init --recursive
On top directory of the repo (not here)

Prepared example is build from composite USB device:
* VCP - Working as echo

* Gamecontroller -  i use Device from this link: http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Classic_Controller

To Create this example i used USB Stack delivered by tinyUSB. In my opinion this stack is very friendly for user
but it is only my opinion.


 
 Version classic, and pro classic - (communication is the same)

**How connect:** (Use Board: Well knowed - BluePill with stm32f103c8t6
![Connections](https://github.com/trteodor/USB-Mastering-Device-and-Host-my-projects/blob/master/pictures/STM32-WiiContollerClassic%20normal%20and%20Pro%20its%20same.jpg)

How test in Windows 10:
Run the app from menustart:
* joy.cpl

# References:

http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Classic_Controller


https://www.artekit.eu/stm32-usb-gamepad-interface/?fbclid=IwAR1iSHBsJSUVjJLKArsPc_yZ_MWaXWk79tJ8i753xQ9sc5e9BVFiAW36ljQ