import os
#os.environ['PYUSB_DEBUG'] = 'debug' # uncomment for verbose pyusb output
import sys
import platform
import time

import usb.core
import usb.util
import usb.control
import usb.backend.libusb1

dev = None

if platform.system() == 'Windows':
    # required for Windows only
    # libusb DLLs from: https://sourcefore.net/projects/libusb/
    arch = platform.architecture()
    if arch[0] == '32bit':
        backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb/x86/libusb-1.0.dll") # 32-bit DLL, select the appropriate one based on your Python installation
    elif arch[0] == '64bit':
        backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb/x64/libusb-1.0.dll") # 64-bit DLL

#     # device = usb.core.find(backend=backend, idVendor=VENDOR_ID, idProduct=PRODUCT_ID)


dev = usb.core.find(idVendor=0xCAFE, idProduct=0x4011)


# for cfg in dev:
#     print("cfg: " + (hex(cfg.bConfigurationValue) ) )

#     for intf in cfg:
#         print("intf: " + hex(intf.bInterfaceNumber) + " AltSett: " + hex(intf.bAlternateSetting) )

#         for ep in intf:
#             print("ep:" + hex(ep.bEndpointAddress) )

cfg = dev.get_active_configuration()
intf = cfg[2,0]
ep = usb.util.find_descriptor(
    intf,
    # match the first OUT endpoint
    custom_match = \
    lambda e: \
        usb.util.endpoint_direction(e.bEndpointAddress) == \
        usb.util.ENDPOINT_OUT)

# print(intf)
# print(cfg)
# print(ep)
# intf = cfg[(2,0)]

device_class = 0x21
feature = 0x22
action = 0x1
interface_nubmer = 0x02

dev.ctrl_transfer(device_class, feature, action, interface_nubmer,0) #only to active
ret = dev.read(0x83, 100, 100)
sret = ''.join([chr(x) for x in ret])
print(str(sret))

assert ep is not None
msg = 'test'

for i in range(20+1):
    print(str(i))
    ep.write(msg + str(i) + '\n')
    time.sleep(0.01) #only to see the proces
    ret = dev.read(0x83, 100, 100)
    sret = ''.join([chr(x) for x in ret])
    print(str(sret))


#this simple script is created only for test, i should create dedicated thread for read for example ;) 


usb.util.dispose_resources(dev)
