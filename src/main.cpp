/************************************************
 *  Includes
 ***********************************************/
#include <Arduino.h>
#include "HomeSpan.h"

/* Local files */
#include "homeKitAccessories/airConditioner.h"

#include "devices/daikin.h"
#include "devices/deviceInfo.h"

/* Private files */
#include "private/wifiCredentials.h"

/************************************************
 *  Defines / Macros
 ***********************************************/

/************************************************
 *  Typedef definition
 ***********************************************/

/************************************************
 *  Public function implementation
 ***********************************************/
void setup() {

    /* Used for debug */
    Serial.begin(115200);

#if defined(WIFI_SSID) && defined(WIFI_PASSWORD)
    /* Connect to the Internet */
    homeSpan.setWifiCredentials(WIFI_SSID, WIFI_PASSWORD);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
#endif

    /* Create the pairing code */
    homeSpan.setPairingCode("11100111");

    /* Create a Bridge to account for multiple devices (accessories) */
    homeSpan.begin(Category::AirConditioners, "ESP32 - Bridge");

    new SpanAccessory();
        new Service::AccessoryInformation();
            new Characteristic::Identify();

    /* Living Room AC */
    new SpanAccessory();
        new Service::AccessoryInformation();
            new Characteristic::Name(DAIKIN_AC_NAME);
            new Characteristic::Manufacturer(DAIKIN_AC_MANUFACTURER);
            new Characteristic::Model(DAIKIN_AC_MODEL);
            new Characteristic::SerialNumber(DAIKIN_AC_SERIAL_NUM);
            new Characteristic::FirmwareRevision(DAIKIN_AC_FIRMWARE);
            new Characteristic::Identify();
        new HS_AirConditioner();

}

void loop() {
    homeSpan.poll();
}
