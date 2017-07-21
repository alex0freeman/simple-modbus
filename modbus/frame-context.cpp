#include "make-request.h"
#include "check-request.h"
#include "make-response.h"
#include "check-response.h"
#include "frame-context.h"

framecontext::framecontext(void)
{
	init_frame(&frame);
}
rtu_frame_t* framecontext::getframe(void)
{
	return &frame;
}
void framecontext::setframe(rtu_frame_t* framep)
{
	if( framep )
	{
		frame = *framep;
	}
}

void framecontext::init_requestA(void)
{
	init_request(&frame);
}

int framecontext::push_requestA(const char *data, int len)
{
	return push_request(&frame, data, len);
}

int framecontext::request_slave(void)
{
	return get_request_slave(&frame);
}

int framecontext::request_slave(int slave)
{
	return set_request_slave(&frame, slave);
}

int framecontext::request_funcode(void)
{
	return get_request_funcode(&frame);
}

int framecontext::request_funcode(int funcode)
{
	return set_request_funcode(&frame, funcode);
}


int framecontext::request_address(void)
{
	return get_request_address(&frame);
}

int framecontext::request_address(int address)
{
	return set_request_address(&frame, address);
}

int framecontext::request_count(void)
{
	return get_request_count(&frame);
}

int framecontext::request_count(int count)
{
	return set_request_count(&frame, count);
}

int framecontext::request_byte(void)
{
	return get_request_byte(&frame);
}

int framecontext::request_byte(int byte)
{
	return set_response_byte(&frame, byte);
}


int framecontext::request_value(int index)
{
	return get_request_value(&frame, index);
}

int framecontext::request_value(int index, int value)
{
	return set_request_value(&frame, index, value);
}

int framecontext::request_data(const char *data, int len)
{
	return set_request_data(&frame, data, len);
}


int framecontext::request_crc(void)
{
	return get_request_crc(&frame);
}

int framecontext::request_crc(int crc)
{
	return set_request_crc(&frame, crc);
}

const char* framecontext::get_request(void)
{
	return (const char*)frame.request.data;
}

int framecontext::request_length(void)
{
	return get_request_length(&frame);
}


/* response */
void framecontext::init_responseA(void)
{
	init_response(&frame);
}

int framecontext::push_responseA(const char *data, int len)
{
	return push_response(&frame, data, len);
}

const char* framecontext::get_response(void)
{
	return (const char*)frame.response.data;
}

const int framecontext::response_length(void)
{
	return get_response_length(&frame);
}

int framecontext::response_slave(void)
{
	return get_response_slave(&frame);
}

int framecontext::response_slave(int slave)
{
	return set_response_slave(&frame, slave);
}

int framecontext::response_funcode(void)
{
	return get_response_funcode(&frame);
}

int framecontext::response_funcode(int funcode)
{
	return set_response_funcode(&frame, funcode);
}


int framecontext::response_address(void)
{
	return get_response_address(&frame);
}

int framecontext::response_address(int address)
{
	return set_response_address(&frame, address);
}


int framecontext::response_count(void)
{
	return get_response_count(&frame);
}

int framecontext::response_count(int count)
{
	return set_response_count(&frame, count);
}


int framecontext::response_byte(void)
{
	return get_response_byte(&frame);
}

int framecontext::response_byte(int byte)
{
	return set_response_byte(&frame, byte);
}


int framecontext::response_value(int index)
{
	return get_response_value(&frame, index);
}

int framecontext::response_value(int index, int value)
{
	return set_response_value(&frame, index, value);
}

int framecontext::response_data(const char *data, int len)
{
	return set_response_data(&frame, data, len);
}


int framecontext::response_crc(void)
{
	return get_response_crc(&frame);
}

int framecontext::response_crc(int crc)
{
	return set_response_crc(&frame, crc);
}


int framecontext::succlen(void)
{
	return get_succlen(&frame);
}

