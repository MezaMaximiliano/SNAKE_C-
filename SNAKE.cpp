#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>


using namespace std;

#define FILA 500
#define COLUMNA 2

int pos[FILA][COLUMNA];

void ocultarCursor();
void gotoxy(int, int);
void dibujarMarco();
void dibujarCuerpo(int);
void borrarCuerpo(int &);
void actualizarPos(int, int,int &);
void agregarComida(int &, int &,int,int);
void iniciar(int &,int,int &,int &);
void mover(int &,int &, char &);
bool finJuego(int , int,int,int);
void recExt();
void recInt();
void mostrarPuntos(int);
void dificultad(int &,int,int &);
bool comprobarPos(int , int , int, int);

int menu(){
	
	int rta;
	bool h=false;
while(!h){

	system("cls");
	
	gotoxy(0,0);
	printf("%c", 201);
	gotoxy(120,0);
	printf("%c",187);
	gotoxy(0,30);
	printf("%c",200);
	gotoxy(120,30);
	printf("%c",188);

	for (int i=1;i<120;i++){
		gotoxy(i,0);
		printf("%c",205);
		gotoxy(i,30);
		printf("%c",205);
	}
	
	for (int i=1;i<30;i++){
		gotoxy(0,i);
		printf("%c",186);
		gotoxy(120,i);
		printf("%c",186);
	}
	
	gotoxy(30,10);
	printf("%c", 201);
	gotoxy(90,10);
	printf("%c",187);
	gotoxy(30,20);
	printf("%c",200);
	gotoxy(90,20);
	printf("%c",188);
	
	for (int i=31;i<90;i++){
		gotoxy(i,10);
		printf("%c",205);
		gotoxy(i,20);
		printf("%c",205);
	}
	
	for (int i=11;i<20;i++){
		gotoxy(30,i);
		printf("%c",186);
		gotoxy(90,i);
		printf("%c",186);
	}
	
	gotoxy(48,12);
	printf("=========>MENU<=========");
	gotoxy(53,14);
	printf("1-JUEGO NUEVO");
	gotoxy(53,15);
	printf("2-SALIR");
	gotoxy(53,18);
	printf("OPCION (1||2): ");
	scanf("%i",&rta);
	fflush(stdin);
	if(rta<1 or rta>2){
		h=false;
	}else{
		h=true;
	}

}
	system("cls");
	return 	rta;
}

int main(){//------------------------INICIO

	int xC, yC,rta;
	int k=5;
	srand(time(NULL));
INICIO:
	system("cls");
	int puntos=0;
	int	tam=3;
	int x=20,y=10;
	int n=0;//INDICE MATRIZ MATRIZ POSICIONES
	int l=0;//CONTADOR BORRAR
	int velocidad=200;
	char op='d';
	rta=menu();
	
	
	if (rta==1){
	
		agregarComida(xC, yC,tam,n);
	
		ocultarCursor();
		dibujarMarco();
		iniciar(n,tam,x,y);
		while (!GetAsyncKeyState(0X1B)){
			gotoxy(142,1);
			printf("PUNTOS  %i",puntos*10);
			dibujarCuerpo(n);
		
			if (x==xC and y==yC){
				agregarComida(xC,yC,tam,n);
				tam++;
				puntos++;
				dificultad(velocidad,puntos,k);
			}else{
		
				borrarCuerpo(l);
			}
			mover(x,y,op);
			if (finJuego(x,y,tam,n)){
				mostrarPuntos(puntos);
				system("pause>NULL");
				break;
			}
		
			actualizarPos(x,y,n);
			if (GetAsyncKeyState(0X20)){
			MessageBoxA(0,"HAGA CLICK EN ACEPTAR PARA CONTINUAR","PAUSE",MB_OK);
			}
		
			Sleep(velocidad);
		}
	goto INICIO;
	}else{
		system("cls");
		recInt();
		recExt();
		gotoxy(44,15);
		printf("=========>FIN DEL JUEGO<=========");
		gotoxy(0,31);
	}
	
	system("pause>NULL");
	return 0;
}

void dificultad(int &velocidad,int puntos,int &k){
	
	if ((puntos%5)==0){
		velocidad=velocidad-50;
		if (velocidad<50){
			velocidad=50-k;
			k=k+5;
			if (velocidad<25){
				velocidad=20;
			}
		}
	}
	
}

void mostrarPuntos(int puntos){
	system("cls");
	recExt();
	recInt();
	gotoxy(46,12);
	printf("=========>PUNTUACION<=========");
	gotoxy(46,14);
	printf("==============>");
	gotoxy(46,15);
	printf("==============>       %i",puntos*10);
	gotoxy(46,16);
	printf("==============>");
	
}

bool finJuego(int x, int y,int tam,int n){
	if (x==0 or x==120 or y==0 or y==30){
		return true;
	}
	
	for(int i=n-1;i>=n-tam;i--){
		if (pos[i][0]==x and pos[i][1]==y){
			return true;
		}
	}
	
	return false;
}

