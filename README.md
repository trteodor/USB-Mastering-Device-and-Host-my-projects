# USB-Mastering-Device-and-Host-my-projects

Hi!
In this repository i Mastering how to operate with USB Device And Host. I will probably prepare few example. 
Each folder on top of the repository consist one example.


1. Example - Composite device - HID and CDC Class (VCP and Game Controller) **using CubeMX Stack**

	*Folder name: **USB_HIDplusCDC_VCPandGameController**

Prepared example consist are from .
VCP - Working as echo
For game controller i planning use Device from this link: http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Classic_Controller

To Create this example i used USB Stack delivered by CubeMX. In my opinion this stack isn't friendly but it is only my opinion. I had to rebuild
a large part of the stack.(Maybe i don't have else sufficient experiance to easy operate with this stack) 
You can check changes before this commit: 
__*"VCP and GameController Is Detected correctly"*__ 
to see what exacly i did. To check te process how i run 
This example will be develop when i get the gamecontroller to my hands. But evrything should work now correctly.



# References:

https://wydawnictwo.btc.pl/elektronika/204656-usb-dla-niewtajemniczonych-w-przykladach-na-mikrokontrolery-stm32-e-book.html
https://www.usb.org/
https://anvilelectronics.ovh/tinyusb-na-stm32-device-cdc/
https://github.com/hathach/tinyusb?fbclid=IwAR2eV_u5AAk7GbArpe6f22GNZaFtwJsuoiuO3vi2VzL7FNbEQ0NLS_DfuY4
https://github.com/pyusb/pyusb/blob/master/docs/tutorial.rst
https://www.elektroda.pl/rtvforum/topic3310418.html
https://github.com/x893/STM32F103-DualCDC
https://sudonull.com/post/68144-CDC-MSC-USB-Composite-Device-on-STM32-HAL

The last only as Curiosity: 
https://github.com/alambe94/I-CUBE-USBD-Composite?fbclid=IwAR2vQEj_NNZ7KUWyuTjpTuLJg-uFVfsuOl11_1ine6B1eP6DTmZ_XS_4VLw