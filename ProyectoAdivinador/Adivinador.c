
#include "ARBOL.C"

#define MAXLEN 100 //Maxima longitud de cadena de los nodos
#define MAXFTXTLEN 200 //Maxima longitud de cadena de texto de archivo

//Funciones para el correcto funcionamiento del programa
char getRespuesta()
{
  char o;

  do {
    scanf(" %c", &o);
    fflush(stdin);

    if (o != 's' && o != 'n')
      puts("Respuesta no valida. Ingrese nuevamente una respuesta");
  } while(o != 's' && o != 'n');
}
void Pausar(char* msg)
{
 printf("\n%s\n", msg);
 printf("(Pulse cualquier tecla para continuar...) ");
 getchar();
 fflush(stdin);
}

//Funciones para modificaciones del arbol
void VerificarArbol(ARBOLBINARIO raiz, char *r1, char *r2)
{
  if (!(raiz -> izq))
    raiz -> izq = CrearNodo(r1);
  if (!(raiz -> der -> izq))
    raiz -> der -> izq = CrearNodo(r2);
}

void AprenderNuevo(char *tematica, ARBOLBINARIO hoja)
{
  char o;
  ARBOLBINARIO rder;
  ARBOLBINARIO rizq;

  char *respuesta = (char *) malloc(MAXLEN);
  char *pregunta = (char *) malloc(MAXLEN);

  puts("\nNo adivine):\n");
  printf("Que %s es? (Ingrese articulo un/una/el/la/los/las si es necesario)\n", tematica);
  gets(respuesta);
  fflush(stdin);

  printf("Que distingue a %s de %s?\n", hoja -> dato, respuesta);
  gets(pregunta);
  fflush(stdin);

  printf("%s %s? (s/n): ", hoja -> dato, pregunta);
  o = getRespuesta();

  if (o == 's') //Manda respuesta original al hijo izquierdo de la nueva pregunta y la respuesta nueva al hijo derecho
  {
    rder = CrearNodo(respuesta);
    rizq = CrearNodo(hoja -> dato);

    hoja -> dato = pregunta;
    hoja -> izq = rizq;
    hoja -> der = rder;
  }
  else //Manda respuesta original al hijo derecho de la nueva pregunta
  {
    rder = CrearNodo(hoja -> dato);
    rizq = CrearNodo(respuesta);

    hoja -> dato = pregunta;
    hoja -> izq = rizq;
    hoja -> der = rder;
  }
}
void Adivinar(ARBOLBINARIO raiz)
{
  char o;
  char tem[MAXLEN];
  ARBOLBINARIO raux = raiz;

  while (raux)
  {
    printf("Estas pensando en un(a) %s?(s/n): ", raux -> dato);
    o = getRespuesta();

    if (o == 's') //Entra en la tematica que el usuario esta pensando
    {
      strcpy(tem, raux -> dato); //tem sera la tematica escogida
      raux = raux -> izq;
      break;
    }
    else //Pasa a otra tematica
      raux = raux -> der;

    system("cls");
  }

  if (!raux)
    printf("No se en que estes pensando:(");

  while (raux) //Empieza el juego. Nodos: Preguntas; Hojas: Respuestas
  {
    if (!(raux -> der) && !(raux -> izq)) //Hoja
    {
      printf("Es %s? (s/n): ", raux -> dato);
      o = getRespuesta();

      if (o == 's')
        puts("Adivine");
      else
      {
        AprenderNuevo(tem, raux);
        raux = raux -> izq;
      }

      raux = raux -> izq; //Es igual si se va a la izquierda o derecha porque es una hoja
    }
    else //Nodo
    {
      printf("%s? (s/n): ", raux -> dato);
      o = getRespuesta();

      if (o == 's') //Si: hijos izquierdos
        raux = raux -> izq;
      else //No: hijos derechos
        raux = raux -> der;
    }
  }

  Pausar("");
}