int framecontext::excplen(void)
{
	return get_excplen(&frame);
}


int framecontext::exception_code(void)
{
	return get_exception_code(&frame);
}

int framecontext::exception_code(int code)
{
	return set_exception_code(&frame, code);
}

int framecontext::make_request_x01(int slave, int address, int count)
{
	return make_x01_request(&frame, 
			(unsigned char)slave, 
			(unsigned short)address, 
			(unsigned short)count);
}
int framecontext::make_request_x02(int slave, int address, int count)
{
	return make_x02_request(&frame, 
			(unsigned char)slave, 
			(unsigned short)address, 
			(unsigned short)count);
}
int framecontext::make_request_x03(int slave, int address, int count)
{
	return make_x03_request(&frame, 
			(unsigned char)slave, 
			(unsigned short)address, 
			(unsigned short)count);
}
int framecontext::make_request_x04(int slave, int address, int count)
{
	return make_x04_request(&frame, 
			(unsigned char)slave, 
			(unsigned short)address, 
			(unsigned short)count);
}
int framecontext::make_request_x05(int slave, int address, int value)
{
	return make_x05_request(&frame, 
			(unsigned char)slave, 
			(unsigned short)address, 
			(unsigned short)value);
}
int framecontext::make_request_x06(int slave, int address, int value)
{
	return make_x06_request(&frame, 
			(unsigned char)slave, 
			(unsigned short)address, 
			(unsigned short)value);
}
int framecontext::make_request_x0f(int slave, int address, int count, int len, char *data)
{
	return make_x0f_request(&frame, 
			(unsigned char)slave, 
			(unsigned short)address, 
			(unsigned short)count,
			(unsigned char)len,
			(unsigned char*)data);
}
int framecontext::make_request_x10(int slave, int address, int count, int len, char *data)
{
	return make_x10_request(&frame, 
			(unsigned char)slave, 
			(unsigned short)address, 
			(unsigned short)count,
			(unsigned char)len,
			(unsigned char*)data);
}

bool framecontext::check_request_frame(void)
{
	return check_request(&frame);
}

int framecontext::make_response_x01(int slave, char *data, int len)
{
	return make_x01_response(&frame,
			(unsigned char)slave,
			(unsigned char)len,
			(unsigned char*)data);
}
int framecontext::make_response_x02(int slave, char *data, int len)
{
	return make_x02_response(&frame,
			(unsigned char)slave,
			(unsigned char)len,
			(unsigned char*)data);
}
int framecontext::make_response_x03(int slave, char *data, int len)
{
	return make_x03_response(&frame,
			(unsigned char)slave,
			(unsigned char)len,
			(unsigned char*)data);
}
int framecontext::make_response_x04(int slave, char *data, int len)
{
	return make_x04_response(&frame,
			(unsigned char)slave,
			(unsigned char)len,
			(unsigned char*)data);
}
int framecontext::make_response_x05(int slave, int address, int value)
{
	return make_x05_response(&frame,
			(unsigned char)slave,
			(unsigned short)address,
			(unsigned short)value);
}
int framecontext::make_response_x06(int slave, int address, int value)
{
	return make_x06_response(&frame,
			(unsigned char)slave,
			(unsigned short)address,
			(unsigned short)value);
}
int framecontext::make_response_x0f(int slave, int address, int count)
{
	return make_x06_response(&frame,
			(unsigned char)slave,
			(unsigned short)address,
			(unsigned short)count);
}
int framecontext::make_response_x10(int slave, int address, int count)
{
	return make_x0f_response(&frame,
			(unsigned char)slave,
			(unsigned short)address,
			(unsigned short)count);
}
int framecontext::make_response_exception(int slave, int funcode, int code)
{
	return make_exception_response(&frame,
			(unsigned char)slave,
			(unsigned short)funcode,
			(unsigned short)code);
}

bool framecontext::check_response_frame(void)
{
	return check_response(&frame);
}

