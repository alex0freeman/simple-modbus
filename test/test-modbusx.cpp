#include <unistd.h>
#include <stdio.h>
#include "modbus.h"
#include "frame-context.h"


int main(int argc, char **argv)
{
	modbus modbus;
	framecontext frame;

	frame.make_request_x03(1, 0, 2);
	modbus.open("/dev/ttyS0", 9600, 'n', 8, 1);
	while(1)
	{
		if( modbus.request(frame) )
		{
			printf("%d:[T=%.1f  H=%.1f]:", 
					modbus.timeconsume(), 
					frame.response_value(0)/10.0,
					frame.response_value(1)/10.0);
			green_begin();
			show_response(frame.getframe());
			green_end();
		}
		sleep(1);
	}

	return 0;
}
