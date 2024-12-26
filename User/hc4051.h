#ifndef _HC4051_H
#define _HC4051_H

#include <stdint.h>
#include <stdbool.h>

// HC4051结构体定义
typedef struct
{
    void (*s0_pin)(bool level);  // 选择引脚S0
    void (*s1_pin)(bool level);  // 选择引脚S1
    void (*s2_pin)(bool level);  // 选择引脚S2
    void (*en_pin)(bool level);  // 使能引脚E

} hc4051_typeDef_t;

extern hc4051_typeDef_t HC4051_ic1;
extern hc4051_typeDef_t HC4051_ic2;
extern hc4051_typeDef_t HC4051_ic3;
extern hc4051_typeDef_t HC4051_ic4;
extern hc4051_typeDef_t HC4051_ic5;

// 函数声明
void hc4051_init(hc4051_typeDef_t* hc4051, void (*s0)(bool), void (*s1)(bool), void (*s2)(bool), void (*en)(bool));
void hc4051_selectChannel(hc4051_typeDef_t* hc4051, uint8_t channel);
void hc4051_enable(hc4051_typeDef_t* hc4051);
void hc4051_disable(hc4051_typeDef_t* hc4051);

#endif