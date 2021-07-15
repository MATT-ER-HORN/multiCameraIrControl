/*******************************************
 *
 * Name.......:  cameraIrControl Library
 * Description:  A powerful Library to control easy various cameras via IR. Please check the project page and leave a comment.
 * Author.....:  Sebastian Setz
 * Version....:  1.9
 * Date.......:  2013-02-12
 * Project....:  http://sebastian.setz.name/arduino/my-libraries/multiCameraIrControl
 * Contact....:  http://Sebastian.Setz.name
 * License....:  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 *               To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
 *               Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 * Keywords...:  arduino, library, camera, ir, control, canon, nikon, olympus, minolta, sony, pentax, interval, timelapse
 * History....:  2010-12-08 V1.0 - release
 *               2010-12-09 V1.1 
 *               2010-12-16 V1.2
 *               2011-01-01 V1.3
 *               2011-01-04 V1.4 - making Sony function work, thank you Walter.
 *               2011-01-25 V1.5 - making Olympus work, thank you Steve Stav.
 *               2011-12-05 V1.6 - adding Olympus zoom, thank you again Steve! Refresh keywords.txt; Arduino 1.0 compatible
 *               2011-12-07 V1.7 - repairing Canon function - thanks to Viktor
 *               2013-02-11 V1.8 - adding toggleFocus for Pentax - thanks to Marcel Normann
 * 								   adding toggleVideo for Sony - thanks to InfinitR
 *               	    V1.9 - adding CanonWLDC100 support - thanks to ImaRH
 *
 ********************************************/
#include "multiCameraIrControl.h"

void Camera::wait(unsigned int time) {
  unsigned long start = micros();
  while (micros() - start <= time) {
  }
}

void Camera::high(unsigned int time) {
  int pause = (1000 / _freq / 2) - 4;
  unsigned long start = micros();
  while (micros() - start <= time) {
    digitalWrite(_pin, HIGH);
    delayMicroseconds(pause);
    digitalWrite(_pin, LOW);
    delayMicroseconds(pause);
  }
}

void Camera::begin()
{
  pinMode(_pin, OUTPUT);
}

void Camera::shotDelayed()
{
  // generic stub
}

void Camera::toggleFocus()
{
  // generic stub
}

void Camera::toggleVideo()
{
  // generic stub
}



// void Camera::zoomin()
// {
//   // generic stub
// }

// void Camera::zoomout()
// {
//   // generic stub
// }

void Nikon::shotNow()
{
  high(2000);
  wait(27830);
  high(390);
  wait(1580);
  high(410);
  wait(3580);
  high(400);
}

void Pentax::shotNow()
{
  high(13000);
  wait(3000);
  for (int i = 0; i < 7; i++) {
    high(1000);
    wait(1000);
  };
}

void Pentax::toggleFocus()
{
  high(13000);
  wait(3000);
  for (int i=0;i<5;i++){
    high(1000);
    wait(1000);
  };
  high(1000);
  wait(3000);
  high(1000);
}

void Olympus::shotNow()
{
  const byte seq[] = { 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 };
  const byte count = sizeof(seq) / sizeof(seq[0]);
  high(8972);
  wait(4384);
  high(624);
  for (int i = 0; i < count; i++) {
    if (seq[i]) {
      wait(1600);
      high(600);
    }
    else {
      wait(488);
      high(500);
    }
  }
}
// void Olympus::zoomin(unsigned int pct)
// {
//   const byte seq[] = {0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 };
//   const byte count = sizeof(seq) / sizeof(seq[0]);
//   high(9000);
//   wait(4500);
//   high(500);
//   for (int i = 0; i < count; i++) {
//     if (seq[i]) {
//       wait(1500);
//       high(500);
//     }
//     else{
//       wait(500);
//       high(500);
//     }
//   };
//   wait(40000);
//   if (pct>100) pct = 100;
//   pct = (pct*52)/100 + 1;
//   for (int i = 1; i < pct; i++)
//   {
//     high(9000);
//     wait(2000);
//     high(500);
//     wait(96000);
//   }

// }

