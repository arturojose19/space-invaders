//Programadores Arturo Linares y Valera Mayras

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#define TAMANO_X 22
#define TAMANO_Y 17
#define ESC 27
#define IZQUIERDA 75
#define DERECHA 77
#define SPACEBAR 32

char matriz[19][24][2];

//Oculta el cursor
void ocultarcursor()
{ 
	HANDLE cord;
	 cord = GetStdHandle(STD_OUTPUT_HANDLE);
	 CONSOLE_CURSOR_INFO cci;
	 cci.dwSize = 100;
	 cci.bVisible = FALSE;
	 SetConsoleCursorInfo(cord, &cci);
}

//Gotoxy
void gotoxy(int x, int y)
{ 
	HANDLE cord;
	 cord = GetStdHandle(STD_OUTPUT_HANDLE);
	 COORD posicion;
	 posicion.X = x;
	 posicion.Y = y;
	SetConsoleCursorPosition(cord, posicion);
}

//Instrucciones
void instrucciones()
{
	system("color 0E");
	printf("\n");
	printf("\n");
	printf("   Pero antes conozcamos un poco mas del juego :D \n");
	printf("\n");
	printf("   Space Invaders es un videojuego de arcade lanzado al mercado en 1978.\n");
	printf("   Es uno de los primeros juegos shoot 'em up.\n");
	printf("   Es uno de los videojuegos mas importantes de la historia.\n");
	printf("   Su objetivo es eliminar oleadas de alienigenas con una nave laser \n");
	printf("   y obtener la mayor cantidad de puntos posible.\n\n");
	printf(" ");
	printf("  Instrucciones:\n");
	printf(" ");
	printf("  Los invasores se moveran de manera horizontal \n");
    printf("   y vertical al llegar al limite de su pantalla\n");
    printf("   Posees de unicamente 3 Vidas. Si las pierdes iras directo a un GAME OVER \n");
    printf("   Los invasores dispararan aleatoriamente sobre ti \n");
    printf("   Posees de 4 escudos que con un disparo de tu nave destruira \n");
    printf("   el escudo al instante \n");
    printf("   y 5 disparos de los invasores destruiran tu escudo  \n\n");
	printf(" ");
	printf("  CONTROLES:\n");
	printf(" ");
	printf("  Con la tecla (A) te moveras a la izquierda\n ");
	printf("  Con la tecla (D) te moveras a la derecha \n");
	printf("   Con la Barra espaciadora podras disparar \n");
}

//Localizador de usuario
int Localizadorjugador()
{
for(int i=0; i<24; i++)
{
	if(matriz[16][i][0]=='S')
	{
		return i;
	}
			
}
}	

//Limite de disparos
int LimiteDisparos()
{
for(int i=0; i<24; i++)
{
	for(int j=0; j<16; j++)
	{
		if(matriz[j][i][0]=='|')
		{
			return 0;
		}
	}
}
	return 1;
}

//Puntos
int puntos(int*lvl)
{
	int invasoresa=0, invasoresq=0, invasoresh=0, puntos;
	
		for(int j=0; j<19; j++){
		for(int i=0; i<24; i++){
			if(matriz[j][i][0]=='A'){
				invasoresa++;
				
			}
			if(matriz[j][i][0]=='Q'){
				invasoresq++;
				
			}
			
			if(matriz[j][i][0]=='H'){
				invasoresh++;
				
			}			
		}		
	}
	puntos=(((10-invasoresa)*40)+((20-invasoresq)*10)+((20-invasoresh)*20));
	if(*lvl==6){
		puntos+=1000;
	}
	else if(*lvl==4){
		puntos+=2000;
	}
	return puntos;
}

//Tiempo
void tiempo(time_t*t1, int &minutos, int &segundos)
{
time_t t2;
double diferencia = 0;
   
int temp;
   
t2 = time(NULL); 
      
      diferencia = difftime(t2, *t1);
      minutos = diferencia / 60.0;
      segundos = diferencia - minutos * 60;
      
if (temp != segundos){ 
         temp = segundos; 
      	 gotoxy(50, 2);
         printf("Tiempo: %02d:%02d", minutos, segundos);
      }
}

//Imprimir Mapa
void mapa()
{	
for(int j=0; j<19; j++)
	{
		for(int i=0; i<24; i++)
		{
	
			if(matriz[j][i][1]!=' ')
			{
			printf(" X");
			}
			else
			{
				printf(" %c", matriz[j][i][0]);
			}
		}
		printf("\n");
	}
}

