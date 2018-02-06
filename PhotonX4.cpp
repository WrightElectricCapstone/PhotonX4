#include "ParticleLink/PhotonLink.h"
#include <Particle.h>
#include "ParticleLink/mavlink/mavlink.h"
#include "ParticleLink/mavlink/mavlink_types.h"


#define UDP_PORT 14550
#define BAUD_RATE 57600

PhotonLink CommLink;

UDP Udp;

IPAddress LocalAdd;

bool ConnectionActive = false;

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
	Serial.begin();
    Serial.println(WiFi.localIP());

    //Need to ensure that once connection is established, messages are ONLY accepted from the original ground control station
    //Otherwise system can be controlled by anyone
    while(!ConnectionActive)
    {
    	int NetworkBytes = CommLink.CheckForNetworkMessage(&Udp, &Remote, &NetworkMessage, &NetworkStatus, NetworkBuff);
		if(NetworkBytes > 0)
		{
			CommLink.SendMessageOnSerial(NetworkBuff, NetworkBytes);
		}
		ConnectionActive = true;
    }
}

void loop()
{
	
	IPAddress PacketSource;
	int NetworkBytes = CommLink.CheckForNetworkMessage(&Udp, &PacketSource, &NetworkMessage, &NetworkStatus, NetworkBuff);
	//Check if there is a packet available from a valid source
	if(NetworkBytes > 0 && PacketSource == Remote)
	{
		CommLink.SendMessageOnSerial(NetworkBuff, NetworkBytes);
	}

	int SerialBytes = CommLink.CheckForSerialMessage(&SerialMessage, &SerialStatus, SerialBuff);
	if(SerialBytes > 0)
	{
		CommLink.SendMessageOnNetwork(&Udp, Remote, UDP_PORT, SerialBuff, SerialBytes);
	}

	Particle.process();
}



