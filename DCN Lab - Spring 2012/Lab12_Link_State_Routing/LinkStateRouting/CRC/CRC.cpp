// CRC Implementation file. CRC.cpp

#include "CRC.h"

// * CRC Table.
long crc32_table[ 256 ];
	

/* CRC function, initialized first time "crc32()" is called. */
unsigned long crc32( unsigned char *buf, int len )
{
    unsigned char *p;
    unsigned long crc;

	/* If not already done... */
    if( !crc32_table[ 1 ] )
	{
		/* Build table */
        init_crc32();   
	}
	
	/* Preload shift register, per CRC-32 spec */
    crc = 0xffffffff;       

    for( p = buf; len > 0; ++p, --len )
	{
        crc = ( crc << 8 ) ^ crc32_table[ ( crc >> 24 ) ^ *p ];
	}

	/* Transmit complement, per CRC-32 spec */
	
	return ~crc;
	
}

/* Initializing the CRC calculator polynomial */
void init_crc32( void )
{
    int i, j;
    unsigned long c;

    for( i = 0; i < 256; ++i )
	{
        for( c = i << 24, j = 8; j > 0; --j )
		{
            c = c & 0x80000000 ? ( c << 1 ) ^ CRC32_POLY : ( c << 1 );
		}

        crc32_table[ i ] = c;
    }
	
}

