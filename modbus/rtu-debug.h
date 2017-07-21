#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef cplusplus
extern "C"
#endif//cplusplus

#define green_begin()	printf("\033[1;32;48m")
#define green_end()		printf("\033[0m")
#define red_begin()		printf("\033[1;31;48m")
#define red_end()		printf("\033[0m")

int printf(const char*,...);

#define showhex(data, len)						\
do{												\
	int i = 0;									\
	int l = (int)len;							\
	unsigned char *p = (unsigned char*)data;	\
												\
	if( NULL == p || l < 1 )					\
	{											\
		break;									\
	}											\
	for(i = 0; i < l; i++)						\
	{											\
		printf("%02X ", p[i]);					\
	}											\
	printf("\n");								\
}while(0)


#define showhex_success(data, len)		\
do{										\
	green_begin();						\
	showhex(data, len);					\
	green_end();						\
}while(0)


#define showhex_error(data, len)		\
do{										\
	red_begin();						\
	showhex(data, len);					\
	red_end();							\
}while(0)

#endif//__DEBUG_H__
