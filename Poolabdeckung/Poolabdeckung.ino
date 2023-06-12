// Definitionen der verwendeten Pins

#include <StateMachine.h>

const int STATE_DELAY = 1000; //ms
const int inClose = 13;
const int inOpen = 12;
const int inEndstopDaemmungOben = 11;
const int inEndstopKlappeGeschlossen = 10;
const int inEndstopKlappeOffen = 9;
const int inEndstopVerfahrenGeschlossen = 8;
const int inEndstopVerfahrenOffen = 7;
const int outDaemmungOeffnen = 6;
const int outDaemmungSchliessen = 5;
const int outKlappeOeffnen = 4;
const int outKlappeSchliessen = 3;
const int outVerfahrenOeffnen = 2;
const int outVerfahrenSchliessen = 1;

const int outOpen = 12;

StateMachine machine = StateMachine();

State* State_Uninitialisiert = machine.addState(&uninitialisiert);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void uninitialisiert()
{
  // Wird ausgeführt, wenn in diesem State ist
}