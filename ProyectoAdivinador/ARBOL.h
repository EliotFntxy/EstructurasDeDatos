
//ARCHIVO DE CABECERA PARA LA DEFINICION DE ARBOL BINARIO CON SUS METODOS RESPECTIVOS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* TipoDatoArbol;

typedef struct nodo
{
  TipoDatoArbol dato;
  struct nodo *izq;
  struct nodo *der;
}ELEMENTODEARBOLBINARIO;

typedef ELEMENTODEARBOLBINARIO *ARBOLBINARIO;

ARBOLBINARIO CrearNodo(TipoDatoArbol x);
void LimpiarArbol(ARBOLBINARIO *raiz);
ARBOLBINARIO BuscarHoja(ARBOLBINARIO raiz, char *clave);
void MostrarOrden(ARBOLBINARIO raiz);
