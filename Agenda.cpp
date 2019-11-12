#include<stdio.h>
#include<stdlib.h>
void menu(){
	
	//Lista l;
	int opc;
	char nombre,telefono,correo,direccion;
	char buscar;
	
	while(1){
		system("cls");
		printf("Bienvenido, que deseas hacer en tu agenda..??\n");
		printf("1.- Insertar\n");
		printf("2.- Imprimir\n");
		printf("3.- Buscar\n");
		printf("4.- Modificar\n");
		printf("5.- Borrar\n");
		printf("6.- Salir\n");
		scanf("%d",&opc);
		if(opc == 1){
			system("cls");
			printf("Ahora insertaremos un nuevo contacto");
			printf("Cual es su nombre? ");
			scanf("%s",&nombre);
			printf("Cual es su telefono? ");
			scanf("%s", &telefono);
			printf("Cual es su correo? ");
			scanf("%s",&correo);
			printf("Cual es su direccion? ");
			scanf("%s", &direccion);
			//l.insertar(nombre,telefono,correo,direccion);
			printf("Listo, tienes un amigo mas a tu lista :D ");
			system("pause");
		}
	};
}
int main(){
	menu();
	
}
