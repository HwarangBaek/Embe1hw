//practice
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/ioctl.h> 
#include <sys/msg.h>
#include <pthread.h>
#include <time.h>


#include "button.h"
#include "game_slope.h"
#include "accelMagGyro.h"
#include "led.h"
#include "fnd.h"


int init_game(void);
//void tilt_evrything(void);


#define PEOPLE 5   // 1 == 시민1 // 2 == 시민2 // 3 == 마피아 // 4 == 경찰 // 5 == 의사




int job[6];
int dead[6];   //0이면 생존, 1이면 사망
int doctor[6];
int voted[6];
int player[6];



int tilt_x, tilt_y, tilt_z;
int i, j, num, a;
int dead_cnt;

int people_job_check_1 = 0;
int people_job_check_2 = 0;
int people_job_check_3 = 0;
int people_job_check_4 = 0;
int people_job_check_5 = 0;




int main(void)
{   //===== 1번 버튼을 누르면 게임 시작 =====//
   printf("====== #TFT LCD : 1. mainscreen ====== \n");
   printf("====== #TEXT LCD : 1 : Press 1 to start ====== \n");
   //===== 버튼 설정 : 초기화=====//
   BUTTON_MSG_T rcv;
   int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);


   buttonInit();
   ledLibInit();
   //===== 버튼 설정 : Home(1)버튼을 누르면 while문을 벗어난다=====//
   
   while (1) {
      
      msgrcv(msgID,&rcv.keyInput,sizeof(rcv.keyInput),0,0);
      printf("*****%d*****\n",rcv.keyInput);
      printf("msgrcv pass !!\n");
      
       if(rcv.keyInput==1) break;
      //break;
   }
  

   printf("#TFT LCD : 2_1.loading \n");
   printf("#TEXT LCD : 1 : loading.. \n");
   sleep(1);
   printf("#TFT LCD : 2_2.loading  \n");
   printf("#TEXT LCD : 1 : loading.... \n");
   sleep(1);
   printf("#TFT LCD : 2_3.loading  \n");
   printf("#TEXT LCD : 1 : loading......  \n");
   sleep(1);




   //===== 게임 시작 =====//
   while (1)
   {
      // ==== 게임 함수 ==== //
      init_game();
   }

   buttonExit();
   ledLibExit();
   //fndexit();
   return 0;
}// ==========================================================게임 함수 ========================================================================//



