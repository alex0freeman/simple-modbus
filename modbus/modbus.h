#ifndef __MODBUS_H__
#define __MODBUS_H__
#include <string>
#include "frame-context.h"
#include "modbus-context.h"
using namespace std;

class modbus
{
private:
	int consumetime;
	modbus_context_t context;

public:
	modbus(void);

public:
	bool open(const string& file);
	bool open(const string& file, int baud, char parity, int bsize, int stop);
	bool config(int baud, char parity, int bsize, int stop);

public:
	bool request(framecontext& frame);
	bool response(framecontext& frame);
	int timeconsume(void);

public:
	void set_fd(int fd);
	void set_timeout(int);
	void set_send( int(*f)(int,char*,int) );
	void set_recv( int(*f)(int,char*,int) );
	void set_mstime( int(*f)(void) );
	void set_msleep( int(*f)(unsigned int) );
	void set_success( int(*f)(rtu_frame_t*, modbus_error_t) );
	void set_failed( int(*f)(rtu_frame_t*, modbus_error_t) );

private:
	static int default_send(int fd, char* data, int len);
	static int default_recv(int fd, char* buf, int len);
	static int default_mstime(void);
	static int default_msleep(unsigned int);
	static int default_success(rtu_frame_t*, modbus_error_t);
	static int default_failed(rtu_frame_t*, modbus_error_t);
};
#endif//__MODBUS_H__
