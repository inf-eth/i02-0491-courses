#include <PacketManip.h>
#include <cstdlib>			// exit()
#include <ctime>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

void packet_capture_callback(u_char *, const struct pcap_pkthdr*, const u_char*);

CPacketManip::CPacketManip (const char *pdev, const char *pfilter)
{
	// ask pcap for the network address and mask of the device
	if (pcap_lookupnet (pdev, &netp, &maskp, errbuf) == -1)
	{
		cerr << "ERROR pcap_lookupnet(): " << errbuf << endl;
		exit(-1);
	}

	// open device for reading this time lets set it in promiscuous mode so we can monitor traffic to another machine
	descr = pcap_open_live (pdev, BUFSIZ, 1, -1, errbuf);
	if(descr == NULL)
	{
		cerr << "ERROR pcap_open_live(): " << errbuf << endl;
		exit(-1);
	}

	// Lets try and compile the program.. non-optimized
	if (pcap_compile (descr, &fp, pfilter, 0, netp) == -1)
	{
		cerr << "ERROR calling pcap_compile()" << endl;
		exit(-1);
	}

	// set the compiled program as the filter
	if (pcap_setfilter (descr, &fp) == -1)
	{
		cerr << "ERROR setting filter" << endl;
		exit(1);
	}
	cout << "Device: " << pdev << endl;
	cout << "Filter: " << pfilter << endl;
}

void CPacketManip::Loop ()
{
	pcap_loop (descr, -1, packet_capture_callback, NULL);
}

// All the work needs to be done here.
void packet_capture_callback(u_char *useless,const struct pcap_pkthdr* header,const u_char* packet)
{
	cout << " Recieved a packet at: " << ctime((const time_t*)&header->ts.tv_sec) << endl;
}