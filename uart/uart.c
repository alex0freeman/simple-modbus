#include "uart.h"

int uart_open(const char *path)
{
	if( path )
	{
		return open(path, O_RDWR);
	}
	return -1;
}

int uart_config(int fd, int baud, char parity, int bsize, int stop)
{
	if( fd < 0 )
	{
		return -1;
	}
	else
	{
		struct termios newios = {0};

		bzero(&newios, sizeof(newios));
		if( set_speed(&newios, baud) )
		{
			return -2;
		}
		if( set_parity(&newios, parity) )
		{
			return -3;
		}
		if( set_bsize(&newios, bsize) )
		{
			return -4;
		}
		if( set_stop(&newios, stop) )
		{
			return -5;
		}
		enable_read(&newios);
		disable_flow_control(&newios);
		if( set_termios(fd, &newios) )
		{
			return -6;
		}
	}
	return 0;
}

int uart_read(int fd, char *buf, int len)
{
	if( fd < 0 || 0 == buf || len < 1 )
	{
		return -1;
	}
	return read(fd, buf, len);
}

int uart_write(int fd,  const char *data, int len)
{
	if( fd < 0 || 0 == data || len < 1 )
	{
		return -1;
	}
	return write(fd, data, len);
}

int uart_close(int fd)
{
	return close(fd);
}
