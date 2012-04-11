#include <PacketHeaders.h>
#include <pcap.h>

// Packet capturing and manipulation class.
class CPacketManip
{
private:
	char *dev;
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t* descr;
	const u_char *packet;
	struct pcap_pkthdr hdr;     /* pcap.h                    */
	struct ether_header *eptr;  /* net/ethernet.h            */
	struct bpf_program fp;      /* hold compiled program     */
	bpf_u_int32 maskp;          /* subnet mask               */
	bpf_u_int32 netp;           /* ip                        */
public:
	CPacketManip (const char *, const char *);		// takes device name and filter program as arguments.
	void Loop ();
};