

#define F_CPU 8000000UL									/* Define CPU clock Frequency e.g. here its 8MHz */
#include <util/delay.h>									/* Include delay header file */
#include <inttypes.h>									/* Include integer type header file */
#include <stdlib.h>										/* Include standard library file */
#include <stdio.h>										/* Include standard library file */
#include "UART_interface.h"							/* Include USART header file */
#include "MPU_6050_interface.h"
#include <math.h>
#define sign(x) (x > 0) ? 1 : ((x < 0) ? -1 : 0)
#define lamda 0.01
#define PI 3.14159265
#define reading_count 1000
#define delta 0.01

extern float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;
float Pitch_res,Roll_res;
float Pitch,Roll;
double dt;
double gyroXangle=0;
double compAngleX=0;
float abs_Xa,abs_Ya,abs_Za;
void timer1_init()
{
    // set up timer with prescaler = 8
    TCCR1B |= (1 << CS11);
  
    // initialize counter
    TCNT1 = 0;
  
    
}
float Q_angle  =  0.1; //0.001
float Q_gyro   =  0.3;  //0.003
float R_angle  =  0.1;  //0.03

float x_bias = 0;
float P_00 = 0, P_01 = 0, P_10 = 0, P_11 = 0;
float  y, S;
float K_0, K_1;


float x_angle;
// newAngle = angle measured with atan2 using the accelerometer
// newRate = angle measured using the gyro
// looptime = loop time in millis()

