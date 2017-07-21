#include <stdio.h>
#include "rtu-debug.h"
#include "crc-modbus.h"
#include "frame-access.h"

void init_frame(rtu_frame_t *m)
{
	init_request(m);
	init_response(m);
}
void show_request(rtu_frame_t *m)
{
	if( m )
	{
		showhex(m->request.data, get_request_length(m));
	}
}
void show_response(rtu_frame_t *m)
{
	if( m )
	{
		showhex(m->response.data, get_response_length(m));
	}
}

/* request frame access */

void init_request(rtu_frame_t *m)
{
	if( m )
	{
		int i = 0;
		for(i = 0 ; i < sizeof(m->request); i++)
		{
			m->request.data[i] = 0;
		}
		m->reqidx = 0;
	}
}
int push_request(rtu_frame_t *m, const char *data, int len)
{
	int i = 0 ;

	if( NULL == m || NULL == data || len < 1 )
	{
		return -1;
	}
	for(i = 0; i < len; i++)
	{
		if( m->reqidx >= sizeof(m->request) )
		{
			return i;
		}
		m->request.data[m->reqidx++] = data[i];
	}
	return len;
}
int get_request_slave(rtu_frame_t* m)
{
	if( m )
	{
		return 0xff & m->request.data[SLAVE_INDEX];
	}
	return 0;
}
int set_request_slave(rtu_frame_t* m, int slave)
{
	if( m )
	{
		m->request.data[SLAVE_INDEX] = (slave & 0xff);
	}
	return Error_Ok;
}

int get_request_funcode(rtu_frame_t* m)
{
	if( m )
	{
		return 0xff & m->request.data[FUNCTION_INDEX];
	}
	return -1;
}
int set_request_funcode(rtu_frame_t* m, int funtion)
{
	if( m )
	{
		m->request.data[FUNCTION_INDEX] = (funtion & 0xff);
	}
	return Error_Ok;
}

int get_request_address(rtu_frame_t* m)
{
	int address = 0;

	if( m )
	{
		address += 0xff & (m->request.data[ADDRESS_INDEX0] << 8);
		address |= 0xff & (m->request.data[ADDRESS_INDEX1] << 0);
	}
	return address;
}
int set_request_address(rtu_frame_t* m, int address)
{
	if( m )
	{
		m->request.data[ADDRESS_INDEX0] = (address >> 8) & 0xff;
		m->request.data[ADDRESS_INDEX1] = (address >> 0) & 0xff;
	}
	return Error_Ok;
}

int get_request_count(rtu_frame_t* m)
{
	int count = 0;

	switch( get_request_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
		case x05_write_coil:
		case x06_write_register:
			count += 0xff & m->request.x01.count[0] << 8;
			count += 0xff & m->request.x01.count[1] << 0;
			break;
		case x0f_write_coils:
		case x10_write_registers:
			count += 0xff & m->request.x10.count[0] << 8;
			count += 0xff & m->request.x10.count[1] << 0;
			break;
	}
	return count;
}
int set_request_count(rtu_frame_t* m, int count)
{
	switch( get_request_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
		case x05_write_coil:
		case x06_write_register:
			m->request.x01.count[0] = (count >> 8) & 0xff;
			m->request.x01.count[1] = (count >> 0) & 0xff;
			break;
		case x0f_write_coils:
		case x10_write_registers:
			m->request.x10.count[0] = (count >> 8) & 0xff;
			m->request.x10.count[1] = (count >> 0) & 0xff;
			break;
	}
	return Error_Ok;
}

int get_request_byte(rtu_frame_t* m)
{
	switch( get_request_funcode(m) )
	{
		case x0f_write_coils:
		case x10_write_registers:
			return (0xff & m->request.x10.byte);
	}
	return Error_Ok;
}
int set_request_byte(rtu_frame_t* m, int byte)
{
	switch( get_request_funcode(m) )
	{
		case x0f_write_coils:
		case x10_write_registers:
			m->request.x10.byte = (byte & 0xff);
			break;
	}
	return Error_Ok;
}

