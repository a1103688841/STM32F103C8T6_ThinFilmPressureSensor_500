#include "HC4051.h"

hc4051_typeDef_t HC4051_ic1;
hc4051_typeDef_t HC4051_ic2;
hc4051_typeDef_t HC4051_ic3;
hc4051_typeDef_t HC4051_ic4;
hc4051_typeDef_t HC4051_ic5;

// 初始化HC4051
void hc4051_init(hc4051_typeDef_t* hc4051, void (*s0)(bool), void (*s1)(bool), void (*s2)(bool), void (*en)(bool))
{
    hc4051->s0_pin = s0;
    hc4051->s1_pin = s1;
    hc4051->s2_pin = s2;
    hc4051->en_pin = en;
}

// 选择通道
void hc4051_selectChannel(hc4051_typeDef_t* hc4051, uint8_t channel)
{
    // 确保通道号在有效范围内
    channel = channel & 0x07;  // 限制在0-7之间

    // 设置选择引脚
    hc4051->s0_pin((channel & 0x01) ? true : false);
    hc4051->s1_pin(((channel >> 1) & 0x01) ? true : false);
    hc4051->s2_pin(((channel >> 2) & 0x01) ? true : false);
}

// 使能芯片
void hc4051_enable(hc4051_typeDef_t* hc4051)
{
    if (hc4051->en_pin)
    {
        hc4051->en_pin(false);  // 低电平有效
    }
}

// 失能芯片
void hc4051_disable(hc4051_typeDef_t* hc4051)
{
    if (hc4051->en_pin)
    {
        hc4051->en_pin(true);
    }
}