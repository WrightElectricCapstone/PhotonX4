#include <ParticleLink.h>

class ElectronLink : public ParticleLink{

public:
	bool StartNetwork(UDP* Udp, uint16_t UdpPort)
	{
		Cellular.on();
		while(!Cellular.ready())
		{
			Cellular.connect();
		}
		Particle.connect();
		Udp->begin(UdpPort);
		Udp->flush();
		return 0;
	}
};