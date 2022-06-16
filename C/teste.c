#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define ARROW_UP    72
#define ARROW_DOWN  80
#define ARROW_RIGHT 77
#define ARROW_LEFT	75


int Snake[300][2], pontos=1;
int Xsnake = 20, Ysnake = 20;
int XApple = 20, YApple = 20;

COORD get_console_dimensions(void)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD dimensions = { 40 - 0,
                         40 - 0 };
    return dimensions;
}

COORD get_console_cursor_pos(void)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition;
}

void gotoxy(short x, short y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void puts_centered(char const *str)
{
    size_t length = strlen(str);
    short x = (short)(get_console_dimensions().X - length) / 2;
    gotoxy(x, get_console_cursor_pos().Y);
    puts(str);
    return;
}



void UpdateXYMatrizSnake(){ 
    int i;
    gotoxy(Snake[pontos][0], Snake[pontos][1]);
    //if()
    printf("\033[0;37m");
    //
	if(Snake[pontos][0] % 2 == 0){
			printf("_");
		}else{
			printf("|");
		}
			
    //printf(" ");
			
	printf("\033[0m");
    for(i=pontos; i>=0; i--){
        Snake[i+1][0] = Snake[i][0];
        Snake[i+1][1] = Snake[i][1];
    }
}

int Collide(){ 
    int i, retorno=0;
    for(i=1; i<pontos; i++){
        if(Xsnake==Snake[i][0] && Ysnake==Snake[i][1]){
            retorno=1;
        }
    }
    return retorno;
}

int CollideWithWalll(){
	

	if( Ysnake == 0|| Ysnake == 21){
		printf("COLLIDEEEED");
		return 1;
	}
	if(Xsnake == 1 || Xsnake == 41){
		printf("eheehhehe");
		return 1;
	}
	

		return 0;
}
//Desenho do quadrado, ou retangulo na tela (largura, altura)
void DrawInterface(int width, int height){
	printf("\033[0;37m");
	printf("%c", 201);
	for(int i = 0; i<width; i++){
		printf("%c", 205);
	}
	printf("%c", 187);

	printf("\n");

	for(int j = 0; j<height; j++){

		printf("%c", 186);
		for(int i = 0; i <width; i++){
			
			if(i % 2 == 0){
				printf("|");
			}else{
				printf("_");
			}
			
			//printf(" ");
			
		}
		printf("%c\n", 186);
	}

	printf("%c", 200);

	for(int i = 0; i<width; i++){
		printf("%c", 205);
	}

	printf("%c", 188);
	printf("\033[0m");
	return;
}

void DrawSnake(){
	printf("\033[0;32m");	
    for(int i=0; i<pontos; i++){
        gotoxy(Snake[i][0], Snake[i][1]);
        printf("%c", 244);
    }
	printf("\033[0m");
	return;
}

void DrawGhostSnake(){
	printf(" ");

	return;
}

void DrawApple(int x, int y){

  printf("\033[0;31m");	
  gotoxy(x, y); printf("%c", 153);
  printf("\033[0m");

}

void generateApple(int *x, int *y){
	randAgain:
	*x = rand() %39;
	
	*y = rand() %19;
	if(*x == 0 || *y == 19){
		goto randAgain;
	}
	printf("%d, %d\n", *x, *y);
}


int main(){
	
	int KeyPressed;

	int points = 1, size = 3;
	int lastEvent =0;
	int times = 0;
	system("cls");
	srand(time(NULL));
	DrawInterface(40,20);
	system("pause");
	puts_centered("SNAKE GAME");
	generateApple(&XApple, &YApple);
	DrawApple(XApple, YApple);
	//system("COLOR 2F");
	int collidedBody = 0;
	int collidedWall = 0;
	while(collidedBody == 0 && collidedWall == 0 ){
		Snake[0][0]=Xsnake;
        Snake[0][1]=Ysnake;
		if(kbhit()){
			KeyPressed = getch();
			
				times = 0;
			
		}

			if(KeyPressed == ARROW_UP){
				Ysnake--;

			}else if(KeyPressed == ARROW_DOWN){
				Ysnake++;

			}else if(KeyPressed == ARROW_LEFT){
			   	Xsnake--;

			}else if(KeyPressed == ARROW_RIGHT){
				Xsnake++;
			}

			if(Xsnake == XApple && Ysnake == YApple){
				pontos++;
				//size++;
				generateApple(&XApple, &YApple);
				DrawApple(XApple, YApple);
				//gotoxy(0,0);printf("POINTS %d", pontos);
			}
		gotoxy(0,0);printf("snake position [X=%d] [Y=%d]", Xsnake, Ysnake);
		collidedBody = Collide();
		collidedWall= CollideWithWalll();
        UpdateXYMatrizSnake(); // Atualiza a cobra
        DrawSnake(); // Desenha a cobra
        gotoxy(0,0);
		Sleep(80);	

	}

	return 0;
}