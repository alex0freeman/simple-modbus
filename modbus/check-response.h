#ifndef __CHECK_RESPONSE_H__
#define __CHECK_RESPONSE_H__
#include "frame-access.h"

#ifdef cplusplus
extern "C"
#endif//cplusplus

int check_response(rtu_frame_t* frame);

 int check_x01_response(rtu_frame_t *frame);
 int check_x02_response(rtu_frame_t *frame);
 int check_x03_response(rtu_frame_t *frame);
 int check_x04_response(rtu_frame_t *frame);
 int check_x05_response(rtu_frame_t *frame);
 int check_x06_response(rtu_frame_t *frame);
 int check_x0f_response(rtu_frame_t *frame);
 int check_x10_response(rtu_frame_t *frame);

int check_exception_response(rtu_frame_t *frame);

 int check_x81_response(rtu_frame_t *frame);
 int check_x82_response(rtu_frame_t *frame);
 int check_x83_response(rtu_frame_t *frame);
 int check_x84_response(rtu_frame_t *frame);
 int check_x85_response(rtu_frame_t *frame);
 int check_x86_response(rtu_frame_t *frame);
 int check_x8f_response(rtu_frame_t *frame);
 int check_x90_response(rtu_frame_t *frame);


#endif//__CHECK_RESPONSE_H__
