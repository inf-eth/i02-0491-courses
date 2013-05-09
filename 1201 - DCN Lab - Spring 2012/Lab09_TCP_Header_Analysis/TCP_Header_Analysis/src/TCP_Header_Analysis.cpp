#include <PacketManip.h>
#include <iostream>
using std::cout;
using std::endl;

int main (int argc, char **argv)
{
	cout << "TCP Header Analysis v1.00." << endl;

	// Empty filter program will capture all packets on device.
	// set device as "lo" to capture packets on loopback interface.
	// filter program can be "dst localhost", "src localhost", "dst www.google.com" etc.
	// Empty string "" captures all packets.
	// TODO: Is this running on localhost or on network? Use loopback for localhost (single PC) and eth0 for network.
	//CPacketManip PacketCapture ("eth0", "");
	CPacketManip PacketCapture ("lo", "");

	PacketCapture.Loop ();
	return 0;
}