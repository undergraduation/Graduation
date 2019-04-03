#ifndef	__PID_H__
#define	__PID_H__ 

#include "stm32f1xx_hal.h"

#define SGN(x) (((x) >= 0) ? 1 : -1)
#define ABS(x) (((x) >= 0)? (x) : -(x))

typedef struct PID_Regulator_t PID_Regulator_t;

typedef enum PID_type
{
	positional,
	increment,
}PID_type;

float set_fdb(PID_Regulator_t *pid, float fdb);
float get_fdb(PID_Regulator_t *pid);
float set_ref(PID_Regulator_t *pid, float ref);
float get_ref(PID_Regulator_t *pid);
float get_output(PID_Regulator_t *pid);
void PID_Calc(PID_Regulator_t *pid, float ref, float fdb);
void PID_Init(PID_Regulator_t *pid,float kp,float ki,float kd,float componentKiMax,float outputMax,PID_type type);

#endif
