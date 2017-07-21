#include <stdio.h>
#include "rtu-debug.h"
#include "check-request.h"

int check_request(rtu_frame_t *frame)
{
	if( NULL == frame )
	{
		return 0;
	}
	switch( get_request_funcode(frame) )
	{
		case x01_read_coil:
			return check_x01_request(frame);

		case x02_read_descrete:
			return check_x02_request(frame);

		case x03_read_holding:
			return check_x03_request(frame);

		case x04_read_input:
			return check_x04_request(frame);

		case x05_write_coil:
			return check_x05_request(frame);

		case x06_write_register:
			return check_x06_request(frame);

		case x0f_write_coils:
			return check_x0f_request(frame);

		case x10_write_registers:
			return check_x10_request(frame);
	}
	return 0;
}

int check_x01_request(rtu_frame_t *frame)
{
	if( get_request_count(frame) < MinCoilCount )
	{
		printf("MinCoilCount\n");
		return 0;
	}
	if( get_request_count(frame) > MaxCoilCount )
	{
		printf("MaxCoilCount\n");
		return 0;
	}
	if( get_request_crc(frame) != calc_request_crc(frame) )
	{
		printf("crc:%04X != %04X\n", 
				get_request_crc(frame), calc_request_crc(frame));
	}
	return ( get_request_crc(frame) == calc_request_crc(frame) );
}
int check_x02_request(rtu_frame_t *frame)
{
	if( get_request_count(frame) < MinCoilCount )
	{
		return 0;
	}
	if( get_request_count(frame) > MaxCoilCount )
	{
		return 0;
	}
	return ( get_request_crc(frame) == calc_request_crc(frame) );
}
int check_x03_request(rtu_frame_t *frame)
{
	if( get_request_count(frame) < MinRegisterCount )
	{
		return 0;
	}
	if( get_request_count(frame) > MaxRegisterCount )
	{
		return 0;
	}
	return ( get_request_crc(frame) == calc_request_crc(frame) );
}
int check_x04_request(rtu_frame_t *frame)
{
	if( get_request_count(frame) < MinRegisterCount )
	{
		return 0;
	}
	if( get_request_count(frame) > MaxRegisterCount )
	{
		return 0;
	}
	return ( get_request_crc(frame) == calc_request_crc(frame) );
}
int check_x05_request(rtu_frame_t *frame)
{
	if( get_request_count(frame) != CoilOn )
	{
		if( get_request_count(frame) != CoilOff )
		{
			return 0;
		}
	}
	return ( get_request_crc(frame) == calc_request_crc(frame) );
}
int check_x06_request(rtu_frame_t *frame)
{
	return ( get_request_crc(frame) == calc_request_crc(frame) );
}
int check_x0f_request(rtu_frame_t *frame)
{
	return ( get_request_crc(frame) == calc_request_crc(frame) );
}
int check_x10_request(rtu_frame_t *frame)
{
	return ( get_request_crc(frame) == calc_request_crc(frame) );
}