float kalmanCalculate(float newAngle, float newRate,float looptime)
{
float dt = (looptime);
x_angle += dt * (newRate - x_bias);
P_00 +=  - dt * (P_10 + P_01) + Q_angle * dt;
P_01 +=  - dt * P_11;
P_10 +=  - dt * P_11;
P_11 +=  + Q_gyro * dt;

y = newAngle - x_angle;
S = P_00 + R_angle;
K_0 = P_00 / S;
K_1 = P_10 / S;

x_angle +=  K_0 * y;
x_bias  +=  K_1 * y;
P_00 -= K_0 * P_00;
P_01 -= K_0 * P_01;
P_10 -= K_1 * P_00;
P_11 -= K_1 * P_01;

return x_angle;
}  
char flag=0;
int main()
{int count;
 /*float inst_Pitch,inst_Roll;
 double sum_Pitch;
 double sum_Roll;
 float angle=0;
 float gero_z; */
	char buffer[20], float_[10];
	float Xa,Ya,Za,t;
	float Xg=0,Yg=0,Zg=0;
	I2C_Init();											/* Initialize I2C */
	MPU6050_Init();										/* Initialize MPU6050 */
	USART_Init(9600);									/* Initialize USART with 9600 baud rate */
	
    timer1_init();

while(1){


Read_RawValue();

		Xa = Acc_x/16384.0;								/* Divide raw value by sensitivity scale factor to get real values */
		Ya = Acc_y/16384.0;
		Za = Acc_z/16384.0;
	
		Xg = Gyro_x/16.4+2.3;
		Yg = Gyro_y/16.4-2.2;
		Zg = Gyro_z/16.4+1;

		t = (Temperature/340.00)+36.53;					/* Convert temperature in °/c using formula */

        dt=(double)TCNT1*1.0/1000000.0;
        TCNT1=0;

        // dtostrf( Xg, 6, 2, float_ );					 Take values in buffer to send all parameters over USART 
		// sprintf(buffer," X_gyro = %s%c\r\n",float_,0xF8);
		// USART_SendString(buffer);
        //Za=0.5;
        
        


       if(Za<0.00){
        abs_Za=-1.00*Za;

       }else{
       	abs_Za=Za;
       }
       if(Xa<0.00){
        abs_Xa=-1.00*Xa;

       }else{
       	abs_Xa=Xa;
       }
       if(Ya<0.00){
        abs_Ya=-1.00*Ya;

       }else{
       	abs_Ya=Ya;
       }
        if((int)((abs_Za)*1000)<2 )
        	continue;
        if((int)((abs_Ya)*1000)<9  )
        	continue;
        if((int)((abs_Xa)*1000)<9  )
        	continue;
        

       
       /* if((int)((Za)*1000)<2 ||(int)((Za)*1000)<-2 )
        	continue;
        if((int)((Ya)*-1000)<9 ||(int)((Za)*100)<-1 )
        	continue;
        if((int)((Xa)*-1000)<9 ||(int)((Za)*100)<-1 )
        	continue;
        
       */

        Roll = atan2(Ya,Za) * 180/PI;
        Pitch = atan2(-Xa ,sqrt(Ya*Ya + Za*Za)) * 180/PI;


        Roll_res=atan2(Ya,sign(Za)*sqrt(Za*Za+lamda*Xa*Xa))* 180/PI;
        Pitch_res = atan2(-Xa ,sqrt(Ya*Ya + Za*Za)) * 180/PI;
        
        // int roll=Roll;
        // if(roll >100)
        // 	Roll=0;
        	//continue;
        float kalx;
        if(flag==0)
        {//x_angle=Roll;
         kalx=kalmanCalculate(0,Xg,dt);

        flag=1;
        }
        else
        kalx=kalmanCalculate(Roll,Xg,dt);
       // kalx=kalx-30;

  //       dtostrf( Roll, 3, 2, float_ );					/* Take values in buffer to send all parameters over USART */
		// sprintf(buffer," Roll = %s g\t",float_);
		// USART_SendString(buffer);


  //       dtostrf( Xg, 3, 4, float_ );					/* Take values in buffer to send all parameters over USART */
		// sprintf(buffer," gx = %s g\t",float_);
		// USART_SendString(buffer);

		// dtostrf( Yg, 3, 4, float_ );
		// sprintf(buffer," gy = %s g\t",float_);
		// USART_SendString(buffer);
		
		// dtostrf( Zg, 3, 4, float_ );
		// sprintf(buffer," gz = %s g\r\n",float_);
		// USART_SendString(buffer);
    
    /**********************************complementary_filter*****************************************/

     /*    // gyroXangle += (Xg-4) * dt; // Calculate gyro angle without any filter
         // compAngleX = 0.93 * (compAngleX + (Xg-4) * dt) + 0.07 * Roll; // Calculate the angle using a Complimentary filter


  //       dtostrf( Pitch, 6, 2, float_ );					 Take values in buffer to send all parameters over USART 
		// sprintf(buffer," Pitch = %s%c\t",float_,0xF8);
		// USART_SendString(buffer);
        */
       
/**********************************************************************************/

        dtostrf( Roll_res, 6, 2, float_ );					/* Take values in buffer to send all parameters over USART */
		sprintf(buffer," Roll_res = %s%c\t",float_,0xF8);
		USART_SendString(buffer);       
        
        dtostrf( Roll, 6, 2, float_ );					/* Take values in buffer to send all parameters over USART */
		sprintf(buffer," Roll = %s%c\t",float_,0xF8);
		USART_SendString(buffer);       
        
        dtostrf( Xg, 6, 4, float_ );					/* Take values in buffer to send all parameters over USART */
		sprintf(buffer," Xg = %s%c\t",float_,'S');
		USART_SendString(buffer);  

		dtostrf( kalx, 6, 4, float_ );					/* Take values in buffer to send all parameters over USART */
		sprintf(buffer," kalx = %s%c\r\n",float_,'S');
		USART_SendString(buffer); 
 }
}	













/*******************************************extra****************************************************************************************/






// 	while(1)
// 	 {	//USART_TxChar('X');
// sum_Roll=0;
// sum_Pitch=0;
// for(count=0;count<reading_count;count++)
// {	Read_RawValue();

// 		Xa = Acc_x/16384.0;								/* Divide raw value by sensitivity scale factor to get real values */
// 		Ya = Acc_y/16384.0;
// 		Za = Acc_z/16384.0;
		
