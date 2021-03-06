#include "SmartPlug.h"

char OFF_PACKET[46] = {0x00,0x00,0x00,0x00,0xd0,0xf2,0x81,0xf8,0x8b,0xff,0x9a,0xf7,0xd5,0xef,0x94,0xb6,0xc5,0xa0,0xd4,0x8b,0xf9,0x9c,0xf0,0x91,0xe8,0xb7,0xc4,0xb0,0xd1,0xa5,0xc0,0xe2,0xd8,0xa3,0x81,0xf2,0x86,0xe7,0x93,0xf6,0xd4,0xee,0xde,0xa3,0xde,0xa3};
char ON_PACKET[46] = {0x00,0x00,0x00,0x2a,0xd0,0xf2,0x81,0xf8,0x8b,0xff,0x9a,0xf7,0xd5,0xef,0x94,0xb6,0xc5,0xa0,0xd4,0x8b,0xf9,0x9c,0xf0,0x91,0xe8,0xb7,0xc4,0xb0,0xd1,0xa5,0xc0,0xe2,0xd8,0xa3,0x81,0xf2,0x86,0xe7,0x93,0xf6,0xd4,0xee,0xdf,0xa2,0xdf,0xa2};

void toggleBool(bool & t){
  t = !t;
}

class CTPLinkSmartPlug : public CSmartPlug{
  private:
    bool m_bNextState;
   
  public:
    void SetNextState(bool nextState){m_bNextState = nextState;};
    bool GetNextState(){return m_bNextState;};
    //automatically toggles the next state bool. if you don't want to do this, use the overriden SendNextState with the untoggle param
    bool SendNextState(WiFiClient & currentClient);
    bool SendNextState(WiFiClient & currentClient,bool untoggle);
    CTPLinkSmartPlug(String ipAddr,unsigned int port) : CSmartPlug(ipAddr,port){};
    ~CTPLinkSmartPlug(){};
};

bool CTPLinkSmartPlug::SendNextState(WiFiClient & currentClient){
    bool result;
    if(m_bNextState)
      result = SendPacket(currentClient,ON_PACKET[0],sizeof(ON_PACKET));
    else
      result = SendPacket(currentClient,OFF_PACKET[0],sizeof(OFF_PACKET));
    //only toggle if the packet sent ok
    if(result)
      toggleBool(m_bNextState);
    return result;
}

bool CTPLinkSmartPlug::SendNextState(WiFiClient & currentClient, bool untoggle){
    bool res = SendNextState(currentClient);
    if(res && untoggle)
      toggleBool(m_bNextState);
    return res;
}
