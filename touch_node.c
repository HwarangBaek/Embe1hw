#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <linux/input.h>
#include <unistd.h>
#include <sys/time.h>


#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "textlcddrv.h"
#include "textlcd.h"
#include "fnddrv.h"
#include <linux/input.h>



struct timeval Tend;





int returnValue_touch = 0; 


int x_point,y_point;



int getElapsedTime_touch(struct timeval Tstart, struct timeval Tend, int clock, int score, int mode)
{
   
int s;

       Tend.tv_usec = Tend.tv_usec - Tstart.tv_usec;
       Tend.tv_sec  = Tend.tv_sec - Tstart.tv_sec;
       Tend.tv_usec += (Tend.tv_sec*1000000);
        

       printf("Elapsed Time: %lf sec\n", Tend.tv_usec / 1000000.0);



if(mode == 1){

         if ((Tend.tv_usec / 1000000.0) <= 0.01*clock*0.5){
           lcdtextWrite("Perfect             ","                        ");
           score=score+10 ; 
           fndDisp(score,0);

           s = 0.01*clock*1000000-Tend.tv_usec ;
           usleep(s);

           }
           else if( (Tend.tv_usec / 1000000.0)>0.01*clock*0.5&&(Tend.tv_usec / 1000000.0)<=0.01*clock*0.9)
           {
               lcdtextWrite("Good    ","                        ");
               score=score+5 ;
               fndDisp(score,0);

               s = 0.01*clock*1000000-Tend.tv_usec ;
               usleep(s);
               }
               else if ((Tend.tv_usec / 1000000.0) > 0.01*clock*0.9 )
               {
                   lcdtextWrite("Miss","                    ");
                   score=score+0 ;
                   fndDisp(score,0);
                         
                }


}
else{

         if ((Tend.tv_usec / 1000000.0) <= 0.01*clock*0.5){
           lcdtextWrite("Miss","                    ");
           score=score+0 ; 
           fndDisp(score,0);

           s = 0.01*clock*1000000-Tend.tv_usec ;
           usleep(s);

           }
           else if( (Tend.tv_usec / 1000000.0)>0.01*clock*0.5&&(Tend.tv_usec / 1000000.0)<=0.01*clock*0.9)
           {
               lcdtextWrite("Miss","                    ");
               score=score+0 ;
               fndDisp(score,0);

               s = 0.01*clock*1000000-Tend.tv_usec ;
               usleep(s);
               }
               else if ((Tend.tv_usec / 1000000.0) > 0.01*clock*0.9 )
               {
                   lcdtextWrite("Miss","                    ");
                   score=score+0 ;
                   fndDisp(score,0);
                         
                }

}

      
            
 Tend.tv_usec=0;

 return score;
}



void touch_node_Init(void)
{

   if (heartbeatInit() == 0)
   {
      printf ("heartbeat init Failed!\r\n");
      return 0;
   }

   if (touchscreenInit() == 0)
   {
      printf ("touchscreen init Failed!\r\n");
      return 0;
   }
  
  return 1;
              
}


int check_touch_node(int x_low,int x_high,int y_low,int y_high,struct timeval Tstart,int usec,int now_score)
{
   int no_input_next=0;
   int key_input_next=0;

   int messageID = msgget (MESSAGE_ID, IPC_CREAT|0666);   //To Receive Message from Library.
       BUTTON_MSG_T rxMsg;

  // usec 
   int ready_x = 0;
   int ready_y = 0;
   int clocknum = usec/10000;

   int clean=0;
   int clock=0;

   int score = now_score;
   
    while( no_input_next != 1 && key_input_next != 1) {

               while (clean != 1) //메세지비우기 
                           {
                  returnValue_touch  = msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int), 0, IPC_NOWAIT); 
                  if (returnValue_touch == -1) clean = 1;
                            }
          
                  msgrcv(messageID, &rxMsg, sizeof(rxMsg) - sizeof(long int),0 ,0);

                  if (rxMsg.messageNum >= 3){

                  if (rxMsg.messageNum == 3)  {

                      x_point = rxMsg.keyInput;
                      printf("X: %d\n",x_point);

                      if(x_low <= x_point && x_high >= x_point) { ready_x =1;  }

                                             }

                  else if (rxMsg.messageNum == 4) {

                      y_point = rxMsg.pressed;
                      printf("Y: %d\n",y_point);

                      if(y_low <= y_point && y_high >= y_point) {  
                                                                   if(ready_x ==1) { 
                                                                      printf("correct \n");
                                                                      gettimeofday(&Tend, NULL);   // 현재시간 구하기(측정할 소스부분 수행 후에 사용)
                                                                      score = getElapsedTime_touch(Tstart, Tend,clocknum,now_score,1);   // 정의된 함수로 시간 구하기
                                                                      key_input_next = 1;
                                                                                                                                            }
                                                                   else { 
                                                                      printf("non correct \n");
                                                                      gettimeofday(&Tend, NULL);   // 현재시간 구하기(측정할 소스부분 수행 후에 사용)
                                                                      score = getElapsedTime_touch(Tstart, Tend,clocknum,now_score,0);   // 정의된 함수로 시간 구하기
                                                                      key_input_next = 1;
                                                                                                                                            }
                                                                                                                                  }
                      else{
                           printf("non correct \n");
                           gettimeofday(&Tend, NULL);   // 현재시간 구하기(측정할 소스부분 수행 후에 사용)
                           score = getElapsedTime_touch(Tstart, Tend,clocknum,now_score,0);   // 정의된 함수로 시간 구하기
                           key_input_next = 1;
                                                     }


                                             }


                                        }



                  else{ 
                          if  (clock == clocknum ) {   // 터치입력없이 음 지속 경우 
                                                   clock = 0 ; 
                                                   lcdtextWrite("Miss","                        "); 
                                                   fndDisp(score,0);
                                                   now_score=now_score+0; 
                                                   printf("no touch\n"); 
                                                   no_input_next = 1;
                                                                                              }

                           else { clock = clock + 1 ;  }
                                                }
                  
}


   return score;
}

