#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DELAY_BODY_SIZE 1300
typedef struct delay_obj
{
    uint16_t seqno;     // 序列号
    int64_t send_time;  // 发送时间
    int64_t recv_time;  // 回来时间
    uint8_t body[DELAY_BODY_SIZE];
} t_delay_obj;

int64_t iclock64();
uint32_t iclock();
t_delay_obj *delay_new();

inline void delay_set_seqno(t_delay_obj *obj, uint16_t seqno)
{
    obj->seqno = seqno;
}

inline void delay_set_seqno_send_time(t_delay_obj *obj, uint16_t seqno)
{
    obj->seqno     = seqno;
    obj->send_time = iclock64();
}

inline void delay_set_send_time(t_delay_obj *obj)
{
    obj->send_time = iclock64();
}

inline void delay_set_recv_time(t_delay_obj *obj)
{
    obj->recv_time = iclock64();
}

inline void delay_print_rtt_time(t_delay_obj *objs, int num)
{
    for (int i = 0; i < num; i++)
    {
        t_delay_obj *obj = &(objs[i]);
        printf("%04d seqno:%d rtt  :%ldms\n", i, obj->seqno, obj->recv_time - obj->send_time);
        // printf("%04d seqno:%d snd_t:%ldms\n", i, obj->seqno, obj->send_time);
        // printf("%04d seqno:%d rcv_t:%ldms\n", i, obj->seqno, obj->recv_time);
    }
}