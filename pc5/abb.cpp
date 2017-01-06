//-------------- DECLARACION DE LAS LIBRERIRAS QUE NECESITAREMOS -------------//

			#include <iostream.h>
			#include <conio.h>
			#include <stdio.h>
			#include <stdlib.h>
			#include <fstream.h>

//--------------------------- FIN DE LA DECLARACION --------------------------//



//--------------- DEFINICION DE LA ESTRUCTURA DE NODO DEL ARBOL --------------//

			struct Nodo
				{
					 int info;
					 Nodo *ProxI;
					 Nodo *ProxD;
				};

//------------------------- FIN DE LA DECLARACION ----------------------------//



//-------------- DEFINICION DE LA ESTRUCTURA DE NODO DE LA COLA --------------//

		typedef struct Nodito
			{
				Nodo *nodo;   // Entero que almacena el nodo_cola
				Nodito *sig;  // Direccion del nodo siguiente
				Nodito *ant;  // Direccion del nodo anterior
			};

//------------------------- FIN DE LA DECLARACION ----------------------------//



//------------------ DECLARACION DE LAS VARIABLES GLOBALES -------------------//

			Nodo *arbol = NULL;
			Nodito *cab = NULL;
			Nodito *col = NULL;
			typedef int bool;
				 const int false = 0;
				 const int true = 1;
			int H[100];   // Array de enteros que almacena a los enteros ingresados
			int A[100];   // Array de enteros que almacena a las info de los
							  // nodos del arbol en forma creciente
			int cont = 1; // Variable contadora

//------------------------- FIN DE LA DECLARACION ----------------------------//



//----------------- DECLARACION DE LAS FUNCIONES EMPLEADAS -------------------//

			void  Agregar_cola (Nodo *T);

			Nodo  *Buscar (Nodo *T , int x);

			void  Camino (Nodo *T , int x);
			bool  Cola_vacia ();
			void  Crear_abb (int n);

			void  Gracias ();

			void  Imprimir_abb (Nodo *T);
			int   Ingresar_data ();
			int   Ingresar_opcion ();
			void  In_orden (Nodo *T);
			void  Insercion_abb (int ele);

			int   Maximo_abb (Nodo *T);
			float Mediana_abb (int n);
			int   Minimo_abb (Nodo *T);
			void  Mostrar_menu ();

			void  Ordenar_abb (Nodo *T);

			void  Remover (int ele);
			Nodo  *Remover_cola ();

//------------------------- FIN DE LA DECLARACION ----------------------------//



//-------------------------- INICIO DEL PROGRAMA -----------------------------//

int main()
  {

	int opcion=0, in=0, ele, n;
	bool salir=false;

	while (!salir)
		 {
		  clrscr();
		  Mostrar_menu ();
		  opcion = Ingresar_opcion ();
		  switch (opcion)
			 {
				 case 1 : {
								n = Ingresar_data ();
								Crear_abb (n);
								++in;
								cout << "\tMENSAJE: Arbol creado, ";
								cout << "presione enter para continuar.";
								getch();
							 }
							 break;
				 case 2 : {
								if (in==0)
								 {
									cout <<"\tMENSAJE: Debe crear el arbol primero,\n"
										  <<"\t         presione enter para continuar.";
									getch();
								 }
								else
								 {
									if (arbol == NULL)
									 {
										cout << "\tMENSAJE: Este arbol esta vacio,"
											  << " presione enter para continuar.";
										getch();
									 }
									else
									 { // Inicio de else
									cout << "\tMENSAJE: Ingrese el dato que desea "
										  << "buscar y presione enter ";
									cin >> ele;
									cout << "\n\n";
									Nodo *tmp = Buscar (arbol , ele);
									if (tmp == NULL)
										cout << "\tMENSAJE: El dato " << ele << " no se "
											  << "encuentra en el arbol,\n"
											  << "\t         ";
									else
										{
										cout << "\tMENSAJE: Dato " << ele << " hallado "
											  << "y el camino de busqueda es:\n\n"
											  << "\t         ";
										Camino (arbol , ele);
										cout << "\n\n";
										cout << "\t         ";
										}
									cout << "presione enter para continuar.";
									getch();
									 } // Fin del else
								 }
							 }
							 break;
				 case 3 : {
								if (in==0)
								 {
									cout <<"\tMENSAJE: Debe crear el arbol primero,\n"
										  <<"\t         presione enter para continuar.";
									getch();
								 }
								else
								 {
									if (arbol == NULL)
									 {
										cout << "\tMENSAJE: Este arbol esta vacio,"
											  << " presione enter para continuar.";
										getch();
									 }
									else
									 {
									cout << "\tMENSAJE: Ingrese el dato que desea "
										  << "remover y presione enter ";
									cin >> ele;
									cout << "\n\n";
									Remover (ele);
									cout << "presione enter para continuar.";
									getch();
									 }
								 }
							 }
							 break;
				 case 4 : {
								if (in==0)
								 {
									cout <<"\tMENSAJE: Debe crear el arbol primero,\n"
										  <<"\t         presione enter para continuar.";
									getch();
								 }
								else
								 { // Inicio del else
								if (arbol == NULL)
								 {
									cout << "\tMENSAJE: Este arbol esta vacio,"
										  << " presione enter para continuar.";
									getch();
								 }
								else
								 {
								cout << "\tResultados del conjunto de datos"
									  << " actual:\n\n\n\t";
								cout << "Recorrido por niveles del arbol:\n\n\t";
								Imprimir_abb (arbol);
								cout <<"\n\n\t";
								cout << "Recorrido en in-orden del arbol:\n\n\t";
								In_orden (arbol);
								cout <<"\n\n\t";
								Ordenar_abb (arbol);
								cout << "Mediana : " << Mediana_abb (cont-1) <<"\n\n\t";
								cont = 1;
								cout << "Maximo  : " << Maximo_abb (arbol) <<"\n\n\t";
								cout << "Minimo  : " << Minimo_abb (arbol) <<"\n\n\n\t";
								cout << "Presione enter para continuar.";
								getch();
								 }
								 } // Fin del else
							 }
							 break;
				 case 5 : {
								Gracias ();
								salir = true;
							 }
							 break;
			 }
		 }

	return 0;
  }

