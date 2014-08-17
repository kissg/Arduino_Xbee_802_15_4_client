/**
 *  Copyright (c) 2014 Gabor Kiss. All rights reserved.
 *  gabor.kiss@gmx.com
 *  kiss.gabor@it.unideb.hu
 * Based on: https://code.google.com/p/xbee-arduino/source/browse/examples/Series1_Rx/Series1_Rx.pde
 * https://code.google.com/p/xbee-arduino/source/browse/examples/Series1_Tx/Series1_Tx.pde
 */

#include <XBee.h>

/*
Lépések:
- XBee tulajdonságok beállítása
  - Csatorna tulajdonságok
  - Célcím beállítása
- Csatlakozás a hálózathoz
- Szinkronizálás
  - Idő
- Adat küldése
  - Csomag típusa
  - Érték
  - Időbélyeg
  - Csomag azon
- Visszajelzés megvárása
  - ACK csomag azon
  - Fontos ? Y -> újrapróbál x alkalommal : N -> időtúllépés
- Watchdog beállítása a következő felébresztéshez
- Lecsatlakozás
- Alvás
*/
/*
  A program az XBee library példa programjaira épül, amelyre a GNU GPL licence érvényes!
*/

#include <XBee.h>

#define BAUDRATE        115000
#define INDICATOR_LED       LED_BUILTIN
#define STANDARD_INFO_LED   LED_BUILTIN
#define ERROR_LED           LED_BUILTIN

// Jelzések - LED villogások száma
#define SETUP_ERROR     50
#define SETUP_SUCCESS   10

// Destination High, Destination Low address
#define DST_SH       
#define DST_SL      

XBee xbee               = XBee();
XBeeResponse response   = XBeeResponse();
Rx16Response rx16       = Rx16Response();

Rx64Response rx64       = Rx64Response();

//uint8_t    option    = 0;
//uint8_t    data      = 0;
uint8_t payload[] = { 0, 0 };

// 64-bit addressing: This is the SH + SL address of remote XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x40a97e16);
Tx64Request tx = Tx64Request(addr64, payload, sizeof(payload));

TxStatusResponse txStatus = TxStatusResponse();



void setup() 
{ 
  Serial.begin( BAUDRATE );
  xbee.begin( Serial );
  pinMode( INDICATOR_LED , OUTPUT );
  /* 
    // Ha különböznek az INDICATOR LED értékétől
    pinMode( STANDARD_INFO_LED , OUTPUT );
    pinMode( ERROR_LED         , OUTPUT );
  */
  delay(2000);
  standardIndicator( SETUP_SUCCESS );
}

void loop() {
  
}

/* Fel és le kapcsolja az INDICATOR_LED-et times alkalommal és sleeptime időközzel. 
      ledPin      A kimeneti LED azonosítója
      times       Fel-le kapcsolások száma
      sleeptime   Alvás a két kapcsolás között tizedmásodpercben
*/
void blinking( uint8_t *ledPin, uint8_t *times, uint8_t *sleeptime )
{
   // LED lekapcsolása a kezdéshez
   digitalWrite( *ledPin, LOW );
   
    for( uint8_t i = 0; i < *times; i++ )
    {
      digitalWrite( *ledPin, HIGH );
      delay( *sleeptime * 100 );
      digitalWrite( *ledPin, LOW );
      delay( *sleeptime * 100 );
    }  // END for
}

/**/
void errorIndicator( uint8_t times )
{
  uint8_t     sleeptime  = 1;                 // Alvás tizedmásodpercben 
  uint8_t     errorLed   = ERROR_LED;         // A led azonosítója
  blinking( &errorLed, &times, &sleeptime );
}

/**/
void standardIndicator( uint8_t times )
{
  uint8_t     sleeptime  = 1;                 // Alvás tizedmásodpercben 
  uint8_t     errorLed   = STANDARD_INFO_LED;         // A led azonosítója
  blinking( &errorLed, &times, &sleeptime );
}
