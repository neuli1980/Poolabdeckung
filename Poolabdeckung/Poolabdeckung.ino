// Definitionen der verwendeten Pins

#include <SimpleFSM.h>
#include <AbleButtons.h>

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

SimpleFSM machine;

State State_Uninitialisiert;
State State_GestopptGeschlossen;

using Button = AblePullupClickerButton; ///< Using clicker pull-up button.
using ButtonList = AblePullupClickerButtonList; ///< Using clicker pull-up button list.

ButtonList btnList = ButtonList()
Button btn(BUTTON_PIN); ///< The button to check.

void State_Uninitialisiert_Enter()
{

}

void State_Uninitialisiert_Exit()
{
  
}

void State_GestopptGeschlossen_Enter()
{
}

void State_GestopptGeschlossen_Exit()
{
}

void setup() {
  // put your setup code here, to run once:
  State_Uninitialisiert = State("Uninitialisiert",State_Uninitialisiert_Enter,nullptr, State_Uninitialisiert_Exit);
  State_GestopptGeschlossen = State("GestopptGeschlossen",State_GestopptGeschlossen_Enter,nullptr, State_GestopptGeschlossen_Exit);
  machine = SimpleFSM();
  Transition Unintialisiert_GestopptGeschlossen = Transition(&State_Uninitialisiert, &State_GestopptGeschlossen,1);
  machine.add(&Unintialisiert_GestopptGeschlossen,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  machine.setInitialState(&State_Uninitialisiert);
  machine.run();
}