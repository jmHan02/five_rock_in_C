#include <stdio.h>
#include <stdbool.h>

int main(){
    int x=0;
    int y=0;
    char board[19][19];
    bool turn = false;

    //보드 초기화
    for(int i=0;i<19; i++){
        for(int j=0; j<19; j++){
            board[i][j]=' ';            
        }        
    }

    while(true){
    printf("\033[H\033[2J");
    fflush(stdout);
    
    turn = !turn;
    
    
    for(int i=0;i<19; i++){
        for(int j=0; j<19; j++){
            printf("%c ",board[i][j]);            
        }
        printf("\n");
    }
    printf("좌표를 입력하세요: ");
    scanf("%d %d",&x, &y);
    board[x][y]= turn ? 'O' : 'X';


}

    return 0;
}