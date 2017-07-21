#ifndef __MAKE_RESPONSE_H__
#define __MAKE_RESPONSE_H__
#include "frame-access.h"

#ifdef cplusplus
extern "C"
#endif//cplusplus

/* make normal response */
int make_x01_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char byte,
	unsigned char *data
);

int make_x02_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char byte,
	unsigned char *data
);

int make_x03_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char byte,
	unsigned char *data
);

int make_x04_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char byte,
	unsigned char *data
);

int make_x05_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned short address,
	unsigned short value 
);

int make_x06_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned short address,
	unsigned short value 
);

int make_x0f_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned short address,
	unsigned short count 
);

int make_x10_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned short address,
	unsigned short count 
);

/* make excption response */

int make_x80_x01_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
);

int make_x80_x02_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
);

int make_x80_x03_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
);

int make_x80_x04_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
);

int make_x80_x05_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
);

int make_x80_x06_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
);

int make_x80_x0f_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
);

int make_x80_x10_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
);

int make_exception_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char funcode,
	unsigned char code
);

#endif//__MAKE_RESPONSE_H__
