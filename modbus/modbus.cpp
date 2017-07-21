#include <sys/time.h>
#include <unistd.h>
#include "uart.h"
#include "modbus.h"

modbus::modbus(void)
{
	consumetime = 0;
	context.fd = -1;
	context.timeout = 50;
	context.send = default_send;
	context.recv = default_recv;
	context.mstime = default_mstime;
	context.msleep = default_msleep;
	context.success = default_success;
	context.failed = default_failed;
}

bool modbus::open(const string& file)
{
	if( file.empty() )
	{
		return false;
	}
	int fd = uart_open(file.data());
	if( -1 == fd )
	{
		return false;
	}
	context.fd = fd;
	return true;
}
bool modbus::open(const string& file, int baud, char parity, int bsize, int stop)
{
	if( open(file) == false )
	{
		return false;
	}
	return (uart_config(context.fd, baud, parity, bsize, stop) == 0);
}
bool modbus::config(int baud, char parity, int bsize, int stop)
{
	return (uart_config(context.fd, baud, parity, bsize, stop) == 0);
}

bool modbus::request(framecontext& frame)
{
	consumetime = context.mstime();
	if( modbus_request(&context, frame.getframe()) )
	{
		consumetime = 0;
		return false;
	}
	consumetime = context.mstime() - consumetime;
	return true;
}
bool modbus::response(framecontext& frame)
{
	if( modbus_response(&context, frame.getframe()) )
	{
		return false;
	}
	return true;
}
int modbus::timeconsume(void)
{
	return consumetime;
}

void modbus::set_fd(int fd)
{
	context.fd = fd;
}
void modbus::set_timeout(int timeout)
{
	context.timeout = timeout;
}
void modbus::set_send( int(*f)(int,char*,int) )
{
	context.send = f;
}
void modbus::set_recv( int(*f)(int,char*,int) )
{
	context.recv = f;
}
void modbus::set_mstime( int(*f)(void) )
{
	context.mstime = f;
}
void modbus::set_msleep( int(*f)(unsigned int) )
{
	context.msleep = f;
}
void modbus::set_success( int(*f)(rtu_frame_t*, modbus_error_t) )
{
	context.success = f;
}
void modbus::set_failed( int(*f)(rtu_frame_t*, modbus_error_t) )
{
	context.failed = f;
}

int modbus::default_send(int fd, char* data, int len)
{
	return uart_write(fd, data, len);
}
int modbus::default_recv(int fd, char* buf, int len)
{
	return uart_read(fd, buf, len);
}
int modbus::default_mstime(void)
{
	int ms = 0;
	struct timeval t;

	if( gettimeofday(&t, 0) )
	{
		return 0;
	}
	ms = t.tv_sec % 60;
	ms = ms * 1000;
	ms = ms + t.tv_usec/1000;
	return ms;
}
int modbus::default_msleep(unsigned int ms)
{
	return usleep( ms * 1000 );
}
int modbus::default_success(rtu_frame_t* frame, modbus_error_t error)
{
	return 0;
}
int modbus::default_failed(rtu_frame_t* frame, modbus_error_t error)
{
	return 0;
}


