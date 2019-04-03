#ifndef 	__MCP4725_H__
#define   __MCP4725_H__ 
#include "sys.h"

void MCP4725_ReadData(void);
void MCP4725_Init(void);
void MCP4725_WriteVelData_Voltage(u16 Vout);
void MCP4725_WriteBreakData_Voltage(u16 Vout);
#endif
