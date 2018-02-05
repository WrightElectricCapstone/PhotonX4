#ifndef ParticleLink_H
#define ParticleLink_H

#include "mavlink/mavlink_types.h"
#include "mavlink/mavlink.h"
#include <Particle.h>


//This is an abstract base class to use particle boards with Mavlink
//It must be extended for the specific board/network type

class ParticleLink{

public:

	/*
	**Constructor
	*/
	ParticleLink() {};

	/*
	**Destructor
	*/
	~ParticleLink() {};

	/*
	**Start serial port with specified baud rate
	*/
	int StartSerial(uint16_t BaudRate);

	/*
	**Connects to Wifi/or 3G etc... and starts UDP Connection
	**must be inherited for specific board type, since network types will be different
	*/
	 virtual bool StartNetwork(UDP* Udp, uint16_t UdpPort) = 0;


	/*
	**returns true if a whole mavlink message is available for reading from serial...passes message contents into Message
	**also packs message into send buffer
	**returns # of bytes copied into send buffer
	**false if otherwise
	*/
	int CheckForSerialMessage(mavlink_message_t* Message, mavlink_status_t* Status, uint8_t* SerialBuff);

	/*
	**Checks for message over UDP connection
	** if available packs message into Message and also send buffer
	*/
	int CheckForNetworkMessage(UDP* Udp, IPAddress* Remote, mavlink_message_t* Message, mavlink_status_t* Status, uint8_t* MessageBuff);


	/*
	**Sends Mavlink message packet buffer over UDP connection
	*/
	int SendMessageOnNetwork(UDP* Udp, IPAddress* Remote, uint16_t UdpPort, uint8_t* MessageBuff, uint16_t len);


	/*
	**Writes Mavlink Message buffer to serial port
	*/
	int SendMessageOnSerial(uint8_t* MessageBuff, uint16_t len);


	


	/*
	**Publishes MavLink message to particle cloud
	**returns true for success, false for fail
	**TODO
	*/
	bool PublishMessage(uint16_t Message) {return true;}




};
#endif
