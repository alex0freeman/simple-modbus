#ifndef __RTU_DEFINE_H__
#define __RTU_DEFINE_H__
#include "type-define.h"

#define MakeShort(h,l)	( (((short)(h)&0xff)<<8) | ((short)(l)&0xff) )
#define ArrayToShort(a)	( (unsigned short)MakeShort(a[0], a[1]) )
#define ArrayToCRC16(a)	( (unsigned short)MakeShort(a[1], a[0]) )
#define GetCoilCount(c) ( (c/8) + ((c%8) ? 1 : 0) )
#define ShortHig(v)		( (unsigned char)(((v)>> 8) & 0xff) )
#define ShortLow(v)		( (unsigned char)((v) & 0xff) )

typedef enum
{
	MinAddress = 0x0000,
	MaxAddress = 0xFFFF,
}MinMaxAddressSize_t;

typedef enum
{
	MinCoilCount = 1,
	MaxCoilCount = 2000,
}MinMaxCoilCount_t;

typedef enum
{
	MinRegisterCount = 1,
	MaxRegisterCount = 125,
}MinMaxRegisterCount_t;


typedef enum
{
	CoilOff = 0x000,
	CoilOn = 0xFF00,
}CoilValue_t;

typedef enum
{
	MinRegisterValue = 0x0000,
	MaxRegisterValue = 0xFFFF,
}RegisterValue_t;

typedef enum 
{	
	x01_read_coil			= 0x01,
	x02_read_descrete		= 0x02,
	x03_read_holding		= 0x03,
	x04_read_input		= 0x04,

	x05_write_coil		= 0x05,
	x06_write_register	= 0x06,
	x0f_write_coils		= 0x0F,
	x10_write_registers	= 0x10,

	x2b_read_devinfo		= 0x2B,
}request_function_code_t;

typedef enum
{
	x80_x01_read_coil		= (0x80 + 0x01),
	x80_x02_read_descrete	= (0x80 + 0x02),
	x80_x03_read_holding	= (0x80 + 0x03),
	x80_x04_read_input		= (0x80 + 0x04),

	x80_x05_write_coil		= (0x80 + 0x05),
	x80_x06_write_register	= (0x80 + 0x06),
	x80_x0f_write_coils		= (0x80 + 0x0F),
	x80_x10_write_registers	= (0x80 + 0x10),
}response_function_code_t;

typedef enum
{
	exception_x01 = 0x01,
	exception_x02 = 0x02,
	exception_x03 = 0x03,
	exception_x04 = 0x04,
	exception_x05 = 0x05,
	exception_x06 = 0x06,
}exception_code_t;

typedef enum 
{	
	Error_Ok						=  0,
	Error_NotInit					= -1,
	Error_SendFailed				= -2,
	Error_InvalidParamter			= -3,
	Error_InvalidCoilValue			= -5,
	Error_InvalidCoilCount			= -6,
	Error_InvalidRegisterCount		= -7,
	Error_InvalidRegisterValue		= -8,

	Error_Recieving					= -40,
	Error_RecvTimeOut				= -41,
	Error_InvalidResponseSlave		= -42,
	Error_InvalidResponseFunc		= -43,
	Error_InvalidResponseAddr		= -44,
	Error_InvalidResponseCount		= -45,
	Error_InvalidResponseValue		= -46,
	Error_InvalidResponseByte		= -47,
	Error_InvalidResponseCrc		= -48,

}ErrorCode_t;

/*****************************************
 ** requestx can be used for:			**
 ** 1. read coil						**
 ** 2. read descrete					**
 ** 3. read holding						**
 ** 4. read input						**
 ** 5. write one coil					**
 ** 6. write one register				**
 *****************************************/
struct requestx
{
	unsigned char slave;
	unsigned char func;
	unsigned char addr[2];
	unsigned char count[2];
	unsigned char crc[2];
};

/*****************************************
 ** requestm can be used for:			**
 ** 1. write multiple coils				**
 ** 2. write multiple registers			**
 *****************************************/
struct requestm
{
	unsigned char slave;
	unsigned char func;
	unsigned char addr[2];
	unsigned char count[2];
	unsigned char byte;
	unsigned char data[256];
};

/*****************************************
 ** responsex can be used for:			**
 ** 1. read coil						**
 ** 2. read descrete					**
 ** 3. read holding						**
 ** 4. read input						**
 *****************************************/
struct responsex
{
	unsigned char slave;
	unsigned char func;
	unsigned char byte;
	unsigned char data[256];
};

/*****************************************
 ** responsew can be used for:			**
 ** 1. write coil						**
 ** 2. write register					**
 ** 3. write multiple coils				**
 ** 4. write multiple registers			**
 ** w meats write operation				**
 *****************************************/
struct responsew
{
	unsigned char slave;
	unsigned char func;
	unsigned char addr[2];
	unsigned char count[2];
	unsigned char crc[2];
};
struct exception
{
	unsigned slave;
	unsigned func;
	unsigned code;
	unsigned crc[2];
};

typedef struct rtu_frame
{
	int reqidx;
	union{
		struct requestx x01;	 //read coil
		struct requestx x02;	 //read descrete
		struct requestx x03;	 //read holding
		struct requestx x04;	 //read input
		struct requestx x05;	 //write coil
		struct requestx x06;	 //write register
		struct requestm x0f;	 //write multiple coil
		struct requestm x10;	 //write multiple register
		unsigned char data[256]; //convenient for byte wise access
	}request;

	int residx;
	union{
		struct responsex x01;
		struct responsex x02;
		struct responsex x03;
		struct responsex x04;
		struct responsew x05;
		struct responsew x06;
		struct responsew x0f;
		struct responsew x10;
		struct exception exc;
		unsigned char data[256];
	}response;
}rtu_frame_t;

#endif//__RTU_DEFINE_H__
