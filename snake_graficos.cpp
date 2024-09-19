//Snake con graficos
#include<iostream>
#include<Windows.h>
#include<time.h>
#include<stdlib.h>
#include <stdio.h> 
#include <conio.h>
using namespace std;
int end = 0,charx=20,chary=10,direccion=0,contador=0,manzanax=0,manzanay=0,anchuraescenario=40,alturaescenario=20,score=0,colax[100],colay[100],ncola=1;
int colaxanterior,colayanterior,pausa=0,contador1=0;
 int cambiadocolor=0;
char backgroundcolor()
{
	return FOREGROUND_GREEN;
}

int setpos(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}
/*
	Colores del texto (FOREGROUND_):
	FOREGROUND_BLUE
	FOREGROUND_GREEN
	FOREGROUND_RED	
	FOREGROUND_INTENSITY
	
	Colores del fondo (BACKGROUND_):
	BACKGROUND_BLUE
	BACKGROUND_GREEN
	BACKGROUND_RED
	BACKGROUND_INTENSITY
*/

int setcolor(WORD color) { //CAMBIAR COLOR
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, color);
}
 
void hidecursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false; // Establece la visibilidad del cursor a falso
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

char dibujarsuelo() {
    char tiles[] = { '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB0', '\xB1' };
    return tiles[rand() % 33]; 
}




char coloraleatorio() 
{
    char colores[] = {
        FOREGROUND_BLUE,
        FOREGROUND_GREEN,
        FOREGROUND_RED,
        FOREGROUND_INTENSITY
    };

    // Elegir un número aleatorio de colores entre 1 y 4
    int numColores = rand() % 4 + 1;

    if (rand() % 2 == 0) {
        char colorFinal = 0;
        for (int i = 0; i < numColores; ++i) {
            int colorAleatorio = colores[rand() % 3]; 
            colorFinal |= colorAleatorio; 
        }
        // Si el color final es azul, volver a generar
        if (colorFinal == FOREGROUND_BLUE) {
            return coloraleatorio();
        }
        return colorFinal;
    }
    char colorFinal = 0;
    for (int i = 0; i < numColores; ++i) {
        int colorAleatorio = rand() % 3; // Excluir azul
        colorFinal |= colores[colorAleatorio]; // Mezclar con operador OR
    }
    // Si el color final es azul solo, volver a generar
    if (colorFinal == FOREGROUND_BLUE) {
        return coloraleatorio();
    }
    return colorFinal;
}




void menu()
{
	int menuend=0;
	setcolor(FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_RED);
	
	setpos(0,0);
	while (!menuend)
	{
			if(_kbhit())
		{
			switch(getch())
			{
				case 'm':
				menuend=1;
		 		break;
		 	  default:
		 	  	break;
			
			}
		}
	
	//dinujar menu
	
	cout<<"M to play";
	setpos(0,0);
	}

}	
	
void dibujarescenario()
{

		for(int i=0;i<anchuraescenario;i++)
	{
		for(int k=0;k<alturaescenario;k++)
		{
			setpos(i,k);
			if(i==0 and k==0) //primera linea
			{
				cout<<"\xC9";
			}else if(i!=39 and k==0)
			{
				cout<<"\xCD";
			}else if(i==39 and k==0)
			{
				cout<<"\xBB";
			}
			
			if(i==0 and k!=19 or i==39 and k!=19)//PAREDES  
			{
				cout<<"\xBA";
			}else if(i==0 and k==19)
			{
				cout<<"\xC8"; //bot left
			}else if(i!=0 and i!=39 and k==19)
			{
				cout<<"\xCD";
			}else if(i==39 and k==19)
			{
				cout<<"\xBC";
			}else {
	
			cout<<dibujarsuelo();
			
			}	
		}
		cout<<endl;
		
	}
setpos(0,0);
}

void drawchar()
{
	setpos(charx,chary);
	cout<<"\xF1";
}

void input()
{
    if (kbhit())
    {
        switch (getch())
        {
            case 'i': //arriba
			if(direccion!=2)
			{direccion=0;}
          	    break;
            
            case 'j': //left
            if(direccion!=3)
			{direccion=1;}
                break;
                
            case 'k': //down
            if(direccion!=0)
			{direccion=2;}
                break;
                
            case 'l': //right
            if(direccion!=1)
			{direccion=3;}
                break;
                
            case'm':
			pausa=1;
				break;
	  		
            default:
                break;
        }
    }
}

