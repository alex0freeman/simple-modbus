#include "make-response.h"

int make_x01_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char byte,
	unsigned char *data
)
{
	if( NULL == frame || NULL == data || byte < 1 )
	{
		return Error_InvalidParamter;
	}
	set_response_slave(frame, slave);
	set_response_funcode(frame, x01_read_coil);
	set_response_byte(frame, byte);
	set_response_data(frame, data, byte);
	set_response_crc(frame, calc_response_crc(frame));
	return Error_Ok;
}

int make_x02_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char byte,
	unsigned char *data
)
{
	if( NULL == frame || NULL == data || byte < 1 )
	{
		return Error_InvalidParamter;
	}
	set_response_slave(frame, slave);
	set_response_funcode(frame, x02_read_descrete);
	set_response_byte(frame, byte);
	set_response_data(frame, data, byte);
	set_response_crc(frame, calc_response_crc(frame));
	return Error_Ok;
}

int make_x03_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char byte,
	unsigned char *data
)
{
	if( NULL == frame || NULL == data || byte < 1 )
	{
		return Error_InvalidParamter;
	}
	set_response_slave(frame, slave);
	set_response_funcode(frame, x03_read_holding);
	set_response_byte(frame, byte);
	set_response_data(frame, data, byte);
	set_response_crc(frame, calc_response_crc(frame));
	return Error_Ok;
}

int make_x04_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char byte,
	unsigned char *data
)
{
	if( NULL == frame || NULL == data || byte < 1 )
	{
		return Error_InvalidParamter;
	}
	set_response_slave(frame, slave);
	set_response_funcode(frame, x04_read_input);
	set_response_byte(frame, byte);
	set_response_data(frame, data, byte);
	set_response_crc(frame, calc_response_crc(frame));
	return Error_Ok;
}

int make_x05_response
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
		return Error_InvalidParamter;
	}
	set_response_slave(frame, slave);
	set_response_funcode(frame, x05_write_coil);
	set_response_address(frame, address);
	set_response_count(frame, value);
	set_response_crc(frame, calc_response_crc(frame));
	return Error_Ok;
}

int make_x06_response
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
	set_response_slave(frame, slave);
	set_response_funcode(frame, x06_write_register);
	set_response_address(frame, address);
	set_response_count(frame, value);
	set_response_crc(frame, calc_response_crc(frame));
	return Error_Ok;
}

int make_x0f_response
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
	if( count < MinCoilCount )
	{
		return Error_InvalidCoilCount;
	}
	if( count > MaxCoilCount )
	{
		return Error_InvalidCoilCount;
	}
	set_response_slave(frame, slave);
	set_response_funcode(frame, x0f_write_coils);
	set_response_address(frame, address);
	set_response_count(frame, count);
	set_response_crc(frame, calc_response_crc(frame));
	return Error_Ok;
}

int make_x10_response
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
	if( count < MinRegisterCount )
	{
		return Error_InvalidRegisterCount;
	}
	if( count > MaxRegisterCount )
	{
		return Error_InvalidRegisterCount;
	}
	set_response_slave(frame, slave);
	set_response_funcode(frame, x10_write_registers);
	set_response_address(frame, address);
	set_response_count(frame, count);
	set_response_crc(frame, calc_response_crc(frame));
	return Error_Ok;
}

/* make excption response */
int make_exception_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char funcode,
	unsigned char code
)
{
	if( NULL == frame )
	{
		return Error_InvalidParamter;
	}
	set_response_slave(frame, slave);
	set_response_funcode(frame, funcode);
	set_exception_code(frame, code);
	set_response_crc(frame, calc_response_crc(frame));
	return Error_Ok;
}


int make_x80_x01_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
)
{
	return make_exception_response(frame, slave, x80_x01_read_coil, code);
}

int make_x80_x02_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
)
{
	return make_exception_response(frame, slave, x80_x02_read_descrete, code);
}

int make_x80_x03_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
)
{
	return make_exception_response(frame, slave, x80_x03_read_holding, code);
}

int make_x80_x04_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
)
{
	return make_exception_response(frame, slave, x80_x04_read_input, code);
}

int make_x80_x05_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
)
{
	return make_exception_response(frame, slave, x80_x05_write_coil, code);
}

int make_x80_x06_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
)
{
	return make_exception_response(frame, slave, x80_x06_write_register, code);
}

int make_x80_x0f_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
)
{
	return make_exception_response(frame, slave, x80_x0f_write_coils, code);
}

int make_x80_x10_response
(
	rtu_frame_t *frame,
	unsigned char slave,
	unsigned char code
)
{
	return make_exception_response(frame, slave, x80_x10_write_registers, code);
}


