#include <stdlib.h>
#include "modbus-context.h"


int modbus_context_init(modbus_context_t* context)
{
	if( context )
	{
		context->fd = -1;
		context->timeout = 0;
		context->mstime = 0;
		context->msleep = 0;
		context->send = 0;
		context->recv = 0;
		context->success = 0;
		context->failed = 0;
	}
}
int modbus_request(modbus_context_t *context, rtu_frame_t *frame)
{
	int slen = 0;//send length
	int then = 0;//time then

	if( NULL == context )
	{
		return error_context_null;
	}
	if( NULL == frame )
	{
		return error_frame_null;
	}
	if( NULL == context->send )
	{
		return error_send_null;
	}
	if( NULL == context->recv )
	{
		return error_recv_null;
	}
	if( NULL == context->success )
	{
		return error_succ_null;
	}
	if( NULL == context->failed )
	{
		return error_fail_null;
	}
	if( NULL == context->mstime )
	{
		return error_time_null;
	}
	if( context->timeout < 20 )
	{
		return error_timeout_less;
	}
	if( check_request(frame) == false )
	{
		context->failed(frame, error_check_failed);
		return error_check_failed;
	}

	while(1)
	{
		int ret = 0;
		char buf[32] = {0};
		ret = context->recv(context->fd, buf, sizeof(buf));
		if( ret < 1 )
		{
			break;
		}
	}
	slen = get_request_length(frame);
	if( slen != context->send(context->fd, (char*)frame->request.data, slen) )
	{
		context->failed(frame, error_send_failed);
		return error_send_failed;
	}
	context->success(frame, error_send_ok);

	//never forget init_response 
	init_response(frame);

	then = context->mstime();
	while( abs(context->mstime() - then) < context->timeout )
	{
		int len = 0;
		char buf[32] = {0};

		if( context->msleep )
		{
			context->msleep(1);
		}
		len = context->recv(context->fd, buf, sizeof(buf));
		if( len < 1 )
		{
			continue;
		}
		push_response(frame, buf, len);
		if( check_response(frame) )
		{
			context->success(frame, error_none_ok);
			return error_none_ok;
		}
		context->success(frame, error_recv_ok);
	}
	context->failed(frame, error_recv_timeout);
	return error_recv_timeout;
}
int modbus_response(modbus_context_t *context, rtu_frame_t *frame)
{
	if( NULL == context )
	{
		return error_context_null;
	}
	if( NULL == frame )
	{
		return error_frame_null;
	}
	if( NULL == context->send )
	{
		return error_send_null;
	}
	if( NULL == context->success )
	{
		return error_succ_null;
	}
	if( NULL == context->failed )
	{
		return error_fail_null;
	}
	if( check_response(frame) == false )
	{
		context->failed(frame, error_check_failed);
		return error_check_failed;
	}
	context->success(frame, error_check_ok);
	do{
		int len = 0;
		int ret = 0;

		len = get_response_length(frame);
		ret = context->send(context->fd, (char*)frame->response.data, len);
		if( len != ret )
		{
			context->success(frame, error_check_failed);
			return error_send_failed;
		}
		context->success(frame, error_send_ok);
	}while(0);
	return error_none_ok;
}
