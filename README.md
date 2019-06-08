Simple-modbus

Pure C implementation, a subset of Modbus, implements the most commonly used functions 0x01, 0x02, 0x03, 0x04, 0x05, 0x6, 0x0f, 0x10
The frame structure initializes the interface. This interface must be called before using the frame structure.

Void init_frame(rtu_frame_t *m)

Make a request frame, the slave will call these interfaces

/ / Read continuous coil
Int make_x01_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

/ / Read the discrete coil
Int make_x02_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

//Read holding register
Int make_x03_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

/ / read the input register
Int make_x04_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

/ / Write a coil state, value is 0xff00, 0x00ff, 0xff00 represents state 1, 0x00ff represents state 0
Int make_x05_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value);

/ / Write a register
Int make_x06_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value);

/ / Write multiple coils, each coil occupies one bit, only 0, 1 two states
Int make_x0f_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count, unsigned char byte, unsigned char *data);

/ / Write multiple registers, each register occupies two bytes
Int make_x10_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count, unsigned char byte, unsigned char *data);

Make a reply post, modbus server will call these interfaces

/* Make a reply frame to reply to the read coil request */
Int make_x01_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

/* Make a reply frame that responds to a request to read a discrete coil */
Int make_x02_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

/* Make a reply frame that reads back from the hold register request */
Int make_x03_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

/* Make a reply frame that responds to the request read from the input register */
Int make_x04_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

/* Make a reply frame that responds to a request to write a single coil */
Int make_x05_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value );

/* Make a reply frame that replies to a single register request */
Int make_x06_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value );

/* Make a reply frame that responds to multiple consecutive coil requests */
Int make_x0f_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count );

/* Make a reply frame that replies to multiple consecutive register requests */
Int make_x10_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count );

The master makes a response frame that responds to the exception request frame.

/* Reply to the response frame of the read coil exception */
Int make_x80_x01_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* Reply to the response frame of the read discrete coil exception */
Int make_x80_x02_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* Reply to read response register exception register response */
Int make_x80_x03_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* Reply to the response frame of the read input register exception */
Int make_x80_x04_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* Reply to the response frame of the write single coil exception */
Int make_x80_x05_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* Reply to the response frame of the write register exception */
Int make_x80_x06_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* Reply to the response frame for writing multiple coil anomalies */
Int make_x80_x0f_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* Reply to the response frame for writing multiple register exceptions */
Int make_x80_x10_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* General interface for making exception request response frames */
Int make_exception_response(rtu_frame_t *frame, unsigned char slave, unsigned char funcode, unsigned char code);

Modbus request and reply processing top level interface
Modbus_context_t field description

/* ************************************************ ********************************************
 * fd: fd can be a socket or open file number in linux environment *
 * time: used to get the system time, return the current time in milliseconds *
 * usleep: delay for read and write operations, parameters in microseconds, this field can be empty *
 * send: The interface for sending data frames cannot be empty (the first parameter is fd, the second parameter is data pointer, and the third parameter is data length) *
 * recv: The interface that receives the data frame, can't be empty (the first parameter is fd, the second parameter is the buffer pointer, and the third parameter is the buffer size) *
 * succ: The process will call back this function, it can't be empty *
 * fail: The procedure will call back this function, it can't be empty *
 ************************************************** ********************************************/


Typedef struct
{
Int fd;
Int timeout;
Int (*time)(void);
Int (*usleep)(unsigned int);
Int (*send)(int, char*, int);
Int (*recv)(int, char*, int);
Int (*succ)(rtu_frame_t*, modbus_error_t);
Int (*fail)(rtu_frame_t*, modbus_error_t);
}modbus_context_t;

/* modub context initialization interface, this interface must be called before using modbus_context_t */
Int modbus_context_init(modbus_context_t*);

/* The interface is called from the end to make a request. If it succeeds, it returns 0. The reply frame is saved in frame->response. If it fails, it returns the failure code. modbus.h defines the failure code.
Int modbus_request(modbus_context_t* context, rtu_frame_t* frame);

/* The master calls these interfaces to reply. If it succeeds, it returns 0. If it fails, it returns the failure code. modbus.h defines the failure code.
Int modbus_response(modbus_context_t* context, rtu_frame_t* frame);