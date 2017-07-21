#ifndef __FRAME_CONTEXT_H__
#define __FRAME_CONTEXT_H__
#include "frame-access.h"

class framecontext
{
private:
	rtu_frame_t frame;

public:
	framecontext(void);

public:
	rtu_frame_t* getframe(void);
	void setframe(rtu_frame_t* framep);

public:/* request frame access */
	void init_requestA(void);
	int push_requestA(const char *data, int len);

	int request_slave(void);
	int request_slave(int slave);

	int request_funcode(void);
	int request_funcode(int funtion);

	int request_address(void);
	int request_address(int address);

	int request_count(void);
	int request_count(int count);

	int request_byte(void);
	int request_byte(int byte);

	int request_value(int index);
	int request_value(int index, int value);
	int request_data(const char *data, int len);

	int request_crc(void);
	int request_crc(int crc);
	int calc_request_crc(void);

	const char* get_request(void);
	int request_length(void);

public:/* response frame access */
	void init_responseA(void);
	int push_responseA(const char *data, int len);

	const char* get_response(void);
	const int response_length(void);

	int response_slave(void);
	int response_slave(int slave);

	int response_funcode(void);
	int response_funcode(int funtion);

	int response_address(void);
	int response_address(int address);

	int response_count(void);
	int response_count(int count);

	int response_byte(void);
	int response_byte(int byte);

	int response_value(int index);
	int response_value(int index, int value);
	int response_data(const char *data, int len);

	int response_crc(void);
	int response_crc(int crc);
	int calc_response_crc(void);

	int succlen(void);
	int excplen(void);

	int exception_code(void);
	int exception_code(int code);

public://make request frame
	int make_request_x01(int slave, int address, int count);
	int make_request_x02(int slave, int address, int count);
	int make_request_x03(int slave, int address, int count);
	int make_request_x04(int slave, int address, int count);
	int make_request_x05(int slave, int address, int value);
	int make_request_x06(int slave, int address, int value);
	int make_request_x0f(int slave, int address, int count, int len, char *data);
	int make_request_x10(int slave, int address, int count, int len, char *data);

public://check request frame
	bool check_request_frame(void);

public://make request frame
	int make_response_x01(int slave, char *data, int len);
	int make_response_x02(int slave, char *data, int len);
	int make_response_x03(int slave, char *data, int len);
	int make_response_x04(int slave, char *data, int len);
	int make_response_x05(int slave, int address, int value);
	int make_response_x06(int slave, int address, int value);
	int make_response_x0f(int slave, int address, int count);
	int make_response_x10(int slave, int address, int count);
	int make_response_exception(int slave, int address, int code);

public://check response frame
	bool check_response_frame(void);
};

#endif//__FRAME_CONTEXT_H__
