#ifndef XC_RFID_H
#define	XC_RFID_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>
#define RFID_TAG_LEN 12

void RFID_get( uint8_t* );
void RFID_new_byte( uint8_t );
bool RFID_new_scan( void );


#endif	/* XC_RFID_H */