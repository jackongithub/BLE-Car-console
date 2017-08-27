#include <Arduino.h>
#include <SPI.h>
#if not defined (_VARIANT_ARDUINO_DUE_X_) && not defined(ARDUINO_ARCH_SAMD)
  #include <SoftwareSerial.h>
#endif

#include <Keypad.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

#define FACTORYRESET_ENABLE         0
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"

//pinout of bt module
//BLUEFRUIT_SWUART_RXD_PIN 9
//BLUEFRUIT_SWUART_TXD_PIN 10
//BLUEFRUIT_UART_CTS_PIN 11
//BLUEFRUIT_UART_MODE_PIN 12

//pinout of keypad
//arduino pin - color of wire
//pin2 - brown
//pin3 - purple
//pin4 - green
//pin5 - orange
//pin6 - yellow
//pin7 - blue
//pin8 - red


//Key defines
char key1[] = "AT+BLEHIDCONTROLKEY=0xB8"; //Bring up onscreen keyboard.Eject key
char key2[] = "AT+BLEKEYBOARDCODE=08-00-1E"; //Map Standard view.Command + 1
char key3[] = "AT+BLEKEYBOARDCODE=08-00-1F"; //Map Satellite view.Command + 2
char key4[] = "AT+BLEHIDCONTROLKEY=PLAYPAUSE"; //Play,Pause.Play/pause (media keys)
char key5[] = "AT+BLEHIDCONTROLKEY=HOME"; //App switcher. have to run twice!!!
char key6[] = "AT+BLEHIDCONTROLKEY=HOME,500"; //Siri.
char key7[] = "AT+BLEHIDCONTROLKEY=BRIGHTNESS+"; //Brightness up. Brightness up (Mac keyboard)
char key8[] = "AT+BLEHIDCONTROLKEY=BRIGHTNESS-"; //Brightness down. Brightness down (Mac keyboard)
char key9[] = "AT+BLEHIDCONTROLKEY=MEDIAPREVIOUS"; //Prev song. Prev song (media keys)
char key10[] = "AT+BLEHIDCONTROLKEY=MEDIANEXT"; //Next song. Next song (media keys)
char key11[] = "AT+BLEHIDCONTROLKEY=HOME"; //iOS Home button. ALT command. AT+BLEKEYBOARDCODE=08-00-0B Command + H

//init software serial
SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);
Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN, BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

//Matrix keypad setup
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
//define the buttons of the keypad
char hexaKeys[ROWS][COLS] = {
  {'A','B','C'},
  {'D','1','2'},
  {'3','4','5'},
  {'6','7','8'}
};
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {8, 7, 6};

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}

void setup(void)
{
  while (!Serial);
  delay(500);

  Serial.begin(115200);
  Serial.println(F("Setup init"));
  
  //Init module
  Serial.print(F("Init Bluefruit: "));
  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  if ( FACTORYRESET_ENABLE )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    Serial.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  /* Set bluetooth name */
  Serial.println(F("Setting device name to 'Car Keyboard': "));
  if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Car Keyboard" )) ) {
    error(F("Could not set device name?"));
  }

  /* Enable HID Service */
  Serial.println(F("Enable HID Service (including Keyboard): "));
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
    if ( !ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))) {
      error(F("Could not enable Keyboard"));
    }
  }else
  {
    if (! ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ))) {
      error(F("Could not enable Keyboard"));
    }
  }

  /* Add or remove service requires a reset */
  Serial.println(F("Performing a SW reset (service changes require a reset): "));
  if (! ble.reset() ) {
    error(F("Couldn't reset??"));
  }
  Serial.println(F("Finish setup()"));
}

// Function to send commands to bt module
int sendcommandd(char J){
    //Serial.println(J);
  if (J == 'A'){
    ble.println(key9);
	delay(100);
    }
  else if (J == 'B'){
    ble.println(key11);
	delay(100);
    }
  else if (J == 'D'){
    ble.println(key3);
	ble.println("AT+BLEKEYBOARDCODE=00-00");
	delay(100);
	}
  else if (J == '1'){
    ble.println(key5);
    ble.println(key5);
	delay(100);
	}
  else if (J == '2'){
    ble.println(key6);
	delay(100);
	}
  else if (J == '3'){
    ble.println(key7);
	delay(100);
	}
  else if (J == '4'){
    ble.println(key8);
	delay(100);
    }
  else if (J == '5'){
    ble.println(key10);
	delay(100);
	}
  else if (J == '6'){
    ble.println(key4);
	delay(100);
	}
  else if (J == '7'){
    ble.println(key1);
	delay(100);
	}
  else if (J == '8'){
    ble.println(key2);
	ble.println("AT+BLEKEYBOARDCODE=00-00");
	delay(100);
	}
  else {
    Serial.println("Error sendcommandd(); unexpected key");
	delay(100);
  }
}

void loop(void){
//Check if any buttons were pressed
  char customKey = customKeypad.getKey();
  if (customKey){
    //Serial.println(customKey);
    sendcommandd(customKey);
  }
  delay(10);
}