void mover(int &x, int &y, char &op){
		if ((GetAsyncKeyState(0X44) or op=='d')and (op!='a')){
			op='d';
			x++;
			fflush(stdin);
		}
		 if ((GetAsyncKeyState(0X41) or op=='a')and (op!='d')){
			op='a';
			x--;
			fflush(stdin);
		}
		 if ((GetAsyncKeyState(0X57) or op=='w')and (op!='s')){
			op='w';
			y--;
			fflush(stdin);
		}
		 if ((GetAsyncKeyState(0X53) or op=='s')and(op!='w')){
			op='s';
			y++;
			fflush(stdin);
		}
}

void iniciar(int &n,int tam,int &x,int &y){
	for(int i=1;i<=tam;i++){
		gotoxy(pos[n][0],pos[n][1]);
		printf("*");
		x++;
		actualizarPos(x, y,n);
	}
}

void dibujarCuerpo(int n){
	
		gotoxy(pos[n][0],pos[n][1]);
		printf("*");
		
	
}

void borrarCuerpo(int &l){
	
	gotoxy(pos[l][0], pos[l][1]);
	printf(" ");
	l++;
	if (l==500){
		l=0;
	}
	
	
}

void actualizarPos(int x, int y,int &n){
	
	n++;
	pos[n][0]=x;
	pos[n][1]=y;
	if (n==500){
		n=0;
	}
	
	

}

void agregarComida(int &xC, int &yC,int tam,int n){
	srand(time(NULL));
	xC=2+rand() % (49 - 2);	
	yC=2+rand() % (19 - 2);
	gotoxy(xC,yC);
	
	if(comprobarPos(xC, yC,tam,n)){
		xC=2+rand() % (49 - 2);	
		yC=2+rand() % (19 - 2);
		gotoxy(xC,yC);	
		if(comprobarPos(xC, yC,tam,n)){
			xC=2+rand() % (49 - 2);	
			yC=2+rand() % (19 - 2);
			gotoxy(xC,yC);
		}
	}
	
	printf("%c",04);
}

bool comprobarPos(int xC, int yC,int tam, int n){
	
	
	if (n>tam){
		
		for (int i=0;i<tam;i++){
			if (xC==pos[n][0] and yC==pos[n][1]){
			return true;
			}
			
		}
		
		
	}else if(n<tam){
		int dif=0;
		dif=tam-n;
		for (int i=n;i>=0;i--){
			if (xC==pos[n][0] and yC==pos[n][1]){
			return true;
			}
			if (n==0){
				break;
			}
		}
		for (int i=FILA; i>=FILA-dif;i--){
			if (xC==pos[i][0] and yC==pos[i][1]){
			return true;
			}
		}
		
	}else if(n==0){
		n=FILA;
		for (int i=0;i<tam;i++){
			if (xC==pos[n][0] and yC==pos[n][1]){
			return true;
			}
			n--;
		}
		
	}
	return false;
}

void recExt(){
	gotoxy(0,0);
	printf("%c", 201);
	gotoxy(120,0);
	printf("%c",187);
	gotoxy(0,30);
	printf("%c",200);
	gotoxy(120,30);
	printf("%c",188);

	for (int i=1;i<120;i++){
		gotoxy(i,0);
		printf("%c",205);
		gotoxy(i,30);
		printf("%c",205);
	}
	
	for (int i=1;i<30;i++){
		gotoxy(0,i);
		printf("%c",186);
		gotoxy(120,i);
		printf("%c",186);
	}
	
}
void recInt(){
	gotoxy(30,10);
	printf("%c", 201);
	gotoxy(90,10);
	printf("%c",187);
	gotoxy(30,20);
	printf("%c",200);
	gotoxy(90,20);
	printf("%c",188);
	
	for (int i=31;i<90;i++){
		gotoxy(i,10);
		printf("%c",205);
		gotoxy(i,20);
		printf("%c",205);
	}
	
	for (int i=11;i<20;i++){
		gotoxy(30,i);
		printf("%c",186);
		gotoxy(90,i);
		printf("%c",186);
	}
	
}

void dibujarMarco(){
	gotoxy(0,0);
	printf("%c", 201);
	gotoxy(120,0);
	printf("%c",187);
	gotoxy(0,30);
	printf("%c",200);
	gotoxy(120,30);
	printf("%c",188);
	for (int i=1;i<120;i++){
		gotoxy(i,0);
		printf("%c",205);
		gotoxy(i,30);
		printf("%c",205);
	}
	
	for (int i=1;i<30;i++){
		gotoxy(0,i);
		printf("%c",186);
		gotoxy(120,i);
		printf("%c",186);
	}

}

void gotoxy(int x, int y){
	HANDLE hcon;
	hcon=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon,dwPos);
}

void ocultarCursor(){
	HANDLE consoleHandle=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize=100;
	info.bVisible=false;
	SetConsoleCursorInfo(consoleHandle,&info);
}
