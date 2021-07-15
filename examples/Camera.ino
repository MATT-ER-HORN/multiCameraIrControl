/*******************************************

   multiCameraIrControl Library - Example
   Description:  A small example of the improved library based on Seastian Setz
   Author.....:  Brian Helterline
   Version....:  2.0
   Date.......:  07-Jul-2021
   Project....:  https://github.com/bhelterline/multiCameraIrControl
  /*******************************************/

#include <multiCameraIrControl.h>

#define TRIGGER_PIN	13


// uncomment the camera of choice
// NOTE:  Not all models have shotDelayed().  If they do not, nothing will happen

Canon camera(TRIGGER_PIN);
//Sony camera(TRIGGER_PIN);
//Nikon camera(TRIGGER_PIN);
//Pentax cameraam(TRIGGER_PIN);
//Olympus camera(TRIGGER_PIN9);
//Sony  camera(TRIGGER_PIN);
//Canon camera(TRIGGER_PIN);

void setup() {
  camera.begin();
}

void loop() {
  camera.shotNow();
  delay(5000);
  camera.shotDelayed();
  delay(5000);
}
