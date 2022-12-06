#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define PEOPLE 5   // 1 == 시민1 // 2 == 시민2 // 3 == 마피아 // 4 == 경찰 // 5 == 의사

int main(void){
    /*게임 시작*/
    while(1){
    int start;
    printf("Press 1 to Start\r\n");
    scanf("%d", &start);
    if (start == 1){
        break;
    }
    }
    
    /*직업 할당*/
    int job[PEOPLE];
    int i, j;   //앞으로 많이 쓸거임
    srand((unsigned)time(NULL));
    for (i=0; i<PEOPLE; i++){
        job[i] = (rand()%5) + 1;
        for (j=0; j<i; j++){
            if (job[i] == job[j]) i--;
        }
    }
    printf("직업 할당 : \r\n");
    for (i=1; i<PEOPLE+1; i++){
        if(job[i] == 1 || job[i] == 2){
            printf("%d번 플레이어\r\n", i);
            printf("당신은 시민입니다.\r\n");
        }
        else if(job[i] == 3){
            printf("%d번 플레이어\r\n", i);
            printf("당신은 마피아입니다.\r\n");
        }
        else if(job[i] == 4){
            printf("%d번 플레이어\r\n", i);
            printf("당신은 경찰입니다.\r\n");
        }
        else if(job[i] == 5){
            printf("%d번 플레이어\r\n", i);
            printf("당신은 의사입니다.\r\n");
        }
    }
    /*버튼 입력을 받아*/
    char player_btn[PEOPLE+1];

    /*기울기 함수까지 구현*/

    /*사람 별로 이미지와 직업 함수를 출력, 다시 내려놓으면 처음으로 돌아가야함*/

    /*게임 진행*/
    int count = 0;
    int vote;
    int dead[4];
    int dead_cnt = 0;
    int night_people;
    int kill, search, heal;
    while(1){
    while(1){
    //낮 이미지 출력하고 60초를 기다림. segment로 60초 카운트하고 10초 남았을 때 부터 1초간격으로 buzzer
        /*while(1){
        if(count != 5){
            printf("count = %d\r\n", count);
            count++;
            sleep(1);
        }
        else if(count == 5){
            break;
        }
        }*/
        /*투표 시퀀스*/
        count = 0;
        printf("누구를 투표하시겠습니까?\r\n");
        /*여기서 투표를 받을 거임*/ //투표 여러번 해야됨
        //모두 투표 완료되면 break
        scanf("%d", &vote);
        printf("플레이어 %d가 투표되었습니다\r\n", vote);
        if(job[vote] == 3){
            printf("플레이어 %d는 마피아입니다!\r\n", vote);
            printf("시민 승리\r\n");
            exit(0);
        }
        else{
            printf("플레이어 %d는 마피아가 아닙니다.\r\n", vote);
            dead[vote] = 1;  //dead[사람 번호] = 1이면 죽은거임
            dead_cnt++;
        }
    //밤 이미지 출력함
    while(1){
        for(i=1; i<PEOPLE-dead_cnt+1; i++){
        printf("본인의 번호를 선택하세요\r\n");
        scanf("%d", &night_people);
        printf("키트를 기울이세요\r\n");
        //기울이는거 추가해야함
        if(job[night_people] == 3 && dead[night_people] != 1){
            printf("누구를 죽이겠습니까?\r\n");
            scanf("%d", &kill);
            printf("플레이어 %d를 죽입니다.\r\n", kill);
        }
        else if(job[night_people] == 4 && dead[night_people] != 1){
            printf("누구를 확인하겠습니까?\r\n");
            scanf("%d", &search);
            if(job[search] == 3){
                printf("플레이어 %d는 마피아입니다!\r\n", search);
            }
            else{
                printf("플레이어 %d는 마피아가 아닙니다..\r\n", search);
            }
        }
        else if(job[night_people] == 5 && dead[night_people] != 1){
            printf("누구를 살리겠습니까?\r\n");
            scanf("%d", &heal);
            printf("플레이어 %d를 살립니다\r\n", heal);
        }
        else if(job[night_people] == 1 || job[night_people] == 2){
            printf("아무 사람의 버튼을 누르세요\r\n");
            scanf("%d", &j);
            j = 0;
        }
        else{
            printf("그런 사람 없습니다\r\n");
            i--;
        }
        }
        /*밤에 한 선택에 따라 계산됨*/
        if(kill != heal){
            dead[kill] = 1;
            printf("player %d is dead\r\n", kill);
            dead_cnt++;
        }
        else if(kill == heal){
            printf("doctor saved a life\r\n");
        }

        if(job[kill] == 3 && dead[kill] == 1){
            printf("mafia dead\r\n");
            exit(0);
        }

    
        break;
    }

    }
}



    return 0;
}