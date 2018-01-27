#include "TPLinkSmartPlug.h"
#define BUTTON_PIN 0

WiFiManager mainManager;
WiFiClient mainClient;

//define your smart plugs here
CTPLinkSmartPlug plugs[] = {CTPLinkSmartPlug("192.168.1.46",9999)};

bool nextState = false;
void setup(){
  Serial.begin(19200);
 // Serial.printf("On Packet Size: %u",(unsigned int)(sizeof(ON_PACKET)/sizeof(byte)));
  pinMode(BUTTON_PIN,INPUT);
	if(!mainManager.autoConnect())
		mainManager.startConfigPortal();
  delay(5000);
}


void loop(){
  bool pinValue = !digitalRead(BUTTON_PIN);   

  //only toggle plug states if the button is pressed
  if(!pinValue)
    return;
    
  for(int i = 0; i < sizeof(plugs)/sizeof(CTPLinkSmartPlug);i++){
      plugs[i].SendNextState(mainClient);
  }

  //delay to prevent overswitching of plugs
  delay(1000);
}
