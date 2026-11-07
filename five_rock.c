#include <stdio.h>

int main(){
    int x=0;
    int y=0;

    char board[19][19];
    for(int i=0;i<19; i++){
        for(int j=0; j<19; j++){
            board[i][j]=' ';            
        }        
    }

    for(int i=0;i<19; i++){
        for(int j=0; j<19; j++){
            printf("%c ",board[i][j]);            
        }
        printf("\n");
    }
    printf("좌표를 입력하세요: ");
    scanf("%d %d",&x, &y);
    printf("%d %d\n",x,y);

    return 0;
}