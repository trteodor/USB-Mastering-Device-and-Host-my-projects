Prepared example is build from composite USB device:
* VCP - Working as echo

* Gamecontroller -  i planning use Device from this link: http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Classic_Controller

To Create this example i used USB Stack delivered by CubeMX. In my opinion this stack isn't friendly but it is only my opinion. I had to rebuild
a large part of the stack.(Maybe i don't have else sufficient experiance to easy operate with this stack) 
You can check changes before this commit: 
__*"VCP and GameController Is Detected correctly"*__ 
to see what exacly i did. To check te process how i run this example.
 After regeration Source Code by CubeMX go to: (small change is required)
 * Middlewares\ST\STM32_USB_Device_Library\Class\usbd_cdc.c
 * Comment Line 655 656
 * //          USBD_CtlError(pdev, req);
 * //          ret = USBD_FAIL;
 
 Version classic, and pro classic - (communication is the same)
 
**How connect:** (Use Board: Well knowed - BluePill with stm32f103c8t6
![Connections](https://github.com/trteodor/USB-Mastering-Device-and-Host-my-projects/blob/master/pictures/STM32-WiiContollerClassic%20normal%20and%20Pro%20its%20same.jpg)

How test in Windows 10:
Run the app from menustart:
* joy.cpl

# References:

http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Classic_Controller


https://www.artekit.eu/stm32-usb-gamepad-interface/?fbclid=IwAR1iSHBsJSUVjJLKArsPc_yZ_MWaXWk79tJ8i753xQ9sc5e9BVFiAW36ljQ