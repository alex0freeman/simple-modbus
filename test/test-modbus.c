#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "uart.h"
#include "modbus-context.h"


int mtime(void);
int recv(int, char*, int);
int send(int, char*, int);
int succ(rtu_frame_t*, modbus_error_t);
int fail(rtu_frame_t*, modbus_error_t);

int main(int argc, char **argv)
{
	int fd = -1;
	int baud = 115200;
	char *file = (char*)"/dev/ttyS0";
	modbus_context_t context;
	rtu_frame_t frame;

	if( argc > 1 )
	{
		file = argv[1];
	}
	if( argc > 2 )
	{
		baud = atoi(argv[2]);
	}

	fd = uart_open(file);
	if( fd < 0 )
	{
		printf("uart_open(%s) failed!\n", file);
		return -1;
	}
	printf("uart_open(%s)=%d\n", file, fd);
	if( uart_config(fd, baud, 'n', 8, 1) )
	{
		printf("uart_config(%d, %d, n, 8, 1) failed\n", fd, baud);
		return -2;
	}
	printf("uart_config(%d, %d, n, 8, 1)\n", fd, baud);

	init_frame(&frame);

	make_x03_request(&frame, 1, 0, 2);

	modbus_context_init(&context);

	context.fd = fd;
	context.mstime = mtime;
	context.send = send;
	context.recv = recv;
	context.success = succ;
	context.failed = fail;
	context.timeout = 200;
	context.msleep = usleep;

	while(1)
	{
		int last = mtime();

		if( modbus_request(&context, &frame) == 0 )
		{ 
			float temp = get_response_value(&frame, 0);
			float humi = get_response_value(&frame, 1);
			printf("%d: ", mtime() - last);
			printf("T = %.1f, H = %.1f\n", temp / 10.0, humi / 10.0);
		}
		sleep(1);
	}

	return 0;
}


int mtime(void)
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
int send(int fd, char *data, int len)
{
	//printf("%s\n", __func__);
	return uart_write(fd, data, len);
}
int recv(int fd, char *buf, int len)
{
	//printf("%s\n", __func__);
	return uart_read(fd, buf, len);
}
int succ(rtu_frame_t *frame, modbus_error_t error)
{
	return 0;
	switch(error)
	{
		case error_check_ok:
			break;
		case error_recv_ok:
			showhex(frame->response.data, frame->residx);
			break;
		case error_send_ok:
			printf("send:");
			green_begin();
			show_request(frame);
			green_end();
			break;
		case error_none_ok:
			printf("recv:");
			green_begin();
			green_begin();
			show_response(frame);
			green_end();
			printf("value[0]=%d\n", get_response_value(frame, 0));
			printf("value[1]=%d\n", get_response_value(frame, 1));
			break;
	}
}
int fail(rtu_frame_t *frame, modbus_error_t error)
{
	return 0;
	switch(error)
	{
		case error_check_failed:
			printf("check failed:");
			red_begin();
			show_request(frame);
			red_end();
			break;
		case error_send_failed:
			printf("send failed:");
			red_begin();
			show_request(frame);
			red_end();
			break;
		case error_recv_timeout:
			printf("recv timeout:");
			red_begin();
			show_response(frame);
			red_end();
			break;
	}
}
