#include "rtu-debug.h"
#include "make-response.h"
#include "check-response.h"

#define check_and_show(f,x)		\
do{								\
	if( f(&x) )					\
	{							\
		green_begin();			\
		show_response(&x);		\
		green_end();			\
	}							\
	else						\
	{							\
		red_begin();			\
		show_response(&x);		\
		red_end();				\
	}							\
}while(0)

int main(void)
{
	rtu_frame_t frame;

	make_x01_response(&frame, 1, 3, "\xaa\xbb\xcc");
	check_and_show(check_x01_response, frame);
		
	make_x02_response(&frame, 1, 4, "\x88\x99\x00\xaa");
	check_and_show(check_x02_response, frame);

	make_x03_response(&frame, 1, 4, "\x11\x22\x33\x44");
	check_and_show(check_x03_response, frame);

	make_x04_response(&frame, 1, 4, "\x12\x34\x56\x78");
	check_and_show(check_x04_response, frame);

	make_x05_response(&frame, 1, 0x355, CoilOn);
	check_and_show(check_x05_response, frame);

	make_x06_response(&frame, 1, 0x466, 0x100);
	check_and_show(check_x06_response, frame);

	make_x0f_response(&frame, 1, 0x1234, 23);
	check_and_show(check_x0f_response, frame);

	make_x10_response(&frame, 1, 0x4567, 2);
	check_and_show(check_x10_response, frame);

	init_response(&frame);
	show_response(&frame);

	push_response(&frame, "\x01\x01\x03\xaa\xbb\xcc\x6e\xcb", 8);
	check_and_show(check_response, frame);

	return 0;
}