//Escudo	
void escudo(int contador, int i, int j)
{
	if(contador>0)
	{
		matriz[j][i][1]='X';
				
		escudo(contador-1, i+5, j);
	}
}

//Movimiento del disparo
void Movdisparo()
{ 
for(int j=1; j<16; j++)
{
	for(int i=0; i<24; i++)
	{
		if(matriz[j][i][0]=='|')
		{
			if(j>1)
			{
				if(matriz[j-1][i][0]==' ' && matriz[j-1][i][1]==' ')
				{
					matriz[j-1][i][0]='|';
				}
				else if(matriz[j-1][i][1]!=' ')
				{
					matriz[j-1][i][1]=' ';
				}
				else if(matriz[j-1][i][0]!=' ')
				{
					matriz[j-1][i][0]=' ';
				}
			 
			}
			matriz[j][i][0]=' ';
		}
			
	}
		
}
}

//Limites
void Limites()
{
for(int j=0; j<19; j++){
	for(int i=0; i<24; i++){
		matriz[j][i][1]=' ';
		
		}
	}

	for(int j=0; j<19; j++){
		for(int i=0; i<24; i++){
			
			if(i==0 || i==23){
				matriz[j][i][0]='8';
			}
			else if(j==0 || j==18){
				matriz[j][i][0]='#';
			}
			
			else if(j==2 && (i>6 && i<17)){
					matriz[j][i][0]='A';
			}
			
			else if((j==3 || j==4)  && (i>6 && i<17)){
					matriz[j][i][0]='H';
			}
			
			else if((j==5 || j==6) && (i>6 && i<17)){
					matriz[j][i][0]='Q';
			}
			
			else if((j==12)&&(i==3 || i==4 || i==5)){
					matriz[j][i][0]=' ';
					escudo(4, i, j);
			}
			else if((j==13)&&(i==3 || i==5)){
					matriz[j][i][0]=' ';
					escudo(4, i, j);
			}
			else if((j==14)&&(i==3 || i==5)){
					matriz[j][i][0]=' ';
					escudo(4, i, j);
			}
			else{
				matriz[j][i][0]=' ';
			}
		}
	}
}
	
//Movimiento de aliens
void Movaliens(int*Movimiento)
{
int pausademovimiento=0;
	if(*Movimiento==0){
	
	for(int j2=1; j2<16; j2++){
		
				if(matriz[j2][22][0]!=' '){
					j2=19;
					*Movimiento=1;
					pausademovimiento++;
						for(int i=23; i>1; i--){
							for(int j=16; j>1; j--){
								
								if(matriz[j][i][0]==' '){
								if(matriz[j-1][i][0]!=' '){
								matriz[j][i][0]=matriz[j-1][i][0];
								matriz[j-1][i][0]=' ';
								
								
								}	
							}
							}
						}
						
				}	
				
			}


	
	if(pausademovimiento==0){
		for(int j=0; j<18; j++){
		for(int i=23; i>0; i--){
			
			if(matriz[j][i][0]==' ' || matriz[j][i][0]=='|'){
		
					if(matriz[j][i][0]=='|' && matriz[j][i-1][0]!=' ' && matriz[j][i-1][0]!='*'){
					matriz[j][i-1][0]=' ';
					matriz[j][i][0]=' ';
				
				
				
				}
				if(matriz[j][i-1][0]=='A'){
					matriz[j][i][0]='A';
					matriz[j][i-1][0]=' ';
				
				}	
				
			if(matriz[j][i][0]==' ' || matriz[j][i][0]=='|'){
				if(matriz[j][i-1][0]=='H'){
					matriz[j][i][0]='H';
					matriz[j][i-1][0]=' ';
				
				
				}
			}
			
			if(matriz[j][i][0]==' ' || matriz[j][i][0]=='|'){
				if(matriz[j][i-1][0]=='Q'){
					matriz[j][i][0]='Q';
					matriz[j][i-1][0]=' ';
				
					}
			}
			
			
	}
	

		}
	}
}
}

if(*Movimiento==1 && pausademovimiento==0){
	
	for(int j2=1; j2<16; j2++){
				if(matriz[j2][1][0]!=' '){
					j2=19;
					*Movimiento=0;
						for(int i=23; i>0; i--){
							for(int j=16; j>1; j--){
								
								if(matriz[j][i][0]==' ' || matriz[j][i][0]=='|'){
								if(matriz[j-1][i][0]!=' '){
								matriz[j][i][0]=matriz[j-1][i][0];
								matriz[j-1][i][0]=' ';
								
								
								}	
							}
							}
						}
						
				}	
				
			}
	
	if(*Movimiento==1){
	for(int j=0; j<18; j++){
		for(int i=0; i<23; i++){
			
			if(matriz[j][i][0]=='|' && matriz[j][i+1][0]!=' ' && matriz[j][i-1][0]!='*'){
					matriz[j][i+1][0]=' ';
					matriz[j][i][0]=' ';
				
				}
				
			if(matriz[j][i][0]==' ' || matriz[j][i][0]=='|'){
				if(matriz[j][i+1][0]=='A'){
					matriz[j][i][0]='A';
					matriz[j][i+1][0]=' ';
				
				}
				
			if(matriz[j][i][0]==' ' || matriz[j][i][0]=='|'){
				if(matriz[j][i+1][0]=='H'){
					matriz[j][i][0]='H';
					matriz[j][i+1][0]=' ';
				
				}
			}
			
			if(matriz[j][i][0]==' ' || matriz[j][i][0]=='|'){
				if(matriz[j][i+1][0]=='Q'){
					matriz[j][i][0]='Q';
					matriz[j][i+1][0]=' ';
					
				}
			}
		
		
		}
	}
}
}


}	

}