int get_request_value(rtu_frame_t* m, int index)
{
	int value = 0;

	if( index < 0 || index > get_request_count(m) )
	{
		return Error_InvalidParamter;
	}
	switch(get_request_funcode(m))
	{
		case x05_write_coil:
		case x06_write_register:
			value += m->request.x05.count[0] << 8;
			value += m->request.x05.count[1] << 0;
			break;
		case x0f_write_coils:
			value = 0xff & m->request.x0f.data[index/8];
			value = 0x01 & (value >> (index%8));
			break;
		case x10_write_registers:
			value += m->request.x10.data[ (index * 2 + 0) ] << 8;
			value += m->request.x10.data[ (index * 2 + 1) ] << 0;
			break;
	}
	return value;
}
int set_request_value(rtu_frame_t* m, int index, int value)
{
	if( index < 0 || index > get_request_count(m) )
	{
		return Error_InvalidParamter;
	}
	switch(get_request_funcode(m))
	{
		case x05_write_coil:
		case x06_write_register:
			m->request.x05.count[0] = (value >> 8) & 0xff;
			m->request.x05.count[1] = (value >> 0) & 0xff;
			break;
		case x0f_write_coils:
			if( CoilOff == value )
			{
				m->request.x0f.data[index/8] &= ~(1 << (index%8));
			}
			else if( CoilOn == value )
			{
				m->request.x0f.data[index/8] |= (1 << (index%8));
			}
			break;
		case x10_write_registers:
			m->request.x10.data[index*2+0] = (value >> 8) & 0xff;
			m->request.x10.data[index*2+1] = (value >> 0) & 0xff;
			break;
	}
	return Error_Ok;
}
int set_request_data(rtu_frame_t* m, const char *data, int len)
{
	if( NULL == m || NULL == data || len < 1 )
	{
		return Error_InvalidParamter;
	}
	switch(get_request_funcode(m))
	{
		case x0f_write_coils:
		case x10_write_registers:
		{
			int i = 0;
			if( len > sizeof(m->request.x10.data) )
			{
				len = sizeof(m->request.x10.data);
			}
			for(i = 0; i < len; i++)
			{
				m->request.x10.data[i] = data[i];
			}
		}
	}
	return Error_Ok;
}

int get_request_crc(rtu_frame_t* m)
{
	int crc = 0;
	int index = 0;

	switch( m->request.data[1] )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
		case x05_write_coil:
		case x06_write_register:
			crc += m->request.x01.crc[1] << 8;
			crc += m->request.x01.crc[0] << 0;
			break;
		case x0f_write_coils:
		case x10_write_registers:
			index = 0xff & m->request.x10.byte;
			crc += m->request.x10.data[index + 1] << 8;
			crc += m->request.x10.data[index + 0] << 0;
			break;
	}
	return crc;
}
int set_request_crc(rtu_frame_t* m, int crc)
{
	int index = 0;

	switch( m->request.data[1] )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
		case x05_write_coil:
		case x06_write_register:
			m->request.x01.crc[0] = (crc >> 0) & 0xff;
			m->request.x01.crc[1] = (crc >> 8) & 0xff;
			break;
		case x0f_write_coils:
		case x10_write_registers:
			index = 0xff & m->request.x10.byte;
			m->request.x10.data[index + 0] = (crc >> 0) & 0xff;
			m->request.x10.data[index + 1] = (crc >> 8) & 0xff;
			break;
	}
	return Error_Ok;
}
int calc_request_crc(rtu_frame_t* m)
{
	int len = get_request_length(m) - 2;
	if( m )
	{
		if( len >= sizeof(m->request) )
		{
			return 0x0000;
		}
		return 0xffff & crc_modbus(m->request.data, len);
	}
	return 0x0000;
}

int get_request_length(rtu_frame_t* m)
{
	int len = 0;

	switch( get_request_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
		case x05_write_coil:
		case x06_write_register:
			/* ***************
			 * slave(1)
			 * func(1)
			 * addr(2)
			 * count(2)
			 * crc(2)
			 * ***************/
			len = 1 + 1 + 2 + 2 + 2;
			break;
		case x0f_write_coils:
		case x10_write_registers:
			/* *************
			 * slave(1)
			 * func(1)
			 * addr(2)
			 * count(2)
			 * byte(1)
			 * data()
			 * crc(2)
			 * *************/
			len = 1 + 1 + 2 + 2 + 1 + m->request.x10.byte + 2;
			break;
	}
	return len;
}

/* response frame access */

void init_response(rtu_frame_t *m)
{
	if( m )
	{
		int i = 0;
		for(i = 0 ; i < sizeof(m->response); i++)
		{
			m->response.data[i] = 0;
		}
		m->reqidx = 0;
	}
}
const char* get_response_sendpoint(rtu_frame_t *m)
{
	if( m )
	{
		return (char*)m->response.data;
	}
	return (char*)NULL;
}
const int get_response_sendlength(rtu_frame_t *m)
{
	return get_response_length(m);
}
int get_response_slave(rtu_frame_t* m)
{
	return (0xff & m->response.data[SLAVE_INDEX]);
}
int set_response_slave(rtu_frame_t* m, int slave)
{
	if( m )
	{
		m->response.data[SLAVE_INDEX] = (0xff & slave);
	}
	return Error_Ok;
}

