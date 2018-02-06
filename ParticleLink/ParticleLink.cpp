#include "ParticleLink.h"
#include "mavlink/mavlink_types.h"
#include "mavlink/mavlink.h"
#include <Particle.h>



int ParticleLink::StartSerial(uint16_t BaudRate)
{
	Serial1.begin(BaudRate);
	return 0;
}

int ParticleLink::CheckForSerialMessage(mavlink_message_t* Message, mavlink_status_t* Status, uint8_t* SerialBuff)
{
	while(Serial1.available())
	{
		char c = Serial1.read();
		if(mavlink_parse_char(MAVLINK_COMM_0,c,Message,Status))
		{
			int bytes = mavlink_msg_to_send_buffer(SerialBuff,Message);
			return bytes;
		}
	}
	
	return 0;
}

int ParticleLink::CheckForNetworkMessage(UDP* Udp, IPAddress* Remote, mavlink_message_t* Message, mavlink_status_t* Status, uint8_t* MessageBuff)
{
	
	Udp->parsePacket();

	if(Udp->available())
	{
		*Remote = Udp->remoteIP();
		while(Udp->available())
		{
			char c = Udp->read();
			if(mavlink_parse_char(MAVLINK_COMM_0,c,Message,Status))
			{
				uint16_t bytes = mavlink_msg_to_send_buffer(MessageBuff, Message);
				return bytes;
			}
		}
	}
	return 0;
}

int ParticleLink::SendMessageOnSerial(uint8_t* MessageBuff, uint16_t len)
{
	int BytesSent = Serial1.write(MessageBuff, len);

	return (BytesSent == len);
}

int ParticleLink::SendMessageOnNetwork(UDP* Udp, IPAddress Remote, uint16_t UdpPort, uint8_t* MessageBuff, uint16_t len)
{
	Udp->beginPacket(Remote, UdpPort);
	int BytesSent = Udp->write(MessageBuff, len);

	Udp->endPacket();

	return (BytesSent == len);
}
