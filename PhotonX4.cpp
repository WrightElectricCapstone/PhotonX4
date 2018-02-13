#include "ParticleLink/PhotonLink.h"
#include <Particle.h>
#include "ParticleLink/mavlink/mavlink.h"
#include "ParticleLink/mavlink/mavlink_types.h"



#define UDP_PORT 14550
#define BAUD_RATE 57600

PhotonLink CommLink;

UDP Udp;
String Local;
IPAddress Remote;


mavlink_message_t NetworkMessage;
mavlink_status_t NetworkStatus;
mavlink_message_t SerialMessage;
mavlink_status_t SerialStatus;
uint8_t NetworkBuff[MAVLINK_MAX_PACKET_LEN];
uint8_t SerialBuff[MAVLINK_MAX_PACKET_LEN];

void setup()
{
	CommLink.StartSerial(BAUD_RATE);
	CommLink.StartNetwork(&Udp, UDP_PORT);
	Serial.begin(115200);
	Particle.variable("IP",Local);
	IPAddress myIP = WiFi.localIP();
  	String ipStr = String(myIP[0])+"."+String(myIP[1])+"."+String(myIP[2])+"."+String(myIP[3]);
  	Local = ipStr;
}

void loop()
{
	int NetworkBytes = CommLink.CheckForNetworkMessage(&Udp, &Remote, &NetworkMessage, &NetworkStatus, NetworkBuff);
	if(NetworkBytes > 0)
	{
		//Serial.write(NetworkBuff,NetworkBytes);
		CommLink.SendMessageOnSerial(NetworkBuff, NetworkBytes);
	}

	int SerialBytes = CommLink.CheckForSerialMessage(&SerialMessage, &SerialStatus, SerialBuff);

	if(SerialBytes > 0)
	{
		CommLink.SendMessageOnNetwork(&Udp, Remote, UDP_PORT, SerialBuff, SerialBytes);
	}


}