//Para Ganar o Perder
void Victoria(bool*fin, int*lvl, int cedula, int minutos, int segundos, int*paramover, int*esperaaliens)
{
int contador=0;

		for(int i=1; i<23; i++){
			
		for(int j=1; j<16; j++){
			
			if(matriz[j][i][0]== 'A'|| matriz[j][i][0]== 'Q'|| matriz[j][i][0]== 'H'){
			contador++;
			}
		}
		}
			for(int i=1; i<23; i++){
				
			if(matriz[16][i][0]== 'A'|| matriz[16][i][0]== 'Q'|| matriz[16][i][0]== 'H'){
			contador=contador + 50;
		}
		
		}
		if(contador>50 || *fin==TRUE){
			system("cls");
			gotoxy(20,10);
			system("color 0B");
			printf("\t FIN DEL JUEGO \n");
			printf("\t HAS PERDIDO TODAS TUS VIDAS \n");
			printf("\t La cedula del usuarios es :  %i\n", cedula);
			printf("\t Tu puntuje fue de : %i\n", puntos(&(*lvl)));
			printf("\t Obtuviste un tiempo de : %02d:%02d", minutos, segundos);
					
			system("pause > NULL");
			*fin=TRUE;
		}
		if(contador==0){
			int nmundo;
			if(*lvl==8){
				*lvl=6;
				nmundo=2;
				Limites();
				matriz[16][10][0]='S';
				matriz[16][11][0]='S';
				matriz[16][12][0]='S';
				*paramover=0;
				*esperaaliens=*lvl;
				
			}
			else if(*lvl==6){
				*lvl=4;
				nmundo=3;
				Limites();
				matriz[16][10][0]='S';
				matriz[16][11][0]='S';
				matriz[16][12][0]='S';
				*paramover=0;
				*esperaaliens=*lvl;
				
			}
			else{
		
			system("cls");
			gotoxy(20,10);
			system("color 0B");
			printf("\t HAS GANADO!!\n");
			printf("\t MATASTE A TODOS LOS ALIENS!!\n");
			printf("\t La cedula del usuarios es :  %i\n", cedula);
			printf("\t Tu puntuje fue de : %i\n", puntos(&(*lvl)));
			printf("\t Obtuviste un tiempo de : %02d:%02d", minutos, segundos);
			system("pause > NULL");	
			*fin=TRUE;
			}
			
			if(*lvl!=4){
			system("cls");
			gotoxy(20,10);
			system("color 0B");
			printf("Has avanzado al nivel %i\n", nmundo);
			system("pause > NULL");	
			}
		
			
		}
}

