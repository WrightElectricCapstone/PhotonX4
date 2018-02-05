#include "ParticleLink.h"



class PhotonLink : public ParticleLink{

public:
	bool StartNetwork(UDP* Udp, uint16_t UdpPort)
	{
		WiFi.on();
		while(!WiFi.ready())
		{
			WiFi.connect();
		}
		Particle.connect();
		Udp->begin(UdpPort);
		Udp->flush();
		return 0;
	}
};


