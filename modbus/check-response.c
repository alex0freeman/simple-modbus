#include <stdio.h>
#include "rtu-debug.h"
#include "check-response.h"

int check_response(rtu_frame_t *frame)
{
	switch( get_response_funcode(frame) )
	{
		/* normal response */
		case x01_read_coil:
			return check_x01_response(frame);
		case x02_read_descrete:
			return check_x02_response(frame);
		case x03_read_holding:
			return check_x03_response(frame);
		case x04_read_input:
			return check_x04_response(frame);
		case x05_write_coil:
			return check_x05_response(frame);
		case x06_write_register:
			return check_x06_response(frame);
		case x0f_write_coils:
			return check_x0f_response(frame);
		case x10_write_registers:
			return check_x10_response(frame);

		/* exception response */
		case x80_x01_read_coil:
		case x80_x02_read_descrete:
		case x80_x03_read_holding:
		case x80_x04_read_input:
		case x80_x05_write_coil:
		case x80_x06_write_register:
		case x80_x0f_write_coils:
		case x80_x10_write_registers:
			return check_exception_response(frame);
	}
	return 0;
}

int check_x01_response(rtu_frame_t *frame)
{
	return ( get_response_crc(frame) == calc_response_crc(frame) );
}
int check_x02_response(rtu_frame_t *frame)
{
	return ( get_response_crc(frame) == calc_response_crc(frame) );
}
int check_x03_response(rtu_frame_t *frame)
{
	return ( get_response_crc(frame) == calc_response_crc(frame) );
}
int check_x04_response(rtu_frame_t *frame)
{
	return ( get_response_crc(frame) == calc_response_crc(frame) );
}
int check_x05_response(rtu_frame_t *frame)
{
	if( get_response_count(frame) != CoilOn )
	{
		if( get_response_count(frame) != CoilOff )
		{
			printf("%s:%X\n", __func__, get_response_count(frame));
			return 0;
		}
	}
	return ( get_response_crc(frame) == calc_response_crc(frame) );
}
int check_x06_response(rtu_frame_t *frame)
{
	return ( get_response_crc(frame) == calc_response_crc(frame) );
}
int check_x0f_response(rtu_frame_t *frame)
{
	if( get_response_count(frame) < MinCoilCount )
	{
		return 0;
	}
	if( get_response_count(frame) > MaxCoilCount )
	{
		return 0;
	}
	return ( get_response_crc(frame) == calc_response_crc(frame) );
}
int check_x10_response(rtu_frame_t *frame)
{
	if( get_response_count(frame) < MinRegisterCount )
	{
		return 0;
	}
	if( get_response_count(frame) > MaxRegisterCount )
	{
		return 0;
	}
	return ( get_response_crc(frame) == calc_response_crc(frame) );
}
int check_exception_response(rtu_frame_t *frame)
{
	switch( get_exception_code(frame) )
	{
		case exception_x01:
		case exception_x02:
		case exception_x03:
		case exception_x04:
		case exception_x05:
		case exception_x06:
			break;
		default:
			return 0;
	}
	return ( get_response_crc(frame) == calc_response_crc(frame) );
}