//Disparo de aliens random
void Disparonrandom()
{
int ultimafila=0, numerodeposiciones=0;
	
	for(int j=1; j<16; j++){
		for(int i=1; i<23; i++){
			if(matriz[j][i][0]=='Q' || matriz[j][i][0]=='H' || matriz[j][i][0]=='A')
			{
				ultimafila=j;
			}
		}
	}

for(int i=1; i<23; i++){
	if(matriz[ultimafila][i][0]!=' ')
	{
			numerodeposiciones++;
	}
}
	int auxcantidad;
	if (numerodeposiciones<3)
	{
		auxcantidad=numerodeposiciones+1;
		
	}
	else
	{
		auxcantidad=4;
	}
	
	int cantidaddedisparos=rand()%auxcantidad;

	int posiciones[3]={0};
	
	for(int cont=0; cont<cantidaddedisparos; cont++)
	{
		
		if(cont==1)
		{
			do{
				posiciones[cont]=(rand()%numerodeposiciones)+1;	
			}while(posiciones[cont]==posiciones[cont-1]);
		}
		else if(cont==2)
		{
			do
			{
				posiciones[cont]=(rand()%numerodeposiciones)+1;	
			}while(posiciones[cont]==posiciones[cont-1] && posiciones[cont]==posiciones[cont-2]);
		}
		else
		{
			posiciones[cont]=(rand()%numerodeposiciones)+1;	
		}
		
	}
	for(int cont=0; cont<cantidaddedisparos; cont++)
	{
	for(int i=1, aux=0; i<23; i++){
		if(matriz[ultimafila][i][0]!=' ')
		{
			aux++;
		
			if(aux==posiciones[cont])
			{
				
				if(matriz[ultimafila+1][i][0]!=' ')
				{
					matriz[ultimafila+1][i][0]=' ';
				}
				else
				{
					matriz[ultimafila+1][i][0]='*';
					gotoxy((i*2)+1, ultimafila+1);
					printf("*");
				}	
			}	
	}	
	}	
}
}

//Movimiento de Balas
void movimientobalasalien(int*vidas)
{
int solounavida=*vidas;
	char q='S';
	for(int j=17; j>1; j--){
		for(int i=0; i<24; i++){
			
		if(matriz[j][i][0]=='*'){
			
			if(j<17){
				if(matriz[j+1][i][0]==' ' && matriz[j+1][i][1]==' '){
					
					matriz[j+1][i][0]='*';
				}
				
				else if(matriz[j+1][i][1]!=' '){
					
					if(matriz[j+1][i][1]=='X'){
					matriz[j+1][i][1]='C';	         

					}
					else if(matriz[j+1][i][1]=='C'){
					matriz[j+1][i][1]='V';	
				}
				
				else if(matriz[j+1][i][1]=='V'){
					matriz[j+1][i][1]='B';	
				}
					else if(matriz[j+1][i][1]=='B'){
					matriz[j+1][i][1]='N';	
					}
					else if(matriz[j+1][i][1]=='N'){
					matriz[j+1][i][1]=' ';	
					}
  
				}
				
				else if(matriz[j+1][i][0]==q && solounavida==*vidas){
					gotoxy(0,20);
					printf("Has perdido una vida\n");
					system("pause");
					gotoxy(0,20);
					printf("\n");
					(*vidas)--;
						for(int j2=18; j2>1; j2--){
						for(int i2=0; i2<24; i2++){
			
						if(matriz[j2][i2][0]=='*'){
						matriz[j2][i2][0]=' ';
						}	
						}
						}
					
                
				}
				else if(matriz[j+1][i][0]=='|'){
					
					 matriz[j+1][i][0]=' ';  
				}
					     
			}
			
           matriz[j][i][0]=' ';              
	
		}

}
}
}

//Patalla de Inicio
void pantallaInicio ()
{
	gotoxy(2,2);
	printf("  _____                            _____                      _");
	gotoxy(2,3);
	printf(" / ____|                          |_   _|                    | |");
	gotoxy(2,4);
	printf("( (____  ____   __ _  ___  ___      | |  _ ____    ____ _  __| | ___ _ ______");
	gotoxy(2,5);
	printf(" \\____ \\|  _ \\ / _` |/ __|/ _ \\     | | | '_ \\ \\  / / _` |/ _` |/ _ \\ '__/ __|");
	gotoxy(2,6);	
	printf(" _____) | |_) | (_| | (__|  __/    _| |_| | | \\ \\/ / (_| | (_| |  __/ |  \\__ \\");
	gotoxy(2,7);
	printf("|______/|  __/ \\__,_|\\___|\\___|   |_____|_| |_|\\__/ \\__,_|\\__,_|\\___|_|  |___/");
	gotoxy(2,8);	
	printf("        |_|");
	gotoxy(2,10);
	printf("          ##          ##            ####                ########");
	gotoxy(2,11);
	printf("            ##      ##            ########        ####################");
	gotoxy(2,12);
	printf("          ##############        ############    ########################");
	gotoxy(2,13);
	printf("        ####  ######  ####    ####  ####  ####  ######    ####    ######");
	gotoxy(2,14);
	printf("      ######################  ################  ########################");
	gotoxy(2,15);
	printf("      ##  ##############  ##    ##  ####  ##    ##########    ##########");
	gotoxy(2,16);
	printf("      ##  ##          ##  ##  ##            ##    ####    ####    ####");
	gotoxy(2,17);
	printf("            ####  ####          ####    ####        ####        ####");
	gotoxy(20,24);
	printf("\tPresiona enter si estas listo\n\n");
	getch();
}

