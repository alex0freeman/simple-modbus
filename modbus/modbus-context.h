#ifndef __MODBUS_CONTEXT_H__
#define __MODBUS_CONTEXT_H__

#ifdef cplusplus
extern "C"
#endif//cplusplus

#include "rtu-debug.h"
#include "crc-modbus.h"
#include "rtu-define.h"
#include "make-request.h"
#include "make-response.h"
#include "check-request.h"
#include "check-response.h"


typedef enum
{
	error_check_ok = 3,
	error_recv_ok = 2,
	error_send_ok = 1,
	error_none_ok = 0,
	error_context_null = -1,
	error_frame_null = -2,
	error_send_null = -3,
	error_recv_null = -4,
	error_succ_null = -5,
	error_fail_null = -6,
	error_time_null = -7,
	error_timeout_less = -8,
	error_check_failed = -9,
	error_send_failed = -10,
	error_recv_timeout = -11,
}modbus_error_t;

/* **************************************************
 * timeout: millisecond, never less then 20			*
 * send: send method								*
 * recv: receive method								*
 * succ: callback if recv success					*
 * fail: callback if send failed or recv timeout    *
 * *************************************************/
typedef struct
{
	int fd;
	int timeout;
	int (*mstime)(void);
	int (*msleep)(unsigned int);
	int (*send)(int, char*, int);
	int (*recv)(int, char*, int);
	int (*success)(rtu_frame_t*, modbus_error_t);
	int (*failed)(rtu_frame_t*, modbus_error_t);
}modbus_context_t;

int modbus_context_init(modbus_context_t*);
int modbus_request(modbus_context_t*, rtu_frame_t*);
int modbus_response(modbus_context_t*, rtu_frame_t*);

#endif//__MODBUS_H__
