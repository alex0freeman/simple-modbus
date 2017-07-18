# simple-modbus
纯C语言实现，Modbus的一个字集，实现了0x01, 0x02, 0x03, 0x04, 0x05, 0x6, 0x0f, 0x10这几个最常用的功能

## 帧结构初始化接口，使用帧结构前必须先调用此接口
```c
void init_frame(rtu_frame_t *m)
```

## 制作请求帧，从设备会调用这些接口
```c

//读连续线圈
int make_x01_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

//读取离散线圈
int make_x02_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

//读保持寄存器 
int make_x03_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

//读输入寄存器
int make_x04_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count);

//写一个线圈状态，value取值是0xff00、0x00ff，0xff00代表状态1，0x00ff代表状态0
int make_x05_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value);

//写一个寄存器
int make_x06_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value);

//写多个线圈，每个线圈占一个位，只有0、1两种状态
int make_x0f_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count, unsigned char byte, unsigned char *data);

//写多个寄存器，每个寄存器占两个字节
int make_x10_request(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count, unsigned char byte, unsigned char *data);

```

## 制作回复帖，modbus的服务端会调用到这些接口
```c
/* 制作回复读线圈请求的回复帧 */
int make_x01_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

/* 制作回复读离散线圈请求的回复帧 */
int make_x02_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

/* 制作回复读离保持寄存器请求的回复帧 */
int make_x03_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

/* 制作回复读离输入寄存器请求的回复帧 */
int make_x04_response(rtu_frame_t *frame, unsigned char slave, unsigned char byte, unsigned char *data);

/* 制作回复写单个线圈的请求的回复帧 */
int make_x05_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value );

/* 制作回复写单个寄存器请求的回复帧 */
int make_x06_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short value );

/* 制作回复写多个连续线圈请求的回复帧 */
int make_x0f_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count );

/* 制作回复写多个连续寄存器请求的回复帧 */
int make_x10_response(rtu_frame_t *frame, unsigned char slave, unsigned short address, unsigned short count );

```

## 主端制作回复异常请求帧的回应帧
```c
/* 回复读线圈异常的回应帧 */
int make_x80_x01_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* 回复读离散线圈异常的回应帧 */
int make_x80_x02_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* 回复读保持寄存器异常的回应帧 */
int make_x80_x03_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* 回复读输入寄存器异常的回应帧 */
int make_x80_x04_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* 回复写单线圈异常的回应帧 */
int make_x80_x05_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* 回复写单寄存器异常的回应帧 */
int make_x80_x06_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* 回复写多线圈异常的回应帧 */
int make_x80_x0f_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* 回复写多寄存器异常的回应帧 */
int make_x80_x10_response(rtu_frame_t *frame, unsigned char slave, unsigned char code);

/* 通用制作异常请求回应帧的接口 */
int make_exception_response(rtu_frame_t *frame, unsigned char slave, unsigned char funcode, unsigned char code);

```

## Modbus 请求与回复处理最高层接口
### modbus_context_t各字段说明

>fd：在linux环境下fd可以是socket或打开的文件号
>time：用来获取系统时间，返回以毫秒为单位的当前时间
>usleep：用于读写操作的延时，参数以微秒为单位，本字段可以为空
>send：发送数据帧的接口，不能为空（第一个参数是fd，第二个参数是数据指针，第三个参数是数据长度）
>recv：接收数据帧的接口，不能为空（第一个参数是fd，第二个参数是缓冲区指针，第三个参数是缓冲区大小）
>succ：过程成功会回调此函数，不能为空
>fail：过程失败会回调此函数，不能为空

```c
typedef struct
{
	int fd;
	int timeout;
	int (*time)(void);
	int (*usleep)(unsigned int);
	int (*send)(int, char*, int);
	int (*recv)(int, char*, int);
	int (*succ)(rtu_frame_t*, modbus_error_t);
	int (*fail)(rtu_frame_t*, modbus_error_t);
}modbus_context_t;

/* modub上下文初始化接口，使用modbus_context_t前必须先调用此接口 */
int modbus_context_init(modbus_context_t*);

/* 从端调用些接口进行请求，成功则返回0，回复帧保存在frame->response内，失败则返回失败码，modbus.h定义了失败码 */
int modbus_request(modbus_context_t* context， rtu_frame_t* frame);

/* 主端调用些接口进行回复，成功则返回0，失败则返回失败码，modbus.h定义了失败码 */
int modbus_response(modbus_context_t* context, rtu_frame_t* frame);

```