int init_game(void)
{
   
   //int tilt_x, tilt_y, tilt_z;
   //===== 버튼 설정 =====//
   BUTTON_MSG_T rcv;
   int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);

   

   
   //===== 난수로 직업 할당 =====//


   srand((unsigned)time(NULL));
   for (i = 1; i < PEOPLE + 1; i++) {
      job[i] = (rand() % 5) + 1;
      for (j = 0; j < i; j++) {
         if (job[i] == job[j]) i--;
      }
   }
   printf("job[1] = %d \n", job[1]); //5
   printf("job[2] = %d \n", job[2]); //4
   printf("job[3] = %d \n", job[3]); //3
   printf("job[4] = %d \n", job[4]); //2
   printf("job[5] = %d \n", job[5]); //1
   int a,b,c,d,e;

   job[1] =1;
   job[2] =2;
   job[3] =3;
   job[4] =4;
   job[5] =5;

   //counter_time(); // 여기서 끝나버린다.

   printf("====== #TFT LCD : 3. job_button ====== \n");
   printf("====== #TEXT LCD : 1 : Press the button ====== \n");

   
   printf("====== #Button_current : %d \n", rcv.keyInput);

   while ((people_job_check_1 & people_job_check_2 & people_job_check_3 & people_job_check_4 & people_job_check_5) != 1) {

      printf("key 입력 받을 준비!!\n");
      msgrcv(msgID, &rcv.keyInput, sizeof(rcv.keyInput), 0, 0);
      printf("====== #Button_current : %d \n", rcv.keyInput);

      switch (rcv.keyInput)
      {
      case 1: if(people_job_check_1 != 1){
         printf("====== #TFT LCD : 4. job_tilt ====== \n");
         printf("====== #TEXT LCD : 1 : tilt the kit ====== \n");
         printf("====== #Button : player_1 \n");
         
         

         while (1) {

            tilt_x = Accel_x_150();
            tilt_y = Accel_y_150();
            tilt_z = Accel_z_150();



            while ((((tilt_y < 10672) && (tilt_z > 12091)) || ((tilt_y > -10524) && (tilt_z > 12657)) || ((tilt_x < 9896) && (tilt_z > 12627)) || ((tilt_x > -10218) && (tilt_z > 12664))) == 1)
            {
               tilt_x = Accel_x_150();
               tilt_y = Accel_y_150();
               tilt_z = Accel_z_150();

            }

          if(job[1]==1)
          {
            ledOnOff(0,1);
            while (1) {
                  tilt_x = Accel_x_150();
                  tilt_y = Accel_y_150();
                  tilt_z = Accel_z_150();


                  if (((tilt_y <= -10524) && (tilt_z <= 12657) || (tilt_x >= 9896) && (tilt_z <= 12627)) == 1) {
                     printf("====== #TFT LCD : 5_1. you are citizn \n");
                     while ((((tilt_y < 10672) && (tilt_z > 12091)) || ((tilt_y > -10524) && (tilt_z > 12657)) || ((tilt_x < 9896) && (tilt_z > 12627)) || ((tilt_x > -10218) && (tilt_z > 12664))) != 1)
                     {
                        tilt_x = Accel_x_150();
                        tilt_y = Accel_y_150();
                        tilt_z = Accel_z_150();


                     }
                     printf("====== #LED : (1) LED ON\n");
                     people_job_check_1 = 1;
                     //break;
                  }

                  else if (((tilt_y >= 10672) && (tilt_z <= 12091) || (tilt_x <= -10218) && (tilt_z <= 12664)) == 1) {
                     printf("====== #TFT LCD : 5_1. you are citizn_Reverse \n");
                     while ((((tilt_y < 10672) && (tilt_z > 12091)) || ((tilt_y > -10524) && (tilt_z > 12657)) || ((tilt_x < 9896) && (tilt_z > 12627)) || ((tilt_x > -10218) && (tilt_z > 12664))) != 1)
                     {
                        tilt_x = Accel_x_150();
                        tilt_y = Accel_y_150();
                        tilt_z = Accel_z_150();

                     }
                     printf("====== #LED : (1) LED ON\n");
                     people_job_check_1 = 1;
                     break;
                  }
                  break;
               }
               
               job[1] +=1;
          }

          else if(job[2] == 2)
          {
            ledOnOff(0,0);
            ledOnOff(1,1);
            while (1) {
                  tilt_x = Accel_x_150();
                  tilt_y = Accel_y_150();
                  tilt_z = Accel_z_150();


                  if (((tilt_y <= -10524) && (tilt_z <= 12657) || (tilt_x >= 9896) && (tilt_z <= 12627)) == 1) {
                     printf("====== #TFT LCD : 5_2. you are mafia \n");
                     while ((((tilt_y < 10672) && (tilt_z > 12091)) || ((tilt_y > -10524) && (tilt_z > 12657)) || ((tilt_x < 9896) && (tilt_z > 12627)) || ((tilt_x > -10218) && (tilt_z > 12664))) != 1)
                     {
                        tilt_x = Accel_x_150();
                        tilt_y = Accel_y_150();
                        tilt_z = Accel_z_150();


                     }
                     printf("====== #LED : (1) LED ON\n");
                     people_job_check_1 = 1;
                     break;
                  }

                  else if (((tilt_y >= 10672) && (tilt_z <= 12091) || (tilt_x <= -10218) && (tilt_z <= 12664)) == 1) {
                     printf("====== #TFT LCD : 5_2. you are mafia_Reverse \n");
                     while ((((tilt_y < 10672) && (tilt_z > 12091)) || ((tilt_y > -10524) && (tilt_z > 12657)) || ((tilt_x < 9896) && (tilt_z > 12627)) || ((tilt_x > -10218) && (tilt_z > 12664))) != 1)
                     {
                        tilt_x = Accel_x_150();
                        tilt_y = Accel_y_150();
                        tilt_z = Accel_z_150();

                     }
                     printf("====== #LED : (1) LED ON\n");
                     people_job_check_1 = 1;
                     break;
                  }
                  break;
               }
               
               job[2]+=1;
          }

           else if(job[3] == 3)
           {
            ledOnOff(1,0);
            ledOnOff(2,1);
            while (1) {
                  tilt_x = Accel_x_150();
                  tilt_y = Accel_y_150();
                  tilt_z = Accel_z_150();


                  if (((tilt_y <= -10524) && (tilt_z <= 12657) || (tilt_x >= 9896) && (tilt_z <= 12627)) == 1) {
                     printf("====== #TFT LCD : 5_3. you are mafia \n");
                     while ((((tilt_y < 10672) && (tilt_z > 12091)) || ((tilt_y > -10524) && (tilt_z > 12657)) || ((tilt_x < 9896) && (tilt_z > 12627)) || ((tilt_x > -10218) && (tilt_z > 12664))) != 1)
                     {
                        tilt_x = Accel_x_150();
                        tilt_y = Accel_y_150();
                        tilt_z = Accel_z_150();


                     }
                     printf("====== #LED : (1) LED ON\n");
                     people_job_check_1 = 1;
                     break;
                  }

                  else if (((tilt_y >= 10672) && (tilt_z <= 12091) || (tilt_x <= -10218) && (tilt_z <= 12664)) == 1) {
                     printf("====== #TFT LCD : 5_3. you are mafia_Reverse \n");
                     while ((((tilt_y < 10672) && (tilt_z > 12091)) || ((tilt_y > -10524) && (tilt_z > 12657)) || ((tilt_x < 9896) && (tilt_z > 12627)) || ((tilt_x > -10218) && (tilt_z > 12664))) != 1)
                     {
                        tilt_x = Accel_x_150();
                        tilt_y = Accel_y_150();
                        tilt_z = Accel_z_150();

                     }
                     printf("====== #LED : (1) LED ON\n");
                     people_job_check_1 = 1;
                     break;
                  }
                  break;
               }
               
               job[3] +=1;
          }

          else if(job[4] == 4)
          {
            ledOnOff(2,0);
            ledOnOff(3,1);
            while (1) {
                  tilt_x = Accel_x_150();
                  tilt_y = Accel_y_150();
                  tilt_z = Accel_z_150();


                  if (((tilt_y <= -10524) && (tilt_z <= 12657) || (tilt_x >= 9896) && (tilt_z <= 12627)) == 1) {
                     printf("====== #TFT LCD : 5_4. you are police \n");
                     while ((((tilt_y < 10672) && (tilt_z > 12091)) || ((tilt_y > -10524) && (tilt_z > 12657)) || ((tilt_x < 9896) && (tilt_z > 12627)) || ((tilt_x > -10218) && (tilt_z > 12664))) != 1)
                     {
                        tilt_x = Accel_x_150();
                        tilt_y = Accel_y_150();
                        tilt_z = Accel_z_150();


                     }
                     printf("====== #LED : (1) LED ON\n");
                     people_job_check_1 = 1;
                     break;
                  }

                  else if (((tilt_y >= 10672) && (tilt_z <= 12091) || (tilt_x <= -10218) && (tilt_z <= 12664)) == 1) {
                     printf("====== #TFT LCD : 5_4. you are police_Reverse \n");
                     while ((((tilt_y < 10672) && (tilt_z > 12091)) || ((tilt_y > -10524) && (tilt_z > 12657)) || ((tilt_x < 9896) && (tilt_z > 12627)) || ((tilt_x > -10218) && (tilt_z > 12664))) != 1)
                     {
                        tilt_x = Accel_x_150();
                        tilt_y = Accel_y_150();
                        tilt_z = Accel_z_150();

                     }
                     printf("====== #LED : (1) LED ON\n");
                     people_job_check_1 = 1;
                     break;
                  }
                  break;
               }
               
               job[4] +=1;
          }

          else if(job[5]==5)
          {
            ledOnOff(3,0);
            ledOnOff(4,1);
            while (1) {
                  tilt_x = Accel_x_150();
                  tilt_y = Accel_y_150();
                  tilt_z = Accel_z_150();


                  if (((tilt_y <= -10524) && (tilt_z <= 12657) || (tilt_x >= 9896) && (tilt_z <= 12627)) == 1) {
                     printf("====== #TFT LCD : 5_5. you are doctor \n");
                     while ((((tilt_y < 10672) && (tilt_z > 12091)) || ((tilt_y > -10524) && (tilt_z > 12657)) || ((tilt_x < 9896) && (tilt_z > 12627)) || ((tilt_x > -10218) && (tilt_z > 12664))) != 1)
                     {
                        tilt_x = Accel_x_150();
                        tilt_y = Accel_y_150();
                        tilt_z = Accel_z_150();


                     }
                     printf("====== #LED : (1) LED ON\n");
                     people_job_check_1 = 1;
                     break;
                  }

                  else if (((tilt_y >= 10672) && (tilt_z <= 12091) || (tilt_x <= -10218) && (tilt_z <= 12664)) == 1) {
                     printf("====== #TFT LCD : 5_5. you are doctor_Reverse \n");
                     while ((((tilt_y < 10672) && (tilt_z > 12091)) || ((tilt_y > -10524) && (tilt_z > 12657)) || ((tilt_x < 9896) && (tilt_z > 12627)) || ((tilt_x > -10218) && (tilt_z > 12664))) != 1)
                     {
                        tilt_x = Accel_x_150();
                        tilt_y = Accel_y_150();
                        tilt_z = Accel_z_150();

                     }
                     printf("====== #LED : (1) LED ON\n");
                     people_job_check_1 = 1;
                     break;
                  }
                  break;
               }
               

               job[5] +=1;
               ledOnOff(4,0);

          }

          else { // 여기에 안들어감.
               ledOnOff(4,1); break;
          } 



          
         } 

         


      }





   case 2: printf("투표 시작 !!!\n");



      }
      
   }



}