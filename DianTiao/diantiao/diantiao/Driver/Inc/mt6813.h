#ifndef   __MT6813_H__
#define   __MT6813_H__ 
#include "sys.h"

#define MT6813_ADDR    0x06
#define MT6813_ID      0x06
#define MT6813_REG1    0x03
#define MT6813_REG2    0x04

u8 MT6813_init(void);
u8 MT6813_Write_Byte(u8 addr, u8 reg, u8 data);
u8 MT6813_Read_Byte(u8 addr, u8 reg);
float MT6813_Get_Angle(void);

#endif
