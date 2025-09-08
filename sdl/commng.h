#ifndef	NP2_COMMNG_H__
#define	NP2_COMMNG_H__

#include <stdint.h>
#include <stdbool.h>

// ---- com manager interface

enum {
	COMCREATE_SERIAL		= 0,
	COMCREATE_PC9861K1,
	COMCREATE_PC9861K2,
	COMCREATE_PRINTER,
	COMCREATE_MPU98II,
#if defined(SUPPORT_SMPU98)
	COMCREATE_SMPU98_A,
	COMCREATE_SMPU98_B,
#endif
	COMCREATE_NULL			= 0xffff,
};

enum {
	COMCONNECT_OFF			= 0,
	COMCONNECT_SERIAL,
	COMCONNECT_MIDI,
	COMCONNECT_PARALLEL
};

enum {
	COMMSG_MIDIRESET		= 0,
	COMMSG_SETFLAG,
	COMMSG_GETFLAG,
#if defined(VAEG_FIX)
	COMMSG_SETRSFLAG,
#endif
	COMMSG_CHANGESPEED,
	COMMSG_CHANGEMODE,
	COMMSG_SETCOMMAND,
	COMMSG_PURGE,
	COMMSG_GETERROR,
	COMMSG_CLRERROR,
	COMMSG_USER			    = 0x80,
};

struct _commng;
typedef struct _commng	_COMMNG;
typedef struct _commng	*COMMNG;

struct _commng {
	uint32_t connect;
	uint32_t (*read)(COMMNG self, uint8_t *data);
	uint32_t (*write)(COMMNG self, uint8_t data);
	uint32_t (*writeretry)(COMMNG self);
	void	(*beginblocktranster)(COMMNG self);					/*!< begin block transfer */
	void	(*endblocktranster)(COMMNG self);					/*!< end block transfer */
	uint32_t (*lastwritesuccess)(COMMNG self);
	uint8_t	(*getstat)(COMMNG self);
	int* 	(*msg)(COMMNG self, uint32_t msg, int *param);
	void	(*release)(COMMNG self);
	uint8_t lastdata;
	uint8_t lastdatafail;
	uint32_t lastdatatime;
};

typedef struct {
	uint32_t size;
	uint32_t sig;
	uint32_t ver;
	uint32_t param;
} _COMFLAG, *COMFLAG;


#ifdef __cplusplus
extern "C" {
#endif

COMMNG commng_create(uint32_t device, bool onReset);
void commng_destroy(COMMNG hdl);

#ifdef __cplusplus
}
#endif


// ----

enum {
	COMPORT_NONE			= 0,
	COMPORT_COM1,
	COMPORT_COM2,
	COMPORT_COM3,
	COMPORT_COM4,
	COMPORT_MIDI
};

enum {
	COMSIG_COM1			= 0x314d4f43,
	COMSIG_COM2			= 0x324d4f43,
	COMSIG_COM3			= 0x334d4f43,
	COMSIG_COM4			= 0x344d4f43,
	COMSIG_MIDI			= 0x4944494d
};

enum {
	COMMSG_MIMPIDEFFILE		= COMMSG_USER,
	COMMSG_MIMPIDEFEN
};

void commng_initialize(void);

#include "cmmidi.h"
#include "cmserial.h"
#include "cmpara.h"

#endif	/* NP2_COMMNG_H__ */