void CargarArbol(ARBOLBINARIO raiz, char *ftxt, int i)
{
  char *hI = (char *) malloc(50);
  char *hD = (char *) malloc(50);

  i++;
  int j = 0;
  while(ftxt[i] != ',') //Lee hijo izquierdo
  {
   hI[j] = ftxt[i];
   i++;
   j++;
  }
  hI[j] = '\0';

  i++;
  j = 0;
  while(ftxt[i] != ftxt[strlen(ftxt) - 1]) //Lee hijo derecho
  {
   hD[j] = ftxt[i];
   i++;
   j++;
  }
  hD[j] = '\0';

  raiz -> izq = CrearNodo(hI);
  raiz -> der = CrearNodo(hD);
}
void Cargar(ARBOLBINARIO *raiz)
{
  LimpiarArbol(raiz);

  ARBOLBINARIO raux = (*raiz);
  char fName[MAXFTXTLEN]; //Nombre del archivo

  puts("Ingrese el nombre del archivo del que quiera recopilar la informacion");
  gets(fName);
  fflush(stdin);

  FILE *archivo = NULL;
  archivo = fopen(fName, "r");
  if (archivo)
  {
   int i = 0, j = 0; //Indices
   char ftxt[MAXFTXTLEN]; //Texto del archivo

   while (fgets(ftxt, sizeof ftxt, archivo) != NULL) //Lee todo el archivo
   {
     i = j = 0;
     if (raux -> izq && ftxt[0] == '/') //Pasa al hijo derecho
       if (raux -> der) //Solamente pasa si ya existe
         raux = raux -> der;
       else //Lo crea si no exista y pasa
         raux = raux -> der = CrearNodo("na");

     if (ftxt[0] == '/') //Ingresando nueva tematica
     {
       char *raizT = (char *) malloc(MAXLEN);
       char *raizA = (char *) malloc(MAXLEN);

       while (ftxt[i] != '\n')
       {
         if (ftxt[i] != '/')
         {
           raizT[j] = ftxt[i];
           j++;
         }
         i++;
       }
       raizT[j] = '\0';
       raux -> dato = raizT;

       memset(ftxt,0,sizeof(ftxt));
       fgets(ftxt, sizeof ftxt, archivo); //Segunda linea: primer pregunta tematica

       i = j = 0;
       while(ftxt[i] != ':') //Lee raiz
       {
        raizA[j] = ftxt[i];
        i++;
        j++;
       }
       raizA[j] = '\0';

       raux -> izq = CrearNodo(raizA);
       CargarArbol(raux -> izq, ftxt, i);
     }
     else if (ftxt[0] != '\0') //Ingresando preguntas y respuestas de la tematica
     {
       char rz[MAXLEN];

       while(ftxt[i] != ':') //Lee raiz
       {
        rz[j] = ftxt[i];
        i++;
        j++;
       }
       rz[j] = '\0';

       CargarArbol(BuscarHoja(raux, rz), ftxt, i);
     }

     memset(ftxt,0,sizeof(ftxt)); //Limpia ftxt
   }

   fclose(archivo);
    Pausar("Archivo cargado correctamente");
  }
  else
   Pausar("El archivo no existe. Verifique el nombre del archivo (ingrese la extension '.txt' si no la ingreso)");
}

