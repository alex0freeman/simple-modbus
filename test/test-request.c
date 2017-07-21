#include <stdio.h>
#include "rtu-debug.h"
#include "make-request.h"
#include "check-request.h"

#define check_and_show(f,x)		\
do{								\
	if( f(&x) )					\
	{							\
		green_begin();			\
		show_request(&x);		\
		green_end();			\
	}							\
	else						\
	{							\
		red_begin();			\
		show_request(&x);		\
		red_end();				\
	}							\
}while(0)

int main(void)
{
	rtu_frame_t frame;

	make_x01_request(&frame, 1, 11, 11);
	check_and_show(check_x01_request, frame);
		
	make_x02_request(&frame, 1, 22, 22);
	check_and_show(check_x02_request, frame);

	make_x03_request(&frame, 1, 33, 33);
	check_and_show(check_x03_request, frame);

	make_x04_request(&frame, 1, 44, 44);
	check_and_show(check_x04_request, frame);

	make_x05_request(&frame, 1, 55, CoilOn);
	check_and_show(check_x05_request, frame);

	make_x06_request(&frame, 1, 66, 166);
	check_and_show(check_x06_request, frame);

	make_x0f_request(&frame, 1, 0x1234, 33, 5, (unsigned char*)"\x33\x44\x55\x66\x00");
	check_and_show(check_x0f_request, frame);

	make_x10_request(&frame, 1, 0x4567, 2, 4, (unsigned char*)"\x77\x88\x99\xaa");
	check_and_show(check_x10_request, frame);

	init_request(&frame);
	show_request(&frame);

	push_request(&frame, "\x01\x01\x00\x0b\x00\x0b\x0c\x0f", 8);
	check_and_show(check_request, frame);

	return 0;
}
