/**********************************************************************
* Project           : Smarthome control
*
* Author            : Bastian Krammer
*
* Date created      : 14_02_2019
*
* Purpose           : library to control my music system
*
**********************************************************************/

#include <IRremote.h>

#include "music_system.h"

#define MAX_IR_LENGTH 67

const unsigned int tonoff []PROGMEM = {8800, 4400, 500, 550, 550, 550, 500, 600, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 600, 500, 1650, 500, 600, 500, 1700, 500, 1650, 500, 1700, 500, 600, 500, 550, 550, 1650, 500, 600, 500, 600, 500, 550, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 550, 1650, 500, 1700, 500, 1650, 500, 1700, 500, 1650, 550, 1650, 500, 1700, 500, 1650, 550};
const unsigned int tstumm []PROGMEM = {8750, 4400, 550, 550, 550, 550, 500, 600, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 600, 500, 1650, 550, 550, 500, 1650, 550, 1650, 500, 1700, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 550, 550, 550, 550, 550, 500, 600, 500, 550, 550, 550, 550, 550, 500, 550, 550, 1700, 500, 1650, 500, 1650, 550, 1650, 550, 1650, 500, 1650, 550, 1650, 550};
const unsigned int tsourceh[]PROGMEM = {8850, 4350, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 500, 1700, 500, 600, 500, 1650, 550, 1650, 500, 1700, 500, 550, 500, 600, 500, 1700, 500, 1650, 550, 550, 500, 600, 500, 1700, 500, 1650, 500, 600, 500, 600, 500, 600, 500, 550, 550, 1650, 500, 1700, 500, 550, 550, 550, 500, 1700, 500, 1650, 500, 1700, 500};
const unsigned int tsourcer[]PROGMEM = {8850, 4350, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 550, 1650, 500, 600, 500, 1650, 550, 1650, 500, 1650, 550, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 500, 1700, 500, 1650, 550, 1650, 500, 600, 500, 550, 550, 550, 550, 550, 500, 1700, 500, 550, 550, 550, 500, 600, 500, 1700, 500, 1650, 500, 1700, 500};
const unsigned int tlauter[]PROGMEM = {8800, 4400, 550, 550, 500, 600, 500, 600, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 550, 500, 1700, 500, 600, 500, 1650, 500, 1700, 500, 1650, 550, 550, 500, 600, 500, 1700, 500, 550, 550, 550, 500, 1700, 500, 1650, 550, 1650, 500, 600, 500, 550, 550, 550, 550, 1650, 500, 1700, 500, 550, 550, 550, 500, 600, 500, 1650, 550, 1650, 500, 1700, 500};
const unsigned int tleiser[]PROGMEM = {8800, 4400, 500, 600, 500, 600, 500, 550, 500, 650, 450, 600, 500, 1650, 550, 1650, 500, 600, 500, 1650, 550, 550, 550, 1650, 500, 1650, 550, 1650, 500, 600, 500, 600, 500, 1650, 550, 550, 500, 1700, 500, 550, 550, 1650, 500, 1700, 500, 600, 500, 600, 450, 600, 500, 1700, 500, 550, 550, 1650, 500, 600, 500, 600, 500, 1650, 500, 1700, 500, 1650, 550};

//Global variables
int counter   = 0;
int counter2  = 0;
int dvd       = 1;
int tape      = 0;
int aux       = 0;
int senden[MAX_IR_LENGTH];
int al        = 50;
int td        = 100;

IRsend irsend = IRsend();


void music_system::turnMusicsystemOn(void) {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tonoff + counter);
  }
  irsend.sendRaw((const unsigned int*)senden, sizeof(senden) / sizeof(int), 40);

  delay(1000);
  counter = 10;

  while (counter > 0) {
    irsend.sendRaw((const unsigned int*)senden, sizeof(senden) / sizeof(int), 40);
    counter--;
  }
}

void music_system::turnMusicsystemOff(void) {
  setSourceDVD();
  delay(500);
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tonoff + counter);
  }

  counter = 5;
  while (counter > 0) {
    irsend.sendRaw((const unsigned int*)senden, sizeof(senden) / sizeof(int), 40);
    counter--;
  }
}

void music_system::sourceOneUp(void) {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tsourceh + counter);
  }

  for (counter = 3; counter > 0; counter--) {
    irsend.sendRaw((const unsigned int*)senden, sizeof(senden) / sizeof(int), 40);
    counter--;
  }
}

void music_system::sourceOneDown() {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tsourcer + counter);
  }

  for (counter = 3; counter > 0; counter--) {
    irsend.sendRaw((const unsigned int*)senden, sizeof(senden) / sizeof(int), 40);
    counter--;
  }
}

void music_system::setSourceDVD(void) {
  if (tape == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      sourceOneUp();
      delay(500);
    }
    tape = 0;
  }

  if (aux == 1) {
    for (counter2 = 2; counter2 > 0; counter2--) {
      sourceOneUp();
      delay(500);
    }
    aux = 0;
  }

  dvd = 1;
}

void music_system::setSourceTape(void) {
  if (dvd == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      sourceOneDown();
      delay(500);
    }
    dvd = 0;
  }

  if (aux == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      sourceOneUp();
      delay(500);
    }
    aux = 0;
  }

  tape = 1;
}

void music_system::setSourceAux(void) {
  if (tape == 1) {
    for (counter2 = 1; counter2 > 0; counter2--) {
      sourceOneDown();
      delay(500);
    }
    tape = 0;
  }

  if (dvd == 1) {
    for (counter2 = 2; counter2 > 0; counter2--) {
      sourceOneDown();
      delay(500);
    }
    dvd = 0;
  }

  aux = 1;
}

void music_system::volumeOneUp(void) {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tlauter + counter);
  }

  //   for(counter=3;counter>0;counter--){
  irsend.sendRaw((const unsigned int*)senden, sizeof(senden) / sizeof(int), 40);
  //        counter--;
  //   }
}

void music_system::volumeOneDown(void) {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tleiser + counter);
  }

  //   for(counter=3;counter>0;counter--){
  irsend.sendRaw((const unsigned int*)senden, sizeof(senden) / sizeof(int), 40);
  //        counter--;
  //   }
}

void music_system::setVolumeMute(void) {
  for (counter = 0; counter < MAX_IR_LENGTH; counter++) {
    senden[counter] = pgm_read_word_near(tstumm + counter);
  }
  irsend.sendRaw((const unsigned int*)senden, 10, 10);
}

void music_system::setVolume(int value){
  counter2 = al - value;
  al = value;
  if(counter2 > 0){
    while(counter2 > 0){
      volumeOneUp();
      delay(td);
      counter2--;
    }
  }
  if (counter2 < 0){
    while(counter2 < 0){
      volumeOneDown();
      delay(td);
      counter2++;
    }
  }
}

void music_system::volumePlusFive(void){
  for(int i=0; i<5; i++){
    volumeOneUp();
    delay(td);
  }
  al+=5;
}

void music_system::volumeMinusFive(void){
  for(int i=0; i<5; i++){
    volumeOneDown();
    delay(td);
  }
  al-=5;
}