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
//const int outOpen = 12;

SimpleFSM machine;

State State_Uninitialisiert;
State State_GestopptGeschlossen;
State State_GestopptP1;
State State_GestopptP2;
State State_GestopptP3;
State State_GestopptOffen;
State State_GestopptGeschlossen;

using Button = AblePullupCallbackButton; ///< Using clicker pull-up button.
using ButtonList = AblePullupCallbackButtonList; ///< Using clicker pull-up button list.

// Forward declaration of callback function.
void clickedCallback(Button::CALLBACK_EVENT, uint8_t);

Button btnInClose                      (inClose, clickedCallback); ///< The button to check.
Button btnInOpen                       (inOpen, clickedCallback); ///< The button to check.
Button btnInEndstopDaemmungOben        (inEndstopDaemmungOben, clickedCallback); ///< The button to check.
Button btnInEndstopKlappeGeschlossen   (inEndstopKlappeGeschlossen, clickedCallback); ///< The button to check.
Button btnInEndstopKlappeOffen         (inEndstopKlappeOffen, clickedCallback); ///< The button to check.
Button btnInEndstopVerfahrenGeschlossen(inEndstopVerfahrenGeschlossen, clickedCallback); ///< The button to check.
Button btnInEndstopVerfahrenOffen      (inEndstopVerfahrenOffen, clickedCallback); ///< The button to check.
Button *btns[] = {
  &btnInClose,
  &btnInOpen,
  &btnInEndstopDaemmungOben,
  &btnInEndstopKlappeGeschlossen,
  &btnInEndstopKlappeOffen,
  &btnInEndstopVerfahrenGeschlossen,
  &btnInEndstopVerfahrenOffen
};
ButtonList btnList = ButtonList(btns);

enum triggers {
  anyInputSwitched = 1  
};

/**
 * Callback function for button released.
 * 
 * @param event The event that has occured.
 * @param id The identifier of the button generating the callback (ignored in this example).
 */
void clickedCallback(Button::CALLBACK_EVENT event, uint8_t id) {
  (void)id; // id is unused.

/*  if(event == Button::RELEASED_EVENT) {
    led = !led;
    digitalWrite(LED_BUILTIN, led);
  }
*/
  machine.trigger(anyInputSwitched);
}

void State_Uninitialisiert_Enter()
{
  DaemmungStop();
  KlappeStop();
  VerfahrenStop();
}

void State_Uninitialisiert_Exit()
{
  
}

bool guardUnintialisiert_GestopptGeschlossen()
{
  // Statuswechsel von Uninitialisiert zu GestopptGeschlossen NUR erlaubt, wenn keiner der beiden Eingängen für Verfahren gedrückt/geschlossen ist und die Abdeckung geschlossen ist
  return !InFahrbefehlAktiv() && PositionGeschlossen();
}

bool InFahrbefehlAktiv()
{
  return btnInClose.isPressed() || btnInOpen.isPressed();
}

bool PositionGeschlossen()
{
  return btnInEndstopVerfahrenGeschlossen.isPressed() && btnInEndstopKlappeGeschlossen.isPressed();
}

void State_GestopptGeschlossen_Enter()
{
  // Aktion, die ausgeführt wird, wenn zu diesem Status gewechselt wird.
  DaemmungStop();
  KlappeStop();
  VerfahrenStop();
}

void State_GestopptGeschlossen_Exit()
{
}

void DaemmungStop()
{
  digitalWrite(outDaemmungOeffnen, false);
  digitalWrite(outDaemmungSchliessen, false);
}

void DaemmungOeffnen()
{
  digitalWrite(outDaemmungOeffnen, true);
  digitalWrite(outDaemmungSchliessen, false);
}

void DaemmungSchliessen()
{
  digitalWrite(outDaemmungOeffnen, false);
  digitalWrite(outDaemmungSchliessen, true);
}

void KlappeStop()
{
  digitalWrite(outKlappeOeffnen, false);
  digitalWrite(outKlappeSchliessen, false);
}

void KlappeOeffnen()
{
  digitalWrite(outKlappeOeffnen, true);
  digitalWrite(outKlappeSchliessen, false);
}

void KlappeSchliessen()
{
  digitalWrite(outKlappeOeffnen, false);
  digitalWrite(outKlappeSchliessen, true);
}

void VerfahrenStop()
{
  digitalWrite(outVerfahrenOeffnen, false);
  digitalWrite(outVerfahrenSchliessen, false);
}

void VerfahrenOeffnen()
{
  digitalWrite(outVerfahrenOeffnen, true);
  digitalWrite(outVerfahrenSchliessen, false);
}

void VerfahrenSchliessen()
{
  digitalWrite(outVerfahrenOeffnen, false);
  digitalWrite(outVerfahrenSchliessen, true);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(outDaemmungOeffnen, OUTPUT);
  pinMode(outDaemmungSchliessen, OUTPUT);
  pinMode(outKlappeOeffnen, OUTPUT);
  pinMode(outKlappeSchliessen, OUTPUT);
  pinMode(outVerfahrenOeffnen, OUTPUT);
  pinMode(outDaemmungSchliessen, OUTPUT);

  btnList.begin(); // ButtonList calls begin() for each button in the list.

  State_Uninitialisiert = State("Uninitialisiert",State_Uninitialisiert_Enter,nullptr, State_Uninitialisiert_Exit);
  State_GestopptGeschlossen = State("GestopptGeschlossen",State_GestopptGeschlossen_Enter,nullptr, State_GestopptGeschlossen_Exit);

  machine = SimpleFSM();
  Transition Unintialisiert_GestopptGeschlossen = Transition(&State_Uninitialisiert, &State_GestopptGeschlossen,anyInputSwitched, NULL, "", guardUnintialisiert_GestopptGeschlossen);
  machine.add(&Unintialisiert_GestopptGeschlossen,1);
  Transition Unintialisiert_GestopptP1 = Transition(&State_Uninitialisiert, &State_GestopptP1,anyInputSwitched, NULL, "", guardUnintialisiert_GestopptP1);
  machine.add(&Unintialisiert_GestopptGeschlossen,1);

}

void loop() {
   // put your main code here, to run repeatedly:
  btnList.handle(); // ButtonList calls handle() for each button in the list.

  machine.setInitialState(&State_Uninitialisiert);
  machine.run();
}