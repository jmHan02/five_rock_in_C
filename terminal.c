#include "terminal.h"
#include <stdio.h>

#define FIND_REFILL_CHARACTER switch (board[(*cursor_x-1)/2][*cursor_y-1]) \
{   \
    case 32: \
        refill_character = 32; \
        break; \
    case 79: \
        refill_character = 79; \
        break; \
    case 88:\
        refill_character = 88;\
        break; \
};
#define RESET_COLOR printf("\033[0m%c\033[%d;%dH",board[(*cursor_x-1)/2][(*cursor_y)-1],*cursor_y,*cursor_x);
#define SET_COLOR printf("\033[%d;%dH\033[42m%c\033[%d;%dH",*cursor_y,*cursor_x,refill_character,*cursor_y,*cursor_x);

extern char board[16][16];
int getch(void){
    int ch;
    
    ch = getchar();
    
    
    return ch;
}

int cursor_move(int *cursor_x, int *cursor_y){
    
    int first_input=0;
    int second_input=0;
    int third_input=0;
    int refill_character=32;
    first_input = getch();

    if(first_input == 27){
        second_input = getch();
        if(second_input == 91){
            third_input = getch();
            switch (third_input)
            {
            case 'A':        
                if(*cursor_y -1 >= 2){
                    RESET_COLOR
                    fflush(stdout);
                    (*cursor_y)--;
                    FIND_REFILL_CHARACTER
                    SET_COLOR
                    fflush(stdout);
                    return 0;

                }   
                break;
            case 'B':                
                if(*cursor_y + 1 <= 16){
                    RESET_COLOR
                    fflush(stdout);
                    (*cursor_y)++;
                    FIND_REFILL_CHARACTER
                    SET_COLOR
                    fflush(stdout);
                    return 0;
                }   
                break;
            case 'C':
                if(*cursor_x + 2 <= 31){
                    RESET_COLOR
                    fflush(stdout);
                    *cursor_x=*cursor_x+2;
                    FIND_REFILL_CHARACTER
                    SET_COLOR
                    fflush(stdout);
                    return 0;
                }   
                break;
            case 'D':
            if(*cursor_x - 2 >= 3){
                    RESET_COLOR
                    fflush(stdout);
                    *cursor_x = *cursor_x - 2;
                    FIND_REFILL_CHARACTER
                    SET_COLOR
                    fflush(stdout);
                    return 0;
                }   
                break;
            
            // \033 [ 까지 입력받았지만 이후 이상한게 들어왔을 때, 버퍼 삭제 후 return 0;
            default:
                tcflush(0, TCIFLUSH);
                return 0;
                
            }
            tcflush(0,TCIFLUSH);
            return 0;
        }else{
            // \033 까지 입력받았지만 이후 이상한게 들어왔을 때, 버퍼 삭제 후 return 0;
            tcflush(0, TCIFLUSH);
            return 0;
        }
    }else if(first_input == 10){
        //엔터 입력했을때 버퍼 비우고 1반환
        tcflush(0,TCIFLUSH);
        return 1;    
    }else{
        //이상한 입력 했을때 버퍼 비우고 0 반환
        tcflush(0,TCIFLUSH);
        return 0;
    }
    


    
}
