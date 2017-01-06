//----------------- DECLARACION DE LAS LIBRERIRAS QUE NECESITAREMOS --------------// 

						#include <stdio.h>
						#include <iostream>
						 using std::cin;

//----------------------------- FIN DE LA DECLARACION ----------------------------//




//-------------------- DEFINICION DE LA ESTRUCTURA DE UN NODO --------------------//

		typedef struct Nodo 
			{
				char info;   // Caracter que almacena el nodo
				Nodo *sig;  // Direccion del nodo siguiente
				Nodo *ant;  // Direccion del nodo anterior
			} 
		Nodo;

//--------------------------- FIN DE LA DEFINICION -------------------------------//




//-------------------- DECLARACION DE LAS VARIABLES GLOBALES ---------------------//

	// Definimos las listas que usaremos:
	// cabeza y nodo de la lista que almacenara la cadena de caracteres ingresada
		Nodo *cabeza; 
		Nodo *cola;
	// cabeza y nodo de la listaR que almacenara el resultado despues de la 
	// primera etapa
		Nodo *cabezaR;
		Nodo *colaR;
	    char pila[100];
	    char cad[100];	

//----------------------------- FIN DE LA DECLARACION -----------------------------//




//-------------------- DECLARACION DE LAS FUNCIONES EMPLEADAS ---------------------//

void Agregar_nodo (char car); 
void Agregar_nodoR (char car);

void Borrar_cadena ();
void Borrar_resultado ();

bool Es_vocal (char car);

void Gracias ();

void Ingresar_cadena ();
int  Ingresar_opcion ();
void Iniciar_listas ();
void Invertir ();

void Mostrar_cadena ();
void Mostrar_menu ();
void Mostrar_resultado ();

void Program_enc ();
	                      
//------------------------------- FIN DE LA DECLARACION -----------------------------//




//-------------------------------- INICIO DEL PROGRAMA ------------------------------//
		
int main() 
  {
	Program_enc ();
	return 0;
  }
    
//---------------------------------- FIN DEL PROGRAMA -------------------------------//




// ----------------------- DEFINICION DE LAS FUNCIONES EMPLEADAS --------------------//

void Agregar_nodo (char car) 
     {
		if (cabeza == NULL) 
		   {
			cabeza = new Nodo;
			cola = cabeza;
			cola->sig = NULL;
			cabeza->ant = NULL;
    	   } 
	    else 
		   {
			cola->sig = new Nodo;
			cola->sig->ant = cola;
			cola = cola->sig;
			cola->sig = NULL;
		   }
		cola->info = car;	
	 }	 
	 

void Agregar_nodoR (char car) 
     {
		if (cabezaR == NULL) 
		   {
			cabezaR = new Nodo;
			colaR = cabezaR;
			colaR->sig = NULL;
			cabezaR->ant = NULL;
    	   } 
	    else 
		   {
			colaR->sig = new Nodo;
			colaR->sig->ant = colaR;
			colaR = colaR->sig;
			colaR->sig = NULL;
		   }
		colaR->info = car;
	 }
	 
void Borrar_cadena () // Borra la lista ingresada
     {
		Nodo *temp = cabeza;
		Nodo *eli = NULL;
		
		while (temp != NULL) 
			  {
				eli = temp;
				temp = temp->sig;
				delete eli;
     	      }
		cabeza = NULL;
		cola = NULL;
     }
     
void Borrar_resultado () // Borra resultado
     {
		Nodo *temp = cabezaR;
		Nodo *eli = NULL;
		
		while (temp != NULL) 
			  {
				eli = temp;
				temp = temp->sig;
				delete eli;
     	      }
		cabezaR = NULL;
		colaR = NULL;
     }

bool Es_vocal (char car)
     {
		bool vocal = true; 
		switch (car)
		       {
				   case'a' : case'e' : case'i' : case'o' : case 'u' :
				   case'A' : case'E' : case'I' : case'O' : case 'U' : break;
				   default  : vocal = false;
			   }
		return vocal; 
	 }
	 
void Gracias ()
     {
	    printf("\n\n");
	    printf("\t==================== GRACIAS ======================\n");	 
	 }
	 