int get_response_funcode(rtu_frame_t* m)
{
	if( m )
	{
		return (0xff & m->response.data[FUNCTION_INDEX]);
	}
	return 0xff;
}
int set_response_funcode(rtu_frame_t* m, int funtion)
{
	if( m )
	{
		m->response.data[FUNCTION_INDEX] = (0xff & funtion);
	}
	return Error_Ok;
}

int get_response_address(rtu_frame_t* m)
{
	int address = 0;

	switch( get_response_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
			break;
		case x05_write_coil:
		case x06_write_register:
		case x0f_write_coils:
		case x10_write_registers:
			address += (0xff & m->response.x05.addr[0] << 8);
			address += (0xff & m->response.x05.addr[1] << 0);
			break;
	}
	return address;
}
int set_response_address(rtu_frame_t* m, int address)
{
	switch( get_response_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
			break;
		case x05_write_coil:
		case x06_write_register:
		case x0f_write_coils:
		case x10_write_registers:
			m->response.x05.addr[0] = (0xff & (address >> 8));
			m->response.x05.addr[1] = (0xff & (address >> 0));
			break;
	}
	return Error_Ok;
}

int get_response_count(rtu_frame_t* m)
{
	int count = 0;

	switch( get_response_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
			count = (m->response.x01.byte * 8);
			break;
		case x03_read_holding:
		case x04_read_input:
			count = (0xff & (m->response.x01.byte / 2));
			break;
		case x05_write_coil:
		case x06_write_register:
		case x0f_write_coils:
		case x10_write_registers:
			count += (m->response.x05.count[0] << 8);
			count += (m->response.x05.count[1] << 0);
			break;
	}
	return count;

}
int set_response_count(rtu_frame_t* m, int count)
{
	switch( get_response_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
			m->response.x01.byte = 0xff & (count / 8);
			break;
		case x03_read_holding:
		case x04_read_input:
			m->response.x01.byte = 0xff & (count * 2);
			break;
		case x05_write_coil:
		case x06_write_register:
		case x0f_write_coils:
		case x10_write_registers:
			m->response.x05.count[0] = 0xff & (count >> 8);
			m->response.x05.count[1] = 0xff & (count >> 0);
			break;
	}
	return Error_Ok;
}

int get_response_byte(rtu_frame_t* m)
{
	int byte = 0;

	switch( get_response_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
			byte = (0xff & m->response.x01.byte);
			break;
	}
	return byte;
}
int set_response_byte(rtu_frame_t* m, int byte)
{
	switch( get_response_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
			m->response.x01.byte = (0xff & byte);
			break;
	}
	return Error_Ok;
}

int get_response_value(rtu_frame_t* m, int index)
{
	int value = 0;

	switch( get_response_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
			value = (0xff & m->response.x01.data[index/8]);
			value = (0x01 & (value >> (index % 8)) );
			break;
		case x03_read_holding:
		case x04_read_input:
			value += (m->response.x03.data[ (index * 2 + 0) ] << 8);
			value += (m->response.x03.data[ (index * 2 + 1) ] << 0);
			break;
	}
	return value;
}
int set_response_value(rtu_frame_t* m, int index, int value)
{
	switch( get_response_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
			if( CoilOn == value )
			{
				m->response.x01.data[index/8] |= (1 << (index%8));
			}
			else if( CoilOff == value )
			{
				m->response.x01.data[index/8] &= ~(1 << (index%8));
			}
			break;
		case x03_read_holding:
		case x04_read_input:
			m->response.x03.data[ (index * 2 + 0) ] = 0xff & (value >> 8);
			m->response.x03.data[ (index * 2 + 1) ] = 0xff & (value >> 0);
			break;
	}
	return Error_Ok;
}

int set_response_data(rtu_frame_t* m, const char *data, int len)
{
	if( NULL == m || NULL == data || len < 1 )
	{
		return Error_InvalidParamter;
	}
	switch(get_response_funcode(m))
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
		{
			int i = 0;
			if( len > sizeof(m->response.x01.data) )
			{
				len = sizeof(m->response.x01.data);
			}
			for(i = 0; i < len; i++)
			{
				m->response.x01.data[i] = data[i];
			}
		}
	}
	return Error_Ok;
}

