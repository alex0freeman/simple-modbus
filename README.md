# simple-modbus
纯C语言实现，Modbus的一个字集，实现了0x01, 0x02, 0x03, 0x04, 0x05, 0x6, 0x0f, 0x10这几个最常用的功能

```c
void init_frame(rtu_frame_t *m)
//read coil

int make_x01_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

//read descrete coil
int make_x02_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

//read holding register 
int make_x03_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

//read input register 
int make_x04_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

//write one coil 
int make_x05_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value);

//write one register 
int make_x06_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value);

//write multiple coil 
int make_x0f_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count, unsigned char byte, unsigned char *data);

//write multiple register
int make_x10_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count, unsigned char byte, unsigned char *data);

```

```c
/* make normal response */
int make_x01_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

int make_x02_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

int make_x03_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

int make_x04_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

int make_x05_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value );

int make_x06_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value );

int make_x0f_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count );

int make_x10_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count );

/* make excption response */

int make_x80_x01_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

int make_x80_x02_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

int make_x80_x03_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

int make_x80_x04_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

int make_x80_x05_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

int make_x80_x06_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

int make_x80_x0f_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

int make_x80_x10_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

int make_exception_response(rtu_frame_t *frame, unsigned char slave, unsigned char funcode, unsigned char code);


```

```c
typedef struct
{
	int fd;
	int timeout;
	int (*time)(void);
	int (*usleep)(unsigned int);
	int (*send)(int, char*, int);
	int (*recv)(int, char*, int);
	int (*succ)(rtu_frame_t*, modbus_error_t);
	int (*fail)(rtu_frame_t*, modbus_error_t);
}modbus_context_t;

int modbus_context_init(modbus_context_t*);
int modbus_request(modbus_context_t*, rtu_frame_t*);
int modbus_response(modbus_context_t*, rtu_frame_t*);

```
