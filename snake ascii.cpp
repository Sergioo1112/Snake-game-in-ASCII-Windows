#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <iostream>
#include <conio.h>
#include <unistd.h> 
#include <Windows.h>
using namespace std;
int ncola=1;//cuantas colas tengo
int colax[1000],colay[1000]; 
int i, j, height = 20,width = 20 ,flag, gameover,score,fruitx,fruity,x=height/2,y=width/2,pausa=0; //el terreno de juego es 18x18
bool pizza=false;

void draw() 
{
    system("cls"); 
    //dibujar escenario
    for (i = 0; i < height; i++) 
	{   						   	 // i =linea //height = altura
        for (j = 0; j < width; j++) // j = espacio //width = anchura
		 { 
            if(i==0 /*Cuando es la linea 0*/||i==width-1 /*cuando es final de anchura*/||j==0 /*espacio = 0*/||j==height-1 /*ultima linea*/) 
			{
			
			if(i==0 /*Cuando es la linea 0*/||i==width-1 /*cuando es final de anchura*/)
            {
            	printf("~");
			}else if(j==0 /*espacio = 0*/||j==height-1 /*ultima linea*/)
			{
				printf("|");
			}
			else{ 
                printf("#"); 
            } 
            }
            else 
			{ 
               if(i==x && j == y)//dibujar personaje
               {
               	printf("@");
               }else if(i ==fruitx && j==fruity) //dibujar fruta
			   {
			   	printf("*");
			   }
               else
			   {
			   	pizza=false;
			   	for(int k=0;k<ncola;k++)  //dibujado de cola
			   	{
			   		if(colax[k]==j&&colay[k]==i)
			   		{
			   			printf("o");
			   			pizza=true;
			   		}
			   	}
			   	
			   if (pizza==false)
			   {
			   
               printf(" ");}	//si no hay nada, dibujar espacio
		    	}
            } 
            
         } 
        printf("\n"); 
    }
if(pausa==1)
{
printf("	Pause\n\n");
}
printf("Score = %d", score); 
}

void fruits()
{
srand(time(NULL));
label5:
fruitx=1+rand()%(height-2);//aleatorio entre 1 y 19
 if (fruitx == 0) 
        goto label5; 
label6:
fruity=1+rand()%(width-2);//aleatorio entre 1 y 19
if (fruitx == 0) 
        goto label6;
}

void inputs()
{
if(_kbhit())
{
	switch(getch())
	{
		case 'j':
			flag=1;//izquierda
			break;
		 case'k':
			flag=2;//abajo
			break;
		case'l':
			flag=3;//derecha
			break;
		case'i':
			flag=4;//arriba
			break;
		case'n':
			gameover=1;//gameover
			break;	
		case'm':
			pausa=1;
	   default:
	   	break;
		
	}
}	
}

void logic()
{
//1=left,2=down,3=right,4=up
switch(flag)//consecuencias de tocar teclas de movimiento
{
case 1://izquierda J  // la variable X y la variable Y estan intercambiadas
	y--;
	break;
case 2://abajo K
	x++;
	break;
case 3://derecha L
	y++;
	break;
case 4://arriba I
	x--;
	break;
default:
	break;
}
if(x<1 || x>(height-2) || y<1 || y>(width-2))//salirse del mapa
{
gameover=1;
}

if(x==fruitx && y==fruity)//si tocar fruta
{
label7:
fruitx=1+rand()%(height-2);
 if(fruitx==1||fruitx==(height-2)||fruitx==x /*si la fruta toca jugador o paredes*/) 
        goto label7; 
label8:
fruity=1+rand()%(width-2);
if(fruity==1||fruity==(width-2)||fruity==y) 
        goto label8;
score++;
ncola++;
}

//colisión colas

for(int i=1;i<=ncola;i++)
{
	if(x==colay[i]&&y==colax[i])
	{
		gameover=1;
	}
}


//colas
/*

x = 0

      
tailx = (1, 2, 3)



tailx = (0,1,2)


*/
int guardacolax=colax[0]; //1
int guardacolay=colay[0]; 
int guardacolax2; 
int guardacolay2; 
colax[0]=y; //0
colay[0]=x;


for(int i = 1 ; i<ncola ; i++) //nose como funciona, pero lo hace
{
	
	guardacolax2=colax[i];  
	guardacolay2=colay[i];
	
	colax[i]=guardacolax;
    colay[i]=guardacolay;
	
	guardacolax=guardacolax2; 
	guardacolay=guardacolay2;
	
	
}
}

void pausa1()
{

	system("cls");

while(pausa==1&&gameover==0)
{
draw();

Sleep(30);
if(_kbhit())
{
	switch(getch())
	{
		case 'm':
			pausa=0;
			break;
		case'n':
			gameover=1;
			pausa=0;
			break;
	   default:
	   	break;
		
	}}


}	
}

void esperar()
{
	
//	if(ncola<=10){
Sleep(70);
/*}else if(ncola<=20)
{
Sleep(90);
}
else if(ncola<=30)
{
Sleep(110);
}
else
{
Sleep(130);
}*/
}


int main() 
{ 

//tamaño ventana
    SMALL_RECT rect;
    COORD coord;
    coord.X = 25; // Define X
    coord.Y = 23; // Define Y para el tamaño del búfer.

    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = coord.Y-1; // Altura para ventana
    rect.Right = coord.X-1; // Ancho para ventana

    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(hwnd, coord); // Establece tamaño del búfer
    SetConsoleWindowInfo(hwnd, TRUE, &rect); // Establece el tamaño de la ventana
    SetConsoleTitle("Snake");


fruits();
while(!gameover)
{ 
draw(); 
inputs();

if(pausa==1)
{
pausa1();
}

esperar();

logic();












}//end of code
return 0; 
} 