int get_response_crc(rtu_frame_t* m)
{
	int crc = 0;
	int index = 0;

	switch( get_response_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
			index = m->response.x01.byte;
			crc += (m->response.x01.data[index + 1] << 8);
			crc += (m->response.x01.data[index + 0] << 0);
			break;
		case x05_write_coil:
		case x06_write_register:
		case x0f_write_coils:
		case x10_write_registers:
			crc += (m->response.x10.crc[1] << 8);
			crc += (m->response.x10.crc[0] << 0);
			break;
		case x80_x01_read_coil:
		case x80_x02_read_descrete:
		case x80_x03_read_holding:
		case x80_x04_read_input:
		case x80_x05_write_coil:
		case x80_x06_write_register:
		case x80_x0f_write_coils:
		case x80_x10_write_registers:
			crc += (m->response.exc.crc[1] << 8);
			crc += (m->response.exc.crc[0] << 0);
			break;
	}
	return crc;
}
int set_response_crc(rtu_frame_t* m, int crc)
{
	int index = 0;

	switch( get_response_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
			index = m->response.x01.byte;
			m->response.x01.data[index + 0] = (crc >> 0) & 0xff;
			m->response.x01.data[index + 1] = (crc >> 8) & 0xff;
			break;
		case x05_write_coil:
		case x06_write_register:
		case x0f_write_coils:
		case x10_write_registers:
			m->response.x10.crc[0] = (crc >> 0) & 0xff;
			m->response.x10.crc[1] = (crc >> 8) & 0xff;
			break;
	}
	return Error_Ok;
}
int calc_response_crc(rtu_frame_t* m)
{
	int len = get_response_length(m)-2;
	if( m )
	{
		if( len >= sizeof(m->response) )
		{
			return 0x0000;
		}
		return crc_modbus(m->response.data, len);
	}
	return 0x0000;
}

int get_response_length(rtu_frame_t* m)
{
	int len = 0;

	switch( get_response_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
			/* ************
			 * slave(1)
			 * func(1)
			 * byte(1)
			 * data(byte)
			 * crc(2)
			 * ************/
			len = 1 + 1 + 1 + m->response.x01.byte + 2;
			break;
		case x05_write_coil:
		case x06_write_register:
			/* ************
			 * slave(1)
			 * func(1)
			 * addr(2)
			 * value(2)
			 * crc(2)
			 * ***********/
			len = 1 + 1 + 2 + 2 + 2;
			break;
		case x0f_write_coils:
		case x10_write_registers:
			/* ***********
			 * slave(1)
			 * func(1)
			 * addr(2)
			 * count(2)
			 * crc(2)
			 * **********/
			len = 1 + 1 + 2 + 2 + 2;
			break;
		case x80_x01_read_coil:
		case x80_x02_read_descrete:
		case x80_x03_read_holding:
		case x80_x04_read_input:
		case x80_x05_write_coil:
		case x80_x06_write_register:
		case x80_x0f_write_coils:
		case x80_x10_write_registers:
			/* ***********
			 * slave(1)
			 * exfunc(1)
			 * excode(1)
			 * crc(2)
			 * **********/
			len = 1 + 1 + 1 + 2;
			break;
	}
	return len;
}
int get_succlen(rtu_frame_t* m)
{
	int len = 0;

	switch( get_request_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
			/* ************
			 * slave(1)
			 * func(1)
			 * byte(1)
			 * data(byte)
			 * crc(2)
			 * ************/
			len = 1 + 1 + 1 + m->response.x01.byte + 2;
			break;
		case x05_write_coil:
		case x06_write_register:
			/* ***********
			 * slave(1)
			 * func(1)
			 * addr(2)
			 * value(2)
			 * crc(2)
			 * **********/
			len = 1 + 1 + 2 + 2 + 2;
			break;
		case x0f_write_coils:
		case x10_write_registers:
			/* **********
			 * slave(1)
			 * func(1)
			 * addr(2)
			 * count(2)
			 * crc(2);
			 * *********/
			len = 1 + 1 + 2 + 2 + 2;
			break;
	}
	return len;
}
int get_excplen(rtu_frame_t* m)
{
	int len = 0;

	switch( get_request_funcode(m) )
	{
		case x01_read_coil:
		case x02_read_descrete:
		case x03_read_holding:
		case x04_read_input:
		case x05_write_coil:
		case x06_write_register:
		case x0f_write_coils:
		case x10_write_registers:
			/* **********
			 * slave(1)
			 * exfunc(1)
			 * excode(1)
			 * crc(2)
			 * *********/
			len = 1 + 1 + 1 + 2;
			break;
	}
	return len;
}
int push_response(rtu_frame_t *m, const char *data, int len)
{
	int i = 0;

	if( NULL == m || NULL == data || len < 1 )
	{
		return -1;
	}
	for(i = 0; i < len; i++)
	{
		if( m->reqidx >= sizeof(m->response) )
		{
			return i;
		}
		m->response.data[m->reqidx++] = data[i];
	}
	return len;
}

int get_exception_code(rtu_frame_t *m)
{
	if( m )
	{
		return (0xff & m->response.exc.code);
	}
	return -1;
}
int set_exception_code(rtu_frame_t *m, int code)
{
	if( m )
	{
		m->response.exc.code = (0xff & code);
	}
	return Error_Ok;
}
