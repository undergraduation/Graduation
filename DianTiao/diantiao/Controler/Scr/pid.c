#include "pid.h"

struct PID_Regulator_t
{
	/* data */
	float ref;//给定值
	float fdb;//反馈值
	float inte;//位置式的积分项
	float err[3];
	float kp;
	float ki;
	float kd;

	float componentKiMax;//位置式的积分限幅
	float outputMax;//输出限幅
	float output;//输出
	
	PID_type type;//增量式或位置式
};

float set_fdb(PID_Regulator_t *pid, float fdb)
{
	float temp = pid->fdb;
	pid->fdb = fdb;
	return temp;
}

float get_fdb(PID_Regulator_t *pid)
{
	return pid->fdb;
}

float set_ref(PID_Regulator_t *pid, float ref)
{
	float temp = pid->ref;
	pid->ref = ref;
	return temp;
}

float get_ref(PID_Regulator_t *pid)
{
	return pid->ref;
}

float get_output(PID_Regulator_t *pid)
{
	return pid->output;
}

void PID_Calc(PID_Regulator_t *pid, float ref, float fdb)
{
	pid->ref = ref;
	pid->fdb = fdb;
	//位置式
	if (pid->type == positional)
	{
		pid->err[1] = pid->err[0];
		pid->err[0] = pid->ref - pid->fdb;
		pid->inte += pid->err[0] * pid->ki;

		if(pid->inte > pid->componentKiMax)//积分限幅
			pid->inte = pid->componentKiMax;
		else if (pid->inte < -pid->componentKiMax)
			pid->inte = -pid->componentKiMax;

		pid->output = (
					   pid->err[0] * pid->kp					//P
					 + pid->inte								//I
					 + (pid->err[0] - pid->err[1]) * pid->kd	//D
					  );
	}
	else	
	//增量式
	{
		pid->err[2] = pid->err[1];
		pid->err[1] = pid->err[0];
		pid->err[0] = pid->ref - pid->fdb;

		pid->output += (
						(pid->err[0] - pid->err[1]) * pid->kp
					  + (pid->err[0]) * pid->ki
					  + (pid->err[0] - 2 * pid->err[1] + pid->err[2]) * pid->kd
					   );
	}
	//输出限幅
	if(pid->output > pid->outputMax)
		pid->output = pid->outputMax;
	else if (pid->output < -pid->outputMax)
		pid->output = -pid->outputMax;	
}

void PID_Init(PID_Regulator_t *pid,float kp,float ki,float kd,float componentKiMax,float outputMax,PID_type type)
{
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	pid->inte = 0;
	pid->err[0] = 0;
	pid->err[1] = 0;
	pid->err[2] = 0;
	pid->componentKiMax = componentKiMax;
	pid->outputMax = outputMax;
	pid->type = type;
}


