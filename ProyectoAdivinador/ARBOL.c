

#include "ARBOL.h"

ARBOLBINARIO CrearNodo(TipoDatoArbol x)
{
  ARBOLBINARIO nuevo = (ARBOLBINARIO) malloc(sizeof(ELEMENTODEARBOLBINARIO));
  nuevo -> dato = x;
  nuevo -> izq = nuevo -> der = NULL;
  return nuevo;
}

ARBOLBINARIO BuscarHoja(ARBOLBINARIO raiz, char *clave)
{
	if(raiz==NULL)
		return NULL;
	else if(strcmp(raiz -> dato , clave) == 0 && (!raiz -> izq && !raiz -> der))
		return raiz;
  else
  {
    ARBOLBINARIO raux;

    raux = BuscarHoja(raiz -> izq, clave);
    if (!raux)
      raux = BuscarHoja(raiz -> der, clave);

    return raux;
  }
}

void LimpiarArbol(ARBOLBINARIO *raiz)
{
  if(*raiz)
  {
    LimpiarArbol(&((*raiz) -> izq));
    LimpiarArbol(&((*raiz) -> der));

    (*raiz) -> izq = (*raiz) -> der = NULL;
  }
}

void MostrarOrden(ARBOLBINARIO raiz)
{
  if (raiz != NULL)
  {
    MostrarOrden(raiz -> izq);
    printf("%s ", raiz -> dato);
    MostrarOrden(raiz -> der);
  }
}
