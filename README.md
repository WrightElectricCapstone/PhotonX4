# PhotonX4

This project allows the use of a Particle Photon WiFi board as a telemetry radio for use with the MAVLink UAV communication protocol
It relies on both the Photon and Ground Control Station to be connected to the same WiFi network and for  UDP port 14550 to be open.
ParticleLink is a component library which facilitates the communication layer between the flight controller and the network.
This project has been tested for use with PX4, QGroundControl, and the Pixhawk 2.1 flight controller, however, there should be no reason why it wouldn't be usable with any MAVLink platform (i.e. Ardupilot).
(You may need to change the baud rate to suit your particular flight controller)

##Getting Started

Make sure your Photon is configured to use the same WiFi network as your Ground Control Station.
The first step is to flash the firmware to your Photon.  All necessary dependencies are included in the GitHub repo.
Next, the Serial1 connection on the Photon needs to be connected to the Telemetry port on your flight controller (It is a simple UART).
When you power on your flight controller the telem radio should automatically connect and start communicating.
The Local IP address of your Photon will be tracked as a cloud variable, use Tinker or another method to note this down.
On your Ground Control Station, establish a telemetry link over UDP port 14550 with the target host set to the Photons IP.
Click Connect and you should see a vehicle connection pop up!  If so, you're good to go!


##Next Steps for this Project
I would like to add support for the Electron as well, which is attractive for its go anywhere nature (allowing unlimited range).
This is challenging for a number of reasons, first because of shifting IP adresses on cellular networks, and second from a security standpoint (no hijackings!)
I think it will require setting up a static server at a fixed IP and having the plane and GCS communicate through this middle layer
I think it will also require some level of encryption and/or password system to keep things locked down. Watch this space!