void EscribirArchivo(ARBOLBINARIO raiz, FILE *archivo)
{
  if (raiz -> izq && raiz -> der)
  {
    fprintf(archivo, "%s:%s,%s\n", raiz -> dato, raiz -> izq -> dato, raiz -> der -> dato); //Primer dato raiz, segundo hijo izquierdo, tercero hijo derecho
    EscribirArchivo(raiz -> izq, archivo);
    EscribirArchivo(raiz -> der, archivo);
  }
}
void Guardar(ARBOLBINARIO raiz)
{
  int flg = 0;
  FILE *archivo = NULL;
  archivo = fopen("dflt.txt", "r");

  while (raiz)
  {
    while (!(raiz -> izq -> izq && raiz -> izq -> der)) //Salta tematica que no tenga datos
    {
      raiz = raiz -> der;
      if (!raiz)
        break;
    }
    if (!raiz)
      break;

    if (flg == 0) //Bandera para abrir el archivo en 'w' si es que existen datos y no sobreescribir lo que ya tenga el archivo
    {
      fclose(archivo);
      archivo = fopen("dflt.txt", "w");
    }

    fprintf(archivo, "/%s\n", raiz -> dato);
    EscribirArchivo(raiz -> izq, archivo); //Izquierda preguntas tematica
    raiz = raiz -> der; //Derecha otra tematica

    flg++;
  }

  fclose(archivo);
  archivo = fopen("dflt.txt", "r");
  char nd[MAXLEN];
  fgets(nd, sizeof nd, archivo);
  fclose(archivo);

  if (flg == 0)
    Pausar("No habia datos para guardar");
  else
    Pausar("Archivo guardado correctamente");

}

void CrearNueva(ARBOLBINARIO raiz)
{
  char *tem = (char *) malloc(MAXLEN);
  char *respDflt = (char *) malloc(MAXLEN);
  ARBOLBINARIO raux = raiz;

  while (raux -> der) //Recorre todo el arbol por la derecha hasta donde se ingreso la ultima tematica
    raux = raux -> der;

  puts("Ingrese la nueva tematica (en singular si es el caso)");
  gets(tem);
  fflush(stdin);
  puts("Ingrese la respueta por default para la nueva tematica");
  gets(respDflt);
  fflush(stdin);

  //Crea arbol de la nueva tematica
  raux = raux -> der = CrearNodo(tem);
  raux -> izq = CrearNodo(respDflt);

  Pausar("");
}

//Funcion principal
int main()
{
  int op = 1; //Opcion del menu
  char tem1[MAXLEN] = "Escuela del IPN"; //Primer temática por defecto
  char tem2[MAXLEN] = "Personaje de Marvel"; //Segunda temática por defecto
  char respT1[MAXLEN] = "ESCOM"; //Respuesta por defecto de la primer tematica
  char respT2[MAXLEN] = "Spider Man"; //Respuesta por defecto de la segunda tematica

  ARBOLBINARIO raiz; //Principal raiz (Hijo izquierdo: si; Hijo derecho: no)
  raiz = CrearNodo(tem1); //Crea respuesta por default de la Tematica 1
  raiz -> der = CrearNodo(tem2); //Los hijos derecho de la raiz principal seran las demas tematicas

  system("cls");
  puts("Programa que adivina lo que el usuario este pensando a traves de un arbol binario");

  do
  {
    puts("Escoja una opcion\n-------------------------------");
    puts("1)Adivina lo que estoy pensando\n2)Cargar tematica\n3)Guardar datos\n4)Crear nueva tematica\n0)Salir");
    scanf(" %d", &op);
    fflush(stdin);

    switch(op)
    {
      case 1: //Adivina
        system("cls");
        VerificarArbol(raiz, respT1, respT2); //Inserta respuestas por default si no hay datos en cargados en los arboles
        Adivinar(raiz);
        break;
      case 2: //Cargar arboles ya con informacion
        system("cls");
        Cargar(&raiz);
        break;
      case 3: //Guardar el arbol generado en archivo txt
        if (raiz -> der)
          Guardar(raiz);
        else
          Pausar("No existen datos para guardar");
        break;
      case 4: //Crea nueva tematica
        system("cls");
        VerificarArbol(raiz, respT1, respT2); //Inserta respuestas por default si no hay datos en cargados en los arboles
        CrearNueva(raiz);
        break;
      case 0: break; //Sale del programa
      default:
        Pausar("Opcion no valida");
        break;
    }

    system("cls");

  } while(op != 0);

  return 0;
}