//--------------------------- FIN DEL PROGRAMA -------------------------------//



//----------------- DEFINICION DE LAS FUNCIONES EMPLEADAS --------------------//

	void Agregar_cola (Nodo *T)
		  {
		  Nodito *temp = new Nodito;
		  if (cab == NULL) // En caso sea una cola vacia
			  {
			  col = cab = temp;
			  col->sig = NULL;
			  cab->ant = NULL;
			  }
		  else // En caso que la cola tenga al menos un nodito
			  {
			  col->sig = temp;
			  col->sig->ant = col;
			  col = col->sig;
			  col->sig = NULL;
			  }
		  delete temp; // Liberando memoria
		  col->nodo = T;
		  }

	Nodo *Buscar (Nodo *T, int x)
		  {
		  if (T == NULL)
			  return NULL;
		  else
			  {
			  if (T->info == x)
				  return T;
			  else
				  {
				  if (x < T->info)
					  return Buscar (T->ProxI,x);
				  else
					  return Buscar (T->ProxD,x);
				  }
			  }
		  }

	void Camino (Nodo *arbol , int x)
		  {
		  Nodo* temp = arbol;
		  cout << temp->info ;
		  while (temp != NULL)
				  {
				  if (temp->info == x)
					  break; // Finaliza el while
				  else
					  {
					  if (temp->info < x) temp = temp->ProxD;
					  else temp = temp->ProxI;
					  }
				  cout << " -> " << temp->info ;
				  }
		  }

	bool Cola_vacia ()
		  {
		  if (cab == NULL)
			  return true;
		  else
			  return false;
		  }

	void Crear_abb (int n)
	  {
		  for (int i=1 ; i<=n ; i++)
				Insercion_abb (H[i]);
	  }

	void Gracias ()
	  {
		  printf("\n\n");
		  printf("\t==================== GRACIAS ======================\n");
	  }

	void Imprimir_abb (Nodo *T)
		  {
		  Nodo *temp = new Nodo;
		  Agregar_cola (T);
		  while ( ! Cola_vacia() )
				  {
				  temp = Remover_cola ();
				  cout << temp->info << "\t";
				  if (temp->ProxI != NULL)
					  Agregar_cola (temp->ProxI);
				  if (temp->ProxD != NULL)
					  Agregar_cola (temp->ProxD);
				  }
		  delete temp;
		  }

	int  Ingresar_data ()
	  {
		  ifstream indata; // indata is like cin
		  int num; // variable for input value

		  indata.open("example.dat"); // opens the file

		  indata >> num;
		  int k = 1;
		  while ( !indata.eof() )  // keep reading until end-of-file
			{
			 H[k] = num;
			 k++;
			 indata >> num; // sets EOF flag if no value found
			}
		  --k;
		  indata.close();
		  //cout << "End-of-file reached.." << endl;
		  return k;
	  }

	int  Ingresar_opcion ()
	  {
		  char opcion[100], car;
		  int N=0, op=0;

		  while (op == 0)
			 {
				  printf("\tIngrese su opcion y presione enter: ");
				  while ( ( car = getchar() ) != '\n' )
				  opcion[N++] = car;
				  if (N == 1)
					{
					  car = opcion[0];
					  switch (car)
						{
						 case 'C' : op = 1;
										break;
						 case 'B' : op = 2;
										break;
						 case 'R' : op = 3;
										break;
						 case 'M' : op = 4;
										break;
						 case 'S' : op = 5;
										break;
						 default  : op = 0;
						}
					}
				  N = 0;
				  printf("\n\n");
			 }
		  return op;
	  }

	void In_orden (Nodo *T)
	  {
		  if (T != NULL)
			{
			  In_orden (T->ProxI);
			  cout << T->info << "\t";
			  In_orden (T->ProxD);
			}
	  }

	void Insercion_abb (int ele)
	  {
		  Nodo* T = new Nodo;
		  T->info = ele;
		  T->ProxI = NULL;
		  T->ProxD = NULL;
		  Nodo* padre = NULL;

		  // is this a new tree?
		  if (arbol == NULL)
			  arbol = T;
		  else
			{
			  //Note: ALL insertions are as leaf nodes
			  Nodo* temp = arbol;
			  // Find the Node's parent
			  while (temp != NULL)
				 {
					  padre = temp;
					  if (temp->info < T->info)
						  temp = temp->ProxD;
					  else
						  temp = temp->ProxI;
				 }
			  if (T->info < padre->info)
				  padre->ProxI = T;
			  else
				  padre->ProxD = T;
			}
	  }

	int  Maximo_abb (Nodo *T)
	  {
		  // Se supone que el arbol tiene al menos un nodo, i.e.,
		  // arbol != NULL

		  Nodo* temp = new Nodo;
		  // Almacenamos en la "free store" una variable Nodo temp
		  temp = T;
		  while (temp->ProxD != NULL)
				  // Mientras que temp no sea el nodo mas hacia la derecha del abb
				  temp = temp->ProxD;
		  // Ahora, el nodo con el maximo info es temp
		  int max = temp->info; // Asignando a max el info de temp
		  delete temp; // Liberando espacio de la "free store"
		  return (max);
	  }

	float Mediana_abb (int n)
	  {
			// Se supone que el arbol tiene al menos un nodo, i.e.,
			// arbol != NULL

			float med; // Varialbe que almacena la mediana del conjunto de datos

			div_t num;
			num = div (n,2);
			int q = num.quot; // Asignando a k el cociente entero de N/2
			int r = num.rem;  // Asignando a r el resto de N/2

			if (r == 0) // Si N es par
				med = ( A[q] + A[q+1] ) / 2.0 ;
			else // Si N es impar
			 {
				med = A[q+1] + 0.0 ;
			 }
			return (med);
	  }

	int  Minimo_abb (Nodo *T)
	  {
		  // Se supone que el arbol tiene al menos un nodo, i.e.,
		  // arbol != NULL

		  Nodo *temp = new Nodo;
		  // Almacenamos en la "free store" una variable Nodo temp
		  temp = T;
		  while (temp->ProxI != NULL)
				  // Mientras que temp no sea el nodo mas hacia la izquierda del abb
				  temp = temp->ProxI;
		  // Ahora, el nodo con el minimo info es temp
		  int min = temp->info; // Asignando a min el info de temp
		  delete temp; // Liberando espacio de la "free store"
		  return (min);
	  }

	void Mostrar_menu ()
	  {
		  printf("\n\n");
		  printf("\t###########################################################\n");
		  printf("\t#                                                         #\n");
		  printf("\t#              =============================              #\n");
		  printf("\t#                        PROGRAMA :                       #\n");
		  printf("\t#               ARBOL BINARIO DE BUSQUEDA                 #\n");
		  printf("\t#              =============================              #\n");
		  printf("\t#                                                         #\n");
		  printf("\t#                         MENU:                           #\n");
		  printf("\t#                                                         #\n");
		  printf("\t#      (C)  :  Crear arbol binario de busqueda (abb)      #\n");
		  printf("\t#      (B)  :  Buscar un dato                             #\n");
		  printf("\t#      (R)  :  Remover un dato                            #\n");
		  printf("\t#      (M)  :  Mostrar calculos                           #\n");
		  printf("\t#      (S)  :  Salir                                      #\n");
		  printf("\t#                                                         #\n");
		  printf("\t###########################################################\n");
		  printf("\n\n\n");
	  }

	void Ordenar_abb (Nodo *T)
	  {
		  if (T != NULL)
			{
			  Ordenar_abb (T->ProxI);
			  A[cont++] = T->info;
			  Ordenar_abb (T->ProxD);
			}
	  }

	void Remover (int ele)
	  {
		  // Se supone que el arbol tiene al menos un nodo, i.e.,
		  // arbol != NULL

		  // Inicio de la busqueda del elemento "ele"
		  bool found = false;
		  Nodo* temp = arbol;
		  Nodo* padre = NULL;
		  while (temp != NULL)
			  {
				  if (temp->info == ele)
					{
					  found = true;
					  break;
					}
				  else
					{
					  padre = temp;
					  if (temp->info < ele) temp = temp->ProxD;
					  else temp = temp->ProxI;
					}
			  }
		  // Fin de la busqueda

		  // Resultado:
		  if (!found)
			  cout << "\tMENSAJE: El dato " << ele << " no se "
					 << "encuentra en el arbol,\n"
					 << "\t         ";

		  else { // Inicio del primer else
		  // Hay 3 casos :
		  // CASO 1: Estamos removiendo un nodo sin hijos.
		  // CASO 2: Estamos removiendo un nodo con un solo hijo.
		  // CASO 3: Estamos removiendo un nodo con dos hijos.

		  // CASO 1:
		  if (temp->ProxI == NULL  &&  temp->ProxD == NULL)
			{
			  if (padre == NULL) // temp es el nodo raiz
				{
				  arbol = NULL;
				  delete temp;
				}
			  else
				{ // Inicio del segundo else
			  if (padre->ProxI == temp) // temp es hijo izquierdo
				  padre->ProxI = NULL;
			  else // temp es hijo derecho
				  padre->ProxD = NULL;
			  delete temp;
				} // Fin del segundo else
			}

		  // CASO 2:
		  if ( (temp->ProxI == NULL  &&  temp->ProxD != NULL)
											  ||
				 (temp->ProxI != NULL  &&  temp->ProxD == NULL) )
			{
			  if (temp->ProxI == NULL  &&  temp->ProxD != NULL)
					 // temp tiene hijo derecho pero no izquierdo
				{
				  if (padre == NULL)
					{
					  arbol = temp->ProxD;
					  delete temp;
					}
				  else
					{ // Inicio del tercer else
				  if (padre->ProxI == temp) // si temp es hijo izquierdo
					{
					  padre->ProxI = temp->ProxD;
					  delete temp;
					}
				  else // si temp es hijo derecho
					{
					  padre->ProxD = temp->ProxD;
					  delete temp;
					}
					} // Fin del tercer else
				}
			  else // temp tiene hijo izquierdo pero no derecho
				{
				  if (padre == NULL) // temp es el nodo raiz
					{
					  arbol = temp->ProxI;
					  delete temp;
					}
				  else
					{ // Inicio del cuarto else
				  if (padre->ProxI == temp) // temp es hijo izquierdo
					{
					  padre->ProxI = temp->ProxI;
					  delete temp;
					}
				  else // temp es hijo derecho
					{
					  padre->ProxD = temp->ProxI;
					  delete temp;
					}
					} // Fin del cuarto else
				}
			}

		  // CASO 3:
			  // Reemplazar la info de temp con la info de la hoja mas izquiesda
			  // del subarbol izquierdo del hijo derecho de temp
		  if (temp->ProxI != NULL  &&  temp->ProxD != NULL)
			{
			  Nodo* hijoDtemp = temp->ProxD;

			  if ( (hijoDtemp->ProxI == NULL) && (hijoDtemp->ProxD == NULL))
				{
				  temp = hijoDtemp;
				  delete hijoDtemp;
				  temp->ProxD = NULL;
				}
			  else // Hijo derecho del nodo temp, hijoDtemp, tiene hijo(s)
				{
				  // Si hijoDtemp tiene un hijo izquierdo, localizar el
				  // menor descendiente, llamemoslo min, de hijoDtemp
				  if ((temp->ProxD)->ProxI != NULL)
					{
					  Nodo* min = (temp->ProxD)->ProxI;
					  Nodo* tmp = temp->ProxD;
					  while (min->ProxI != NULL)
						  {
							  tmp = min;
							  min = min->ProxI;
						  }
					  temp->info = min->info;
					  tmp->ProxI = min->ProxD;
					  delete min;
					}
				  else
					{
					  Nodo* tmp = temp->ProxD;
					  temp->info = tmp->info;
					  temp->ProxD = tmp->ProxD;
					  delete tmp;
					}
				}
			}
		  cout << "\tMENSAJE: El dato " <<ele<< " ha sido removido del arbol,\n";
		  cout << "\t         ";
		  } // Fin del primer else
	  }

	Nodo *Remover_cola () // Retorna el dato del nodito cab
		  { // Se supone que cab != NULL
		  Nodo *eli = cab->nodo;
		  if (cab->sig == NULL)
			  cab = col = NULL;
		  else
			  {
			  cab = cab->sig;
			  // El nuevo nodito cab sera el nodo siguiente a cab
			  cab->ant = NULL;
			  // Estableciendo que cab sera ahora la cabeza de la cola
			  }
		  return eli;
		  }

//-------------------------- FIN DE LA DEFINICION ----------------------------//

