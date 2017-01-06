//----------------- DECLARACION DE LAS LIBRERIRAS QUE NECESITAREMOS --------------// 


#include <ctime>
#include <math.h>
#include <iostream.h>
#include <iostream>
using std::cerr;
using std::cout;
using std::cin;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstdlib> // for exit function

    // This program reads values from the file 'example.dat'
    // and echoes them to the display until a negative value
    // is read.

//----------------------------- FIN DE LA DECLARACION ----------------------------//



//-------------------- DECLARACION DE LAS VARIABLES GLOBALES ---------------------//
    
int H[100]; // Arreglo de enteros que almacenara los mismos ingresados
int cont=0; // Contador de los intercambios de elementos del vector A

//----------------------------- FIN DE LA DECLARACION -----------------------------//



//-------------------- DECLARACION DE LAS FUNCIONES EMPLEADAS ---------------------//

int  Crear_heap (int n);

void Gracias ();

void Heapsort (int n);

int  Ingresar ();
void Imprimir (int n);
int  Insertar (int x, int n);
int  Ingresar_opcion ();

void Mostrar_menu ();

void Programa_a ();
void Programa_b ();

int  Remover (int n);

//------------------------------- FIN DE LA DECLARACION -----------------------------//



//-------------------------------- INICIO DEL PROGRAMA ------------------------------//

int main()
  {
	int opcion = 0; 
	bool salir = false;
		
	while (!salir)
	    {
		   Mostrar_menu ();
		   opcion = Ingresar_opcion ();
		   switch (opcion)
                {
			      case 1 : {
							   Programa_a ();
			               } 
			               break;
			      case 2 : {
							   Programa_b ();
						   } 
						   break;
				  case 3 : {
					           Gracias ();  
							   salir = true; 
						   } 
						   break;
			    }
		 }

	return 0;
  }
  
//---------------------------------- FIN DEL PROGRAMA -------------------------------//



// ----------------------- DEFINICION DE LAS FUNCIONES EMPLEADAS --------------------//

int Crear_heap (int n)
   {
	 int N=0;  
	 for (int i=1 ; i<=n ; i++)
	   	 N = Insertar (H[i],N);  
	 return N;
   }

void Gracias ()
     {
	    printf("\n\n");
	    printf("\t==================== GRACIAS ======================\n");	 
	 }
	 
void Heapsort (int n)
   {
     int N = Crear_heap (n);
	 for (int i=1 ; i<=n ; i++)
	   {
		 int temp = H[1];
		 N = Remover (N);
		 H[N+1] = temp;
	   }
   }
 
int Insertar (int x, int n)
  { 
	n++; 
	int son = n;
	int dad = son/2;
	bool up = true;
	while ( (dad>0) && (up) )
	    {
		  if (H[dad] >= x)
		     up = false;
		  else
		   {
		     H[son] = H[dad];
		     H[dad] = x;
		     son = dad;
		     dad = son/2;
		     cont++;
		   }  	
		} 
	H[son] = x;
	return n;
  }

int Ingresar ()
  {
	int n;   
    cout << "\tIngrese el tamanio, n, del vector A que va ordenar.\n\n\tn: ";
    cin >> n; 
    cout << "\n\tIngrese cada elemento de A presionando enter por cada uno.\n\n";
    for (int i=1 ; i<=n ; i++)
      {
		printf("\tA[%d] = ",i);
		cin >> H[i];
		cout << "\n";  
	  }
	cout << "\n\n"; 
	return n; 
  }
   
void Imprimir (int n)
   {
	 cout << "\t";  
	 for (int i=1 ; i<=n ; i++)
	     cout << H[i] << " ";
	 cout << "\n\n";
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
			   case 'A' : op = 1;
			              break;
		       case 'B' : op = 2; 
						  break;
		       case 'S' : op = 3; 
						  break;
		       default  : op = 0;
			  }
		    }
	       N = 0;
	       printf("\n\n");
	     }
	 return op;
  }   
  
void Mostrar_menu ()
	 {
      printf("\n\n");
	  printf("\t###################################################\n");
	  printf("\t#                                                 #\n"); 
	  printf("\t#        ===============================          #\n"); 
      printf("\t#                   PROGRAMA :                    #\n");
	  printf("\t#        PREGUNTA 3 DE LA 4ta CALIFICADA          #\n");
	  printf("\t#        ===============================          #\n");
	  printf("\t#                                                 #\n");  
	  printf("\t#                     MENU:                       #\n");
	  printf("\t#                                                 #\n");
	  printf("\t#         (A)  :  Subprograma (a)                 #\n");
	  printf("\t#         (B)  :  Subprograma (b)                 #\n");
	  printf("\t#         (S)  :  Salir                           #\n");
	  printf("\t#                                                 #\n");
	  printf("\t###################################################\n");
	  printf("\n\n\n");
     }
      
void Programa_a ()
   {
	 int n = Ingresar ();
	 cout << "\tArreglo ingresado:\n\n";
	 Imprimir (n);
	 Heapsort (n);
	 cout << "\n\n";
	 cout << "\tArreglo ordenado:\n\n";
	 Imprimir (n); 
	 cont = 0; 
   } 

void Programa_b ()
   {
	 srand((unsigned)time(0));
     int T,n; 
     double P,Q;
     
	 for (int k=2 ; k<10 ; k=k+2)
	   {
		 n = pow(2,k);    
         for (int i=1; i<=n ; i++)
             H[i] = (rand()%1000) + 1;
         Heapsort (n);
         T = cont;
         cont = 0;
         P=T ; Q=n*k;      
         printf("\tn = %d \t\t T = %d \t\t T/(n*log_{2}n) = %4.2f \n\n",n,T,P/Q);
       }
   } 

int  Remover (int n)
  {
	 int aux = H[n];
	 int dad = 1;
	 int son = 2;
	 bool down = true;
	 while ( (son<=n) && (down) )
	    {
	      if (son<n)
	       {
			 if (H[son] < H[son+1])
			    ++son;  
		   }
		  if (H[son] <= aux)
		     down = false;
		  else
		   {
			 H[dad] = H[son];
			 dad = son;
			 son = 2*son;
			 cont++;
		   } 
		}
	 H[dad] = aux;
	 return --n;
  }

//---------------------------- FIN DE LA DEFINICION ---------------------------------//
