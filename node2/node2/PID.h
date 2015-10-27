/*
 * PID.h
 *
 * Created: 15.10.2015 09:51:08
 *  Author: andreabm
 */ 


#ifndef PID_H_
#define PID_H_

//Only allows ms between 1 and 16 with 1 byte counter register on timer 2
void init_PID(double kp, double ki, double kd, double ms);
double controllSignal();
void pid(double error);
void set_pid_reference(int ref);

#endif /* PID_H_ */
