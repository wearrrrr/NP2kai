#ifndef	NP2_X_CMSERIAL_H__
#define	NP2_X_CMSERIAL_H__

#include <stdint.h>

// ---- com manager serial for unix

extern const uint32_t cmserial_speed[10];

COMMNG cmserial_create(uint32_t port, uint8_t param, uint32_t speed);

#if defined(SUPPORT_PC9861K)
#define	MAX_SERIAL_PORT_NUM	3
#else
#define	MAX_SERIAL_PORT_NUM	1
#endif

#endif	/* NP2_X_CMSERIAL_H__ */