void generarmanzana()
{
    int manzanaposible = 0;
    while (manzanaposible == 0)
    {
        manzanax = 1 + rand() % (anchuraescenario - 2);
        manzanay = 1 + rand() % (alturaescenario - 2);
        
        
        bool colision = false; //que la manzana no se genere en medio de la cola
        for (int i = 0; i < ncola; i++)
        {
            if (manzanax == colax[i] && manzanay == colay[i])
            {
                colision = true;
                break;
            }
        }
        
      
        if (!colision) //si todo va bien se genera la manzana
        {
            manzanaposible = 1;
            setpos(manzanax, manzanay);
            cout << "O";
        }
    }
}

void logic()
{
	
		//tocar manzana
	if(charx==manzanax&&chary==manzanay)
	{
		generarmanzana();
	
		colax[ncola]=charx;
		colay[ncola]=chary;
		score++;
		ncola++;
		contador1++;
		cambiadocolor=0;
	}
	
	//mover dirección automatica segun donde mire la serpiente
	int delay=1;
	switch(direccion)
	{
		case 0:  
			if(contador%delay==0)
			{
			  setpos(charx,chary);
	             cout<<"\xB0";
				chary--;
			}contador++;
				break;
		case 1:
			if(contador%delay==0)
			{
			  setpos(charx,chary);        
	             cout<<"\xB0";
				charx--;
			}contador++;
				break;
		
		case 2:
			if(contador%delay==0)
			{
			  setpos(charx,chary);            
	             cout<<"\xB0";
				chary++;
			}contador++;
				break;
		
		case 3:
			if(contador%delay==0)
			{
			  setpos(charx,chary);         
	             cout<<"\xB0";
				charx++;
			}contador++;
				break;
		default:break;
	}
	
	//tocar borde
	if(charx==anchuraescenario-1 or chary==alturaescenario-1 or charx==0 or chary==0)
	{
		end=true;
	}
	
	int guardacolax=colax[0]; //1
	int guardacolay=colay[0]; 
	int guardacolax2; 
	int guardacolay2; 
	
	colax[0]=chary; //0
	colay[0]=charx;
	if(ncola>0)
	{
		colaxanterior=colax[ncola-1];
		colayanterior=colay[ncola-1];
		setpos(colayanterior,colaxanterior);
			cout<<"\xB0";
	}
	for(int i = 1 ; i<ncola ; i++) //nose como funciona
	{
		guardacolax2=colax[i];  
		guardacolay2=colay[i];
		
		colax[i]=guardacolax;
	    colay[i]=guardacolay;
		
		guardacolax=guardacolax2; 
		guardacolay=guardacolay2;
	}
	
	//colision colas
	for(int i=1;i<=ncola;i++)
	{
		if(charx==colay[i]&&chary==colax[i])
		{
			end=true;
		}
	}



}


void dibujarcola()
{
	for(int i=1;i<ncola;i++)
	{
	
	setpos(colay[i],colax[i]);
	cout<<"\xFE";
	
	
	}
}

void pausa1()
{

	while(pausa==1)
	{
	
	
		Sleep(30);
		
		if(_kbhit())
		{
			switch(getch())
			{
				case 'm':
					pausa=0;
					break;
			   default:
			   	break;
				
			}}
	
	
	}	
}

int main() {
srand(time(NULL));	

  //tamaño ventana
	    SMALL_RECT rect;
	    COORD coord;
	    coord.X = 40; // columna (anchura)
	    coord.Y = 20; // Fila 
	
	    rect.Top = 0;
	    rect.Left = 0;
	    rect.Bottom = coord.Y - 1; // Altura para ventana
		rect.Right = coord.X - 1; // Ancho para ventana

	
	    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	    SetConsoleScreenBufferSize(hwnd, coord); // Establece tamaño del búfer
	    SetConsoleWindowInfo(hwnd, TRUE, &rect); // Establece el tamaño de la ventana
	    SetConsoleTitle("Snake ASCII");
	
   //AQUI EMPIEZA EL PROGRAMA
   hidecursor();
   //menu();
 
  setcolor( backgroundcolor());
 
   dibujarescenario();
  
   generarmanzana();
   while(!end)
   {
   	
   		input();
   		if(pausa==1)
		{
		pausa1();
		}
   		logic();    
   		setpos(0,0);
	    dibujarcola();
	    drawchar();
	    setpos(manzanax, manzanay);
            cout << "O";
        setpos(37,19);
        cout<<ncola-1;
	  	Sleep(90);
	  	if(contador1%5==0 and ncola>1 and cambiadocolor==0)
	  	{
	  		setcolor(coloraleatorio());
	  		dibujarescenario();
	  			cambiadocolor=1;
	  	}
	  	
	  	
   }

 

}