void Ingresar_cadena () // procedimiento para ingresar la cadena
	 {
	    char car;
	    printf("\tIngrese una cadena de caracteres y "); 
	    printf("presione enter:\n\n\n\tCadena = ");
		while ( (car = getchar()) != '\n' )
		      Agregar_nodo (car); // almacenando cada caracter en un nodo 
		printf("\n\n");
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
			   case 'I' : op = 1;
			              break;
		       case 'M' : op = 2; 
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

void Iniciar_listas () // iniciando la lista
     {
		cabeza = cola = NULL; 
		cabezaR = colaR = NULL;
     }

void Invertir ()
     {
		Nodo *temp = cabeza;
		char car;
		int cont=0;
		
		while (temp != NULL) 
	        {
			  car = temp->info;
			  	
			  if (Es_vocal (car))
			   {
				 if (cont>0)
				  {
					for (int i=cont-1 ; 0<=i ; i--)
				        Agregar_nodoR (pila[i]);
				    cont = 0;
				  }  
				 Agregar_nodoR (car);  
			   }   
			  else
			  	 pila[cont++] = car;
			  temp = temp->sig;
	        } 
	    if (cont>0)
		 {
		   for (int i=cont-1 ; 0<=i ; i--)
			   Agregar_nodoR (pila[i]);
		   cont = 0;
		 } 
	 }

void Mostrar_cadena () // Muestra la cadena ingresada
     {
		Nodo *temp = cabeza;
		Nodo *imp = NULL;
	    printf("\tCadena = ");
		while (temp != NULL) 
	        {
			  imp = temp;
			  temp = temp->sig;
			  printf("%c",imp->info);
	        }
	    printf("\n\n\n");
	 }
	
void Mostrar_menu ()
	 {
      printf("\n\n");
	  printf("\t###################################################\n");
	  printf("\t#                                                 #\n"); 
	  printf("\t#         ============================            #\n"); 
      printf("\t#                   PROGRAMA :                    #\n");
	  printf("\t#          ENCRIPTAMIENTO DE MENSAJES             #\n");
	  printf("\t#         ============================            #\n");
	  printf("\t#                                                 #\n");  
	  printf("\t#                     MENU:                       #\n");
	  printf("\t#                                                 #\n");
	  printf("\t#         (I)  :  Ingresar mensaje                #\n");
	  printf("\t#         (M)  :  Mostrar Resultado               #\n");
	  printf("\t#         (S)  :  Salir                           #\n");
	  printf("\t#                                                 #\n");
	  printf("\t###################################################\n");
	  printf("\n\n\n");
     }
      
void Mostrar_resultado () // Muestra la cadena encriptada
     {
		Nodo *temp = colaR;
		Nodo *imp = NULL;
	    printf("\tCadena encriptada = ");
		while (temp != NULL) 
	        {
			  imp = temp;
			  temp = temp->ant;
			  printf("%c",imp->info);
	        }
	    printf("\n\n\n");
	 }
	
void Program_enc ()
   {
	 int opcion = 0; 
	 bool salir = false;
	 bool ingresado = false;
		
	 Iniciar_listas ();
	 while (!salir)
	     {
		   Mostrar_menu ();
		   opcion = Ingresar_opcion ();
		   switch (opcion)
                {
			      case 1 : {
							   Borrar_cadena ();
							   Ingresar_cadena (); 
							   ingresado = true;
			               }
			               break;
			      case 2 : {
							   if (ingresado)
							    {
								  Invertir ();
								  printf("\tResultados:\n\n\n");
							      Mostrar_cadena ();
					              Mostrar_resultado ();
                                  Borrar_resultado ();
							    }
							   else
							      printf("\tERROR: No ha ingresado cadena alguna.\n\n\n");
						   } 
						   break;
		          case 3 : {
					           Gracias ();  
							   salir = true; 
						   } 
						   break;
			    }
		 }
     Borrar_cadena ();
     Borrar_resultado ();
   }
	 
//---------------------------- FIN DE LA DEFINICION ---------------------------------//