// 		Xg = Gyro_x/16.4;
// 		Yg = Gyro_y/16.4;
// 		Zg = Gyro_z/16.4;

// 		t = (Temperature/340.00)+36.53;					/* Convert temperature in °/c using formula */

// /************************************************************************************************************************/

// 		// dtostrf( Xa, 3, 2, float_ );					/* Take values in buffer to send all parameters over USART */
// 		// sprintf(buffer," Ax = %s g\t",float_);
// 		// USART_SendString(buffer);

// 		// dtostrf( Ya, 3, 2, float_ );
// 		// sprintf(buffer," Ay = %s g\t",float_);
// 		// USART_SendString(buffer);
		
// 		// dtostrf( Za, 3, 2, float_ );
// 		// sprintf(buffer," Az = %s g\t",float_);
// 		// USART_SendString(buffer);

// 		// dtostrf( t, 3, 2, float_ );
// 		// sprintf(buffer," T = %s%cC\t",float_,0xF8);           /* 0xF8 Ascii value of degree '°' on serial */
// 		// USART_SendString(buffer);

// 		// dtostrf( Xg, 3, 2, float_ );
// 		// sprintf(buffer," Gx = %s%c/s\t",float_,0xF8);
// 		// USART_SendString(buffer);

// 		// dtostrf( Yg, 3, 2, float_ );
// 		// sprintf(buffer," Gy = %s%c/s\t",float_,0xF8);
// 		// USART_SendString(buffer);
		
// 		// dtostrf( Zg, 3, 2, float_ );
// 		// sprintf(buffer," Gz = %s%c/s\r\n",float_,0xF8);
// 		// USART_SendString(buffer);



// 		// dtostrf( Xa, 3, 2, float_ );					/* Take values in buffer to send all parameters over USART */
// 		// sprintf(buffer," Ax = %s g\t",float_);
// 		// USART_SendString(buffer);

// 		// dtostrf( Ya, 3, 2, float_ );
// 		// sprintf(buffer," Ay = %s g\t",float_);
// 		// USART_SendString(buffer);

// 		// dtostrf( Za, 3, 2, float_ );
// 		// sprintf(buffer," Az = %s g\t",float_);
// 		// USART_SendString(buffer);

		
// 		// Yaw=atan((Ya/Xa)*180.0 / PI);
//   //       Pitch=(atan(Za/Ya)*180.0 / PI);
//   //       Roll=(atan(Xa/Za)*180.0 / PI);
// 		//Yaw=120.00;

//   //       dtostrf( Yaw, 6, 2, float_ );					 Take values in buffer to send all parameters over USART 
// 		// sprintf(buffer," Yaw = %s%c/s\r\n",float_,0xF8);
// 		// USART_SendString(buffer);

// /**************************************************************************************************************************************/




// //Roll = atan(Ya/Za) * 180/PI;
// //Pitch = atan(-Xa /sqrt(Ya*Ya + Za*Za)) * 180/PI;
// inst_Roll=atan2(Ya,sign(Za)*sqrt(Za*Za+lamda*Xa*Xa))* 180/PI;
// inst_Pitch = atan2(-Xa ,sqrt(Ya*Ya + Za*Za)) * 180/PI;
// sum_Roll+=inst_Roll;
// sum_Pitch+=inst_Pitch;        
// }

// Roll=sum_Roll/reading_count;
// Pitch=sum_Pitch/reading_count;

//         dtostrf( Pitch, 6, 2, float_ );					/* Take values in buffer to send all parameters over USART */
// 		sprintf(buffer," Pitch = %s%c\t",float_,0xF8);
// 		USART_SendString(buffer);
        
//         dtostrf( Roll, 6, 2, float_ );					/* Take values in buffer to send all parameters over USART */
// 		sprintf(buffer," Roll = %s%c\r\n",float_,0xF8);
// 		USART_SendString(buffer);       

// 	}
// }
