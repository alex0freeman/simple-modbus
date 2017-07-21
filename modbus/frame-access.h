#ifndef _FRAME_ACCESS_H__
#define _FRAME_ACCESS_H__
#include "rtu-define.h"

#ifdef cplusplus
extern "C"
#endif//cplusplus

#define SLAVE_INDEX			0
#define FUNCTION_INDEX		1
#define ADDRESS_INDEX0		2
#define ADDRESS_INDEX1		3
#define COUNT_INDEX0		4
#define COUNT_INDEX1		5
#define BYTES_INDEX			6

void init_frame(rtu_frame_t *m);
void show_request(rtu_frame_t *m);
void show_response(rtu_frame_t *m);

/* request frame access */

void init_request(rtu_frame_t *m);
int push_request(rtu_frame_t *m, const char *data, int len);

const char* get_request_sendpoint(rtu_frame_t *m);
const int get_request_sendlength(rtu_frame_t *m);

int get_request_slave(rtu_frame_t* m);
int set_request_slave(rtu_frame_t* m, int slave);

int get_request_funcode(rtu_frame_t* m);
int set_request_funcode(rtu_frame_t* m, int funtion);

int get_request_address(rtu_frame_t* m);
int set_request_address(rtu_frame_t* m, int address);

int get_request_count(rtu_frame_t* m);
int set_request_count(rtu_frame_t* m, int count);

int get_request_byte(rtu_frame_t* m);
int set_request_byte(rtu_frame_t* m, int byte);

int get_request_value(rtu_frame_t* m, int index);
int set_request_value(rtu_frame_t* m, int index, int value);
int set_request_data(rtu_frame_t* m, const char *data, int len);

int get_request_crc(rtu_frame_t* m);
int set_request_crc(rtu_frame_t* m, int crc);
int calc_request_crc(rtu_frame_t* m);

int get_request_length(rtu_frame_t* m);

/* response frame access */

void init_response(rtu_frame_t *m);
int push_response(rtu_frame_t *m, const char *data, int len);

const char* get_response_sendpoint(rtu_frame_t *m);
const int get_response_sendlength(rtu_frame_t *m);

int get_response_slave(rtu_frame_t* m);
int set_response_slave(rtu_frame_t* m, int slave);

int get_response_funcode(rtu_frame_t* m);
int set_response_funcode(rtu_frame_t* m, int funtion);

int get_response_address(rtu_frame_t* m);
int set_response_address(rtu_frame_t* m, int address);

int get_response_count(rtu_frame_t* m);
int set_response_count(rtu_frame_t* m, int count);

int get_response_byte(rtu_frame_t* m);
int set_response_byte(rtu_frame_t* m, int byte);

int get_response_value(rtu_frame_t* m, int index);
int set_response_value(rtu_frame_t* m, int index, int value);
int set_response_data(rtu_frame_t* m, const char *data, int len);

int get_response_crc(rtu_frame_t* m);
int set_response_crc(rtu_frame_t* m, int crc);
int calc_response_crc(rtu_frame_t* m);

int get_response_length(rtu_frame_t* m);
int get_succlen(rtu_frame_t* m);
int get_excplen(rtu_frame_t* m);

int get_exception_code(rtu_frame_t *m);
int set_exception_code(rtu_frame_t *m, int code);

#endif//__FRAME_ACCESS_H__