int main()
{   
pantallaInicio ();                                    						
system("color 0D");
int cedula, minutos, segundos;
char seguir;
printf("\t\t Introduzca su cedula para comenzar a jugar\n");
scanf("%i", &cedula);
system("cls");
instrucciones();
ocultarcursor();
system("pause > NULL");
do{
Limites();
matriz[16][10][0]='S';
matriz[16][11][0]='S';
matriz[16][12][0]='S';
system("cls");
int nivel=8;
int numeronivel=1;
mapa();
int ayuda;
int esperaaliens=8;
int paramover=0;
int descansoalfuego, vidas=3;
time_t t1;		
 t1 = time(NULL); 		
			bool fin=FALSE;
				while(!fin){
				if(nivel==8){
				system("color 0B");
				numeronivel=1;	
				}
				else if(nivel==6){
				system("color 0B");	
				numeronivel=2;
				} 	
				else if(nivel==4){
				system("color 0B");
				numeronivel=3;	
				} 	
		if(kbhit()){
                   	
				char tecla = getch();
		 
				
				int x=Localizadorjugador();
				
				if((tecla == 'a' || tecla== 'A') && matriz[16][(x-1)][0]!='8'){
                         
					matriz[16][x-1][0]='S';
					matriz[16][x+2][0]=' ';
					gotoxy((x*2)-1,16);
                    printf("S");
                    gotoxy((x*2)+5,16);
                    printf(" ");
                }
				
				else if((tecla == 'd' || tecla== 'D') && matriz[16][(x+3)][0]!='8'){
				
					matriz[16][x+3][0]='S';
					matriz[16][x][0]=' ';
					gotoxy((x*2)+7,16);
                    printf("S");
                    gotoxy((x*2)+1,16);
                    printf(" ");
				 }
				 
				 else if((tecla == 'P' || tecla== 'p')){
				 gotoxy(0,20);
					system("pause");
				 }
                
                else if(tecla == 32 && descansoalfuego==1){

                     if(matriz[15][x+1][0]!=' '){
                     	matriz[15][x+1][0]=' ';
                     	
                     }
                     else{
                     	 matriz[15][x+1][0]='|';
                     	 gotoxy(((x+1)*2)+1,15);
                    	printf("|");
                    	
                    	 	
                     }
                }
               
					}
	
	Sleep(100);				
	descansoalfuego = LimiteDisparos();
	Movdisparo();
	movimientobalasalien(&vidas);
	
	if(esperaaliens==nivel){
    Movaliens(&paramover);
    esperaaliens=0;
    }
    if(rand()%2==1 && (esperaaliens==nivel/2)){
	Disparonrandom();
	}
   	tiempo(&t1, minutos, segundos);
    esperaaliens++;
    gotoxy(50, 4);
    
    printf("Cedula del Jugador: %i", cedula);
	gotoxy(50, 10);
    
	printf("Nivel %i", numeronivel);
	gotoxy(50, 6);
	
	printf("Puntos: %i", puntos(&nivel));
	gotoxy(50, 8);
	
	printf("Vidas: %i", vidas);
	gotoxy(0,0);
	
	mapa();
	if(vidas==0)
	{
		fin=true;
	}
	Victoria(&fin, &nivel, cedula, minutos, segundos, &paramover, &esperaaliens);
	}
		system("cls");
		printf("\n\t Quiere volver a jugar? \n\t presione [5] si desea volver a jugar \n\t presione enter para salir.\n");
		scanf("%i", &seguir);

	}while(seguir==5);
	}	
