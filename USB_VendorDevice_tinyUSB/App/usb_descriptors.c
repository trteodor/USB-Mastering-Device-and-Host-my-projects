

#include "tusb.h"
#include "main.h"
#include "usb_descriptors.h"

/* A combination of interfaces must have a unique product id, since PC will save device driver after the first plug.
 * Same VID/PID with different interface e.g MSC (first), then CDC (later) will possibly cause system error on PC.
 *
 * Auto ProductID layout's Bitmap:
 *   [MSB]         HID | MSC | CDC          [LSB]
 */
#define _PID_MAP(itf, n)  ( (CFG_TUD_##itf) << (n) )
#define USB_PID           (0x4000 | _PID_MAP(CDC, 0) | _PID_MAP(MSC, 1) | _PID_MAP(HID, 2) | \
                           _PID_MAP(MIDI, 3) | _PID_MAP(VENDOR, 4) )

#define USB_VID   0xCafe
#define USB_BCD   0x0200

//--------------------------------------------------------------------+
// Device Descriptors
//--------------------------------------------------------------------+
tusb_desc_device_t const desc_device =
{
  .bLength            = sizeof(tusb_desc_device_t),
  .bDescriptorType    = TUSB_DESC_DEVICE,
  .bcdUSB             = USB_BCD,

  // Use Interface Association Descriptor (IAD) for CDC
  // As required by USB Specs IAD's subclass must be common class (2) and protocol must be IAD (1)
  .bDeviceClass       = TUSB_CLASS_MISC,
  .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
  .bDeviceProtocol    = MISC_PROTOCOL_IAD,

  .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

  .idVendor           = USB_VID,
  .idProduct          = USB_PID,
  .bcdDevice          = 0x0100,

  .iManufacturer      = 0x01,
  .iProduct           = 0x02,
  .iSerialNumber      = 0x03,

  .bNumConfigurations = 0x01
};

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
uint8_t const * tud_descriptor_device_cb(void)
{
  return (uint8_t const *) &desc_device;
}

//--------------------------------------------------------------------+
// HID Report Descriptor
//--------------------------------------------------------------------+

#define HID_GAME_CNTR_REPORT_DESC_SIZE    74

__ALIGN_BEGIN static uint8_t HID_GAME_CNTR_ReportDesc[HID_GAME_CNTR_REPORT_DESC_SIZE]  __ALIGN_END =
{
	    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	    0x09, 0x05,                    // USAGE (Game Pad)
	    0xa1, 0x01,                    // COLLECTION (Application)
	    0x05, 0x02,                    //   USAGE_PAGE (Simulation Controls)
	    0x09, 0xbb,                    //   USAGE (Throttle)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x1f,                    //   LOGICAL_MAXIMUM (31)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0x05, 0x02,                    //   USAGE_PAGE (Simulation Controls)
	    0x09, 0xbb,                    //   USAGE (Throttle)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x1f,                    //   LOGICAL_MAXIMUM (31)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x95, 0x01,                    //   REPORT_COUNT (1)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0x05, 0x01,                    //   USAGE_PAGE (Generic Desktop)
	    0xa1, 0x00,                    //   COLLECTION (Physical)
	    0x09, 0x30,                    //   USAGE (X)
	    0x09, 0x31,                    //   USAGE (Y)
	    0x09, 0x32,                    //   USAGE (Z)
	    0x09, 0x33,                    //   USAGE (Rx)
	    0x15, 0x81,                    //   LOGICAL_MINIMUM (-127)
	    0x25, 0x7f,                    //   LOGICAL_MAXIMUM (127)
	    0x75, 0x08,                    //   REPORT_SIZE (8)
	    0x95, 0x04,                    //   REPORT_COUNT (4)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0x05, 0x09,                    //   USAGE_PAGE (Button)
	    0x19, 0x01,                    //   USAGE_MINIMUM (Button 1)
	    0x29, 0x10,                    //   USAGE_MAXIMUM (Button 16)
	    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
	    0x75, 0x01,                    //   REPORT_SIZE (1)
	    0x95, 0x10,                    //   REPORT_COUNT (16)
	    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	    0xc0,                          // END_COLLECTION
	    0xc0                           // END_COLLECTION
};

//uint8_t const desc_hid_report[] =
//{
//		HID_GAME_CNTR_ReportDesc
//};

// Invoked when received GET HID REPORT DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const * tud_hid_descriptor_report_cb(uint8_t instance)
{
  (void) instance;
  return HID_GAME_CNTR_ReportDesc;
}

//--------------------------------------------------------------------+
// Configuration Descriptor
//--------------------------------------------------------------------+

enum
{
  ITF_NUM_CDC = 0,
  ITF_NUM_CDC_DATA,
  ITF_NUM_HID,
  ITF_NUM_TOTAL
};

  #define EPNUM_CDC_NOTIF   0x81
  #define EPNUM_CDC_OUT     0x02
  #define EPNUM_CDC_IN      0x82
  #define EPNUM_HID   0x85

#define CONFIG_TOTAL_LEN    (TUD_CONFIG_DESC_LEN + TUD_CDC_DESC_LEN + TUD_HID_DESC_LEN)

// full speed configuration
uint8_t const desc_fs_configuration[] =
{
  // Config number, interface count, string index, total length, attribute, power in mA
  TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x00, 100),

  // Interface number, string index, EP notification address and size, EP data address (out, in) and size.
  TUD_CDC_DESCRIPTOR(ITF_NUM_CDC, 4, EPNUM_CDC_NOTIF, 8, EPNUM_CDC_OUT, EPNUM_CDC_IN, 64),

  // Interface number, string index, protocol, report descriptor len, EP In address, size & polling interval
  TUD_HID_DESCRIPTOR(ITF_NUM_HID, 5, HID_ITF_PROTOCOL_NONE, HID_GAME_CNTR_REPORT_DESC_SIZE, EPNUM_HID, CFG_TUD_HID_EP_BUFSIZE, 10)
};


// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
uint8_t const * tud_descriptor_configuration_cb(uint8_t index)
{
  (void) index; // for multiple configurations

  return desc_fs_configuration;
}

//--------------------------------------------------------------------+
// String Descriptors
//--------------------------------------------------------------------+

// array of pointer to string descriptors
char const* string_desc_arr [] =
{
  (const char[]) { 0x09, 0x04 }, // 0: is supported language is English (0x0409)
  "TinyUSB",                     // 1: Manufacturer
  "TinyUSB Device",              // 2: Product
  "123456789012",                // 3: Serials, should use chip ID
  "TinyUSB CDC",                 // 4: CDC Interface
  "TinyUSB MSC",                 // 5: MSC Interface
};

static uint16_t _desc_str[32];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
  (void) langid;

  uint8_t chr_count;

  if ( index == 0)
  {
    memcpy(&_desc_str[1], string_desc_arr[0], 2);
    chr_count = 1;
  }else
  {
    // Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
    // https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

    if ( !(index < sizeof(string_desc_arr)/sizeof(string_desc_arr[0])) ) return NULL;

    const char* str = string_desc_arr[index];

    // Cap at max char
    chr_count = (uint8_t) strlen(str);
    if ( chr_count > 31 ) chr_count = 31;

    // Convert ASCII string into UTF-16
    for(uint8_t i=0; i<chr_count; i++)
    {
      _desc_str[1+i] = str[i];
    }
  }

  // first byte is length (including header), second byte is string type
  _desc_str[0] = (TUSB_DESC_STRING << 8 ) | (2*chr_count + 2);

  return _desc_str;
}
