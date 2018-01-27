#include <ESP8266WiFi.h> 
#include "WiFiManager.h"
#include <EEPROM.h>

class CSmartPlug{
  private:
    String m_strIPAddr;
    unsigned int m_nPort;
    String m_strLabel;
    
  protected:
    bool SendPacket(WiFiClient & currentClient,char & packetStart,unsigned int packetLen);
    
  public:
    CSmartPlug(String ipAddr,unsigned int port);
    ~CSmartPlug();
    String GetIPAddr(){return m_strIPAddr;};
    unsigned int GetPort(){return m_nPort;};
    String GetLabel(){return m_strLabel;};
    
    void SetIPAddr(String ipAddr){m_strIPAddr = ipAddr;};
    void SetPort(unsigned int port){m_nPort = port;};
    void SetLabel(String label){m_strLabel = m_strLabel;};
};

CSmartPlug::CSmartPlug(String ipAddr,unsigned int port){
    m_strIPAddr = ipAddr;
    m_nPort = port;
}

CSmartPlug::~CSmartPlug(){
}

bool CSmartPlug::SendPacket(WiFiClient & currentClient,char & packetStart, unsigned int packetLen){
  IPAddress addr;
  addr.fromString(m_strIPAddr);
  if(!currentClient.connect(addr,m_nPort))
    return false;

  currentClient.write(&packetStart,packetLen);

  currentClient.stop();

  return true;
}

