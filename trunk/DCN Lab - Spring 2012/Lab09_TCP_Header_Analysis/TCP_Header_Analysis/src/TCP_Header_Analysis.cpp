#include <PacketManip.h>
#include <iostream>
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
	cout << "Automated Worm Fingerprinting." << endl;

	// Empty filter program will capture all packets on device.
	// set device as "lo" to capture packets on loopback interface.
	// filter program can be "dst localhost", "src localhost", "dst www.google.com" etc.
	CPacketManip PacketCapture ("eth0", "");

	PacketCapture.Loop ();
	return 0;
}