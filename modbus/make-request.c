#include "make-request.h"


//read coil
int make_x01_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count
)
{
	if( NULL == frame )
	{
		return Error_InvalidParamter;
	}
	if( count < MinCoilCount || count > MaxCoilCount )
	{
		return Error_InvalidCoilCount;
	}
	set_request_slave(frame, slave);
	set_request_funcode(frame, x01_read_coil);
	set_request_address(frame, address);
	set_request_count(frame, count);
	set_request_crc(frame, calc_request_crc(frame));
	return Error_Ok;
}

//read descrete coil
int make_x02_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count
)
{
	if( NULL == frame )
	{
		return Error_InvalidParamter;
	}
	if( count < MinCoilCount || count > MaxCoilCount )
	{
		return Error_InvalidCoilCount;
	}
	set_request_slave(frame, slave);
	set_request_funcode(frame, x02_read_descrete);
	set_request_address(frame, address);
	set_request_count(frame, count);
	set_request_crc(frame, calc_request_crc(frame));
	return Error_Ok;
}

//read holding register
int make_x03_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count
)
{
	if( NULL == frame )
	{
		return Error_InvalidParamter;
	}
	if( count < MinRegisterCount || count > MaxRegisterCount )
	{
		return Error_InvalidRegisterCount;
	}
	set_request_slave(frame, slave);
	set_request_funcode(frame, x03_read_holding);
	set_request_address(frame, address);
	set_request_count(frame, count);
	set_request_crc(frame, calc_request_crc(frame));
	return Error_Ok;
}


//read input register 
int make_x04_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count
)
{
	if( NULL == frame )
	{
		return Error_InvalidParamter;
	}
	if( count < MinRegisterCount || count > MaxRegisterCount )
	{
		return Error_InvalidRegisterCount;
	}
	set_request_slave(frame, slave);
	set_request_funcode(frame, x04_read_input);
	set_request_address(frame, address);
	set_request_count(frame, count);
	set_request_crc(frame, calc_request_crc(frame));
	return Error_Ok;
}

//write one coil 
int make_x05_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short value
)
{
	if( NULL == frame )
	{
		return Error_InvalidParamter;
	}
	if( CoilOn != value && CoilOff != value )
	{
		return Error_InvalidCoilValue;
	}
	set_request_slave(frame, slave);
	set_request_funcode(frame, x05_write_coil);
	set_request_address(frame, address);
	set_request_count(frame, value);
	set_request_crc(frame, calc_request_crc(frame));
	return Error_Ok;
}

//write one register 
int make_x06_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short value
)
{
	if( NULL == frame )
	{
		return Error_InvalidParamter;
	}
	set_request_slave(frame, slave);
	set_request_funcode(frame, x06_write_register);
	set_request_address(frame, address);
	set_request_count(frame, value);
	set_request_crc(frame, calc_request_crc(frame));
	return Error_Ok;
}

//write multiple coil 
int make_x0f_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count,
	unsigned char byte,
	unsigned char *data
)
{
	if( NULL == frame || NULL == data ||byte < 1 )
	{
		return -1;
	}
	if( count < MinCoilCount || count > MaxCoilCount )
	{
		return Error_InvalidCoilCount;
	}
	set_request_slave(frame, slave);
	set_request_funcode(frame, x0f_write_coils);
	set_request_address(frame, address);
	set_request_count(frame, count);
	set_request_byte(frame, byte);
	set_request_data(frame, data, byte);
	set_request_crc(frame, calc_request_crc(frame));
	return Error_Ok;
}

//write multiple register
int make_x10_request
(
	rtu_frame_t *frame, 
	unsigned char slave,
	unsigned short address,
	unsigned short count,
	unsigned char byte,
	unsigned char *data
)
{
	if( NULL == frame || NULL == data || byte < 1 )
	{
		return -1;
	}
	if( count < MinRegisterCount || count > MaxRegisterCount )
	{
		return Error_InvalidRegisterCount;
	}
	set_request_slave(frame, slave);
	set_request_funcode(frame, x10_write_registers);
	set_request_address(frame, address);
	set_request_count(frame, count);
	set_request_byte(frame, byte);
	set_request_data(frame, data, byte);
	set_request_crc(frame, calc_request_crc(frame));
	return Error_Ok;
}


