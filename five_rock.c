#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "utility.h"
#include "terminal.h"

//컴파일러는 컴파일하다가 모르는 함수가 나오면 일단 int 반환 함수로 생각하기 때문에 사실 int 반환 함수가 아니었다면 충돌이 남
bool is_win(bool turn, int x, int y, char board[16][16]);
char board[16][16];
int main(){
    #pragma region [보드 초기화]
    // int x=0; int y=0; // 키보드 입력값
    
    bool turn = true;
    int k= 10;
    int cursor_x=17; int cursor_y=9;
    int x=0; int y=0;
    int selected = 0;

    struct termios oldt,newt;
    tcgetattr(0,&oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON|ECHO );
    tcsetattr(0, TCSANOW, &newt);    
    
    

    //보드를 공백문자로 초기화
    for(int i=0;i<16; i++){
        for(int j=0; j<16; j++){
            board[i][j]=' ';            
        }        
    }
    //보드 행렬 인덱스 대입
    for(int i=1;i<10;i++){
        board[0][i]=i+'0';
        board[i][0]=i+'0';
    }
    for(int i='A';i<'G';i++){
        board[0][k]=i;
        board[k][0]=i;
        k++;
    }
    board[0][0]='\\';
    #pragma endregion

    printf("\033[?25l"); // 커서 숨김
    fflush(stdout);

    CLEAR_SCREEN(); 

    //화면 출력(처음에만)
    for(int i=0;i<16; i++){

        for(int j=0; j<16; j++){
            printf("%c ", board[i][j]);            
        }
        printf("\n");
    }
    fflush(stdout);
    


    while(true){

    cursor_x = 17;
    cursor_y = 9;
    printf("\033[%d;%dH\033[42m%c\033[%d;%dH",9,17,board[8][8],9,17);
    //cursor_move()반복호출
    while(selected == 0){    
    selected = cursor_move(&cursor_x,&cursor_y);
    }
    //선택된 커서 좌표를 보드배열좌표로 변환
    y = cursor_y - 1;
    x = (cursor_x-1)/2;
    selected = 0;
    

    //중복된 좌표인지 검사하고 보드배열 수정 및 턴 교체
    if(board[x][y]==32){
        board[x][y]= turn ? 'O' : 'X';
        printf("\033[0m%c",board[x][y]);
        //fflush(stdout); 테스트용
        if(is_win(turn,x,y,board)){
            break;            
        }
        turn = !turn;
    }
    else{
        continue;
    }
}   
    tcsetattr(0, TCSANOW, &oldt);
    printf("\033[%d;%dH",17,1);
    turn ? printf("흑돌 승!") : printf("백돌 승!");
    printf("\033[?25h");
    printf("\n");
    
    return 0;
}

bool is_win(bool turn,int x,int y,char board[16][16]){
    int count=0;
    char rock=32;
    int locate_x=x; int locate_y=y;

    if(turn==true){
        rock=79;
    }else{
        rock=88;
    }

    // 가로방향검사
    while(y-1>=1){
        if(board[x][y-1]==rock){count++; y--;}
        else{y=locate_y; break;}
    }
    while(y+1<=15){
        if(board[x][y+1]==rock){count++; y++;}
        else{y=locate_y; break;}
    }
    if(count==4){
        return true;
    }else{
        count=0;
    }

    // 세로방향검사
    while(x-1>=1){
        if(board[x-1][y]==rock){count++; x--;}
        else{x=locate_x; break;}
    }
    while(x+1<=15){
        if(board[x+1][y]==rock){count++; x++;}
        else{x=locate_x; break;}
    }
    if(count==4){
        return true;
    }else{
        count=0;
    }   
    // \방향검사

    while((x-1>=1)&&(y-1>=1)){
        if(board[x-1][y-1]==rock){count++;x--;y--;}
        else{x=locate_x; y=locate_y; break;}
    }
    while((x+1<=15)&&(y+1<=15)){
        if(board[x+1][y-1]==rock){count++;x++;y++;}
        else{x=locate_x; y=locate_y; break;}
    }
    if(count==4){
        return true;
    }else{
        count=0;
    }
    
    // /방향검사
    while((x-1>=1)&&(y+1<=15)){
        if(board[x-1][y-1]==rock){count++;x--;y++;}
        else{x=locate_x; y=locate_y; break;}
    }
    while((x+1<=15)&&(y-1>=1)){
        if(board[x+1][y+1]==rock){count++;x++;y--;}
        else{x=locate_x; y=locate_y; break;}
    }
    if(count==4){
        return true;
    }else{
        return false;
    }

}



    
