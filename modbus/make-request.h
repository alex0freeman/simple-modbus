#ifndef __MAKE_REQUEST_H__
#define __MAKE_REQUEST_H__
#include "frame-access.h"

#ifdef cplusplus
extern "C"
#endif//cplusplus

//read coil
int make_x01_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count
);

//read descrete coil
int make_x02_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count
);

//read holding register 
int make_x03_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count
);

//read input register 
int make_x04_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count
);

//write one coil 
int make_x05_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short value
);

//write one register 
int make_x06_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short value
);

//write multiple coil 
int make_x0f_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count,
	unsigned char byte,
	unsigned char *data
);

//write multiple register
int make_x10_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count,
	unsigned char byte,
	unsigned char *data
);

#endif//__MAKE_REQUEST_H__