// void Olympus::zoomout(unsigned int pct)
// {
//   const byte seq[] = {0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1  };
//   const byte count = sizeof(seq) / sizeof(seq[0]);
//   high(9000);           // 
//   wait(4500);
//   high(500);
//   for (int i = 0; i < count; i++) {
//     if (seq[i]) {
//       wait(1500);
//       high(500);
//     }
//     else{
//       wait(500);
//       high(500);
//     }
//   };
//   wait(40000);
//   if (pct>100) pct = 100;
//   pct = (pct*70)/100 + 1;
//   for (int i = 1; i < pct; i++)
//   {
//     high(9000);
//     wait(2000);
//     high(500);
//     wait(96000);
//   }
// }

void Minolta::shotNow()
{
  const byte seq[] = { 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 };
  const byte count = sizeof(seq) / sizeof(seq[0]);
  high(3750);
  wait(1890);
  for (int i = 0; i < count; i++) {
    if (seq[i]) {
      high(456);
      wait(1430);
    }
    else {
      high(456);
      wait(487);
    }
  }
}

void Minolta::shotDelayed()
{
  const byte seq[] = { 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
  const byte count = sizeof(seq) / sizeof(seq[0]);
  high(3750);
  wait(1890);
  for (int i = 0; i < count; i++) {
    if (seq[i]) {
      high(456);
      wait(1430);
    }
    else {
      high(456);
      wait(487);
    }
  }
}


void Sony::shotNow()
{
  const byte seq[] = { 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1 };
  const byte count = sizeof(seq) / sizeof(seq[0]);
  for (int j=0;j<3;j++) {
  high(2320);
  wait(650);
  for (int i = 0; i < count; i++) {
    if (seq[i]) {
      high(1175);
      wait(650);
    }
    else {
      high(575);
      wait(650);
    }
  }
  wait(10000);
}
}
void Sony::shotDelayed()
{
  const byte seq[] = { 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1 };
  const byte count = sizeof(seq) / sizeof(seq[0]);
  for (int j = 0; j < 3; j++) {
  high(2320);
  wait(650);
  for (int i = 0; i < count; i++) {
    if (seq[i]) {
      high(1175);
      wait(650);
    }
    else {
      high(575);
      wait(650);
    }
  }
  wait(10000);
 }
}

void Sony::toggleVideo()
{
  const byte seq[] = {  0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1 };
  const byte count = sizeof(seq) / sizeof(seq[0]);
  for (int j = 0; j < 3; j++) {
  high(2320);
  wait(650);
  for (int i = 0; i < count; i++) {
    if (seq[i]) {
      high(1175);
      wait(650);
    }
    else {
      high(575);
      wait(650);
    }
  }
  wait(10000);
 }
}

void Canon::shotNow()
{
 for(int i=0; i<16; i++) { 
    digitalWrite(_pin, HIGH);
    delayMicroseconds(11);
    digitalWrite(_pin,LOW);
    delayMicroseconds(11);
  } 
  delayMicroseconds(7330); 
  for(int i=0; i<16; i++) { 
    digitalWrite(_pin,HIGH);
    delayMicroseconds(11);
    digitalWrite(_pin,LOW);
    delayMicroseconds(11);
  }
}

void Canon::shotDelayed()
{
  for(int i=0; i<16; i++) { 
    digitalWrite(_pin, HIGH);
    delayMicroseconds(11);
    digitalWrite(_pin, LOW);
    delayMicroseconds(11);
  } 
  delayMicroseconds(5360); 
  for(int i=0; i<16; i++) { 
    digitalWrite(_pin, HIGH);
    delayMicroseconds(11);
    digitalWrite(_pin, LOW);
    delayMicroseconds(11);
  }
}

void CanonWLDC100::shotNow()
{
 const byte seq[] = {0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1};
 const byte count = sizeof(seq) / sizeof(seq[0]);
  high(9042);
  wait(4379);
 
  for (int i = 0; i < count; i++) {
    if (seq[i]) {
      high(612);
      wait(1621);
    }
    else{
      high(612);
      wait(512);
    }
  };
    high(599);
}

