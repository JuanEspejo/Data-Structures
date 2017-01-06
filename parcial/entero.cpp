//================================================================================//
//                                                                                //
//                                                                                //
//                          ============================                          // 
//                                   PROGRAMA :                                   //
//                           "OPERANDO ENTEROS GRANDES"                           //
//                          ============================                          //
//                                                                                //
//                                                                                //
//                                                                                //      
//      Copyright 2010 juanca <juanca@juanca-laptop>                              // 
//                                                                                //  
//      This program is free software; you can redistribute it and/or modify      //
//      it under the terms of the GNU General Public License as published by      //
//      the Free Software Foundation; either version 2 of the License, or         //
//      (at your option) any later version.                                       //
//                                                                                //      
//      This program is distributed in the hope that it will be useful,           //
//      but WITHOUT ANY WARRANTY; without even the implied warranty of            // 
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             //
//      GNU General Public License for more details.                              //
//                                                                                //     
//      You should have received a copy of the GNU General Public License         //
//      along with this program; if not, write to the Free Software               // 
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,                //
//      MA 02110-1301, USA.                                                       //
//                                                                                //
//      Lima, Sunday 16th, May 2010.                                              //
//                                                                                //
//                                                                                //
//================================================================================//


//----------------- DECLARACION DE LAS LIBRERIRAS QUE NECESITAREMOS --------------// 

						#include <stdio.h>
						#include <math.h>

//----------------------------- FIN DE LA DECLARACION ----------------------------//




//-------------------- DEFINICION DE LA ESTRUCTURA DE UN NODO --------------------//

		typedef struct Nodo 
			{
				int info;     // Informacion que contiene el nodo
				int grado;    // grado de la base
				Nodo *sig;  // Direccion del nodo siguiente
				Nodo *ant;  // Direccion del nodo anterior
			} 
		Nodo;

//--------------------------- FIN DE LA DEFINICION -------------------------------//




//-------------------- DECLARACION DE LAS VARIABLES GLOBALES ---------------------//

	// Definimos las listas que usaremos:
	// cabeza y nodo de la lista1 que almacenara al primer entero
		Nodo *cabeza1; 
		Nodo *cola1;
	// cabeza y nodo de la lista2 que almacenara al primer entero	
		Nodo *cabeza2;
		Nodo *cola2;
	// cabeza y nodo de la listaR que almacenara el resultado de operar
	// los dos enteros ingresados
		Nodo *cabezaR;
		Nodo *colaR;

		char resultado[100]; // cadena de caracteres que se mostrara
		int ind=0; // numeros de caracteres de la cadena a mostrar
		int min=2;

		char entero1[100];
		int index1 = 0;

		char entero2[100];
		int index2 = 0;
		
		int opcion = 0;

//----------------------------- FIN DE LA DECLARACION -----------------------------//




//-------------------- DECLARACION DE LAS FUNCIONES EMPLEADAS ---------------------//

		char A_char (int n);
		int  A_entero (char car);
		void Agregar_nodo1 (int valor); 
		void Agregar_nodo2 (int valor); 
		void Agregar_nodoR (int valor); 

		void Borrar_entero1 (); 
		void Borrar_entero2 (); 
		void Borrar_resultado (); 
	
		void Convertir_pb (int N);
		void Convertir (int N);

		void Depurar_resultado ();
		void Dif ();
									
		void Gracias (); 
		
		void Ingresar_entero1 ();
		void Ingresar_entero2 ();
		void Ingresar_opcion ();
		void Iniciar_listas ();

		void Leer_entero1 (); 
		void Leer_entero2 ();
		void Leer_instrucciones ();
		
		void Minimo ();
		void Mostrar_entero1 (); 
		void Mostrar_entero2 (); 
		void Mostrar_menu ();    
		void Mostrar_resultado ();

		void Restar_enteros ();
		
		void Sum ();
		void Sumar_enteros ();
		
//------------------------------- FIN DE LA DECLARACION -----------------------------//




//-------------------------------- INICIO DEL PROGRAMA ------------------------------//
		
int main() 
    {
		int cont1=0, cont2=0; 
		
		Iniciar_listas ();
		
		while (opcion != 9)
			{
			  Mostrar_menu ();
			  Ingresar_opcion ();
              switch (opcion)
                   {
					 case 1 : Leer_instrucciones (); break;
					 case 2 : {
								if (cont1 == 0) {
								Ingresar_entero1 ();
								Leer_entero1 (); 
								cont1++; }
								else printf("\n\n\n\tERROR : No ha eliminado N1.");
							  }	
							  break;
					 case 3 : {
								if (cont1 == 1) {
								Mostrar_entero1 ();
								Borrar_resultado (); }
								else printf("\n\n\n\tERROR : No ha ingresado N1.");
							  }	
							  break;
					 case 4 : {
								if (cont1 == 1) {
								Borrar_entero1 (); 
								cont1--; 
								printf("\n\n\n\tMENSAJE: N1 borrado."); }
								else printf("\n\n\n\tERROR : No ha ingresado N1.");
							  }
							  break;
					 case 5 : {
								if (cont2 == 0) {
								Ingresar_entero2 ();
								Leer_entero2 (); 
								cont2++; }
								else printf("\n\n\n\tERROR : No ha eliminado N2."); 
							  }	
								break;
					 case 6 : {
								if (cont2 == 1) {
								Mostrar_entero2 ();
								Borrar_resultado (); }
								else printf("\n\n\n\tERROR : No ha ingresado N2.");
							  }	
							  break;
					 case 7 : {
								if (cont2 == 1) {
								Borrar_entero2 (); 
								cont2--; 
								printf("\n\n\n\tMENSAJE: N2 borrado."); }
								else printf("\n\n\n\tERROR : No ha ingresado N2.");
							  }
							  break;
					 case 8 : {
								if ( (cont1 == 1) & (cont2 == 1) ) 
								 {
								   printf("\n\n\n\tENTEROS INGRESADOS:");
								   Mostrar_entero1 ();
								   Borrar_resultado ();
								   Mostrar_entero2 ();
								   Borrar_resultado ();
								   printf("\n\n\n\n");
								   
								   printf("\tRESULTADOS:\n\n\n");	 
								   Minimo ();
								   printf("\t min {|N1|,|N2|} = ");
								   Mostrar_resultado ();
								   Borrar_resultado (); 
								   printf("\n\n");
								   
 								   Sumar_enteros ();
								   Depurar_resultado ();
								   printf("\t N1 + N2 = ");
								   Mostrar_resultado ();
								   Borrar_resultado (); 
								   printf("\n\n");
 								
								   Restar_enteros ();
								   Depurar_resultado ();
								   printf("\t N1 - N2 = ");
								   Mostrar_resultado ();
								   Borrar_resultado (); 
								   printf("\n\n");
								   
								   min = 2;
								 }
								else printf("\n\n\n\tERROR : No ha ingresado N1 y N2.");
							  }	
							  break;
					 default: Gracias ();
				   }
			}
		
		// liberando memoria	
		Borrar_entero1(); 
		Borrar_entero2(); 
		
		return 0;
    }
    
//---------------------------------- FIN DEL PROGRAMA -------------------------------//




// ----------------------- DEFINICION DE LAS FUNCIONES EMPLEADAS --------------------//


char A_char (int n) // transforma un numero entero a un caracter
	 {
		char car;
		switch (n)
		       {
				   case 0 : car = '0'; break;
				   case 1 : car = '1'; break;
				   case 2 : car = '2'; break;
				   case 3 : car = '3'; break;
				   case 4 : car = '4'; break;
				   case 5 : car = '5'; break;
				   case 6 : car = '6'; break;
				   case 7 : car = '7'; break;
				   case 8 : car = '8'; break;
				   case 9 : car = '9'; break;
			   }
		return car;
	 }


int A_entero (char car) // transforma un caracter al numero entero que representa
	 {
		int n;
		switch (car)
		       {
				   case '0' : n = 0; break;
				   case '1' : n = 1; break;
				   case '2' : n = 2; break;
				   case '3' : n = 3; break;
				   case '4' : n = 4; break;
				   case '5' : n = 5; break;
				   case '6' : n = 6; break;
				   case '7' : n = 7; break;
				   case '8' : n = 8; break;
				   case '9' : n = 9; break;
			   }
		 return n;
	  }


void Agregar_nodo1 (int valor) // Agrega un nodo a la lista, resultado
     {
		// Si cabeza1 es NULL, entonces este también el último nodo
		if (cabeza1 == NULL) 
		   {
			// Designando memoria
			cabeza1 = new Nodo;
			// El último Nodo es igual al primer
			cola1 = cabeza1;
			// No hay Nodo antes del Nodo cabeza
			// y después del Nodo cola tampoco
			cola1->sig = NULL;
			cabeza1->ant = NULL;
    	   } 
	    else 
		   {
			cola1->sig = new Nodo;
			cola1->sig->ant = cola1;
			cola1 = cola1->sig;
			cola1->sig = NULL;
		   }
		cola1->info = valor;
		if (cola1->ant == NULL) 
		    cola1->grado = -1;
		else
		    cola1->grado = cola1->ant->grado + 1;	
	 }


void Agregar_nodo2 (int valor) 
     {
		if (cabeza2 == NULL) 
		   {
			cabeza2 = new Nodo;
			cola2 = cabeza2;
			cola2->sig = NULL;
			cabeza2->ant = NULL;
    	   } 
	    else 
		   {
			cola2->sig = new Nodo;
			cola2->sig->ant = cola2;
			cola2 = cola2->sig;
			cola2->sig = NULL;
		   }
		cola2->info = valor;
		if (cola2->ant == NULL) 
		    cola2->grado = -1;
		else
		    cola2->grado = cola2->ant->grado + 1;	
	 }	 
	 

void Agregar_nodoR (int valor) 
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
		colaR->info = valor;
		if (colaR->ant == NULL) 
		    colaR->grado = -1;
		else
		    colaR->grado = colaR->ant->grado + 1;	
	 }	
	 
	 
void Borrar_entero1 () // Borra  N1
     {
		Nodo *temp = cabeza1;
		Nodo *eli = NULL;
		
		while (temp != NULL) 
			  {
				eli = temp;
				temp = temp->sig;
				delete eli;
     	      }
		cabeza1 = NULL;
		cola1 = NULL;
     }


void Borrar_entero2 () // Borra  N2
     {
		Nodo *temp = cabeza2;
		Nodo *eli = NULL;
		
		while (temp != NULL) 
			  {
				eli = temp;
				temp = temp->sig;
				delete eli;
     	      }
		cabeza2 = NULL;
		cola2 = NULL;
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
     

void Convertir_pb (int N)  // convierte colaR->info a una cadena de caracteres
	 {
		int d=100,q;
		q = N/d; 
		if (q != 0) 
		   {
			resultado[ind++] = A_char(q);
		
			N = N - d*q;
			d = d/10;
			q = N/d;
			resultado[ind++] = A_char(q);
			
			N = N - d*q;
			resultado[ind++] = A_char(N);
			resultado[ind++] = ' ';
		   }
		else 
		   {  
			d = d/10;
			q = N/d;
			if (q != 0) resultado[ind++] = A_char(q);
			N = N - d*q;
			resultado[ind++] = A_char(N);
			resultado[ind++] = ' ';  
		   }
	 }

void Convertir (int N) // convierte NodoR->info a una cadena de caracteres
	 {
		int d=100,q;
	
		q=N/d;
		resultado[ind++] = A_char(q);
		
		N = N - d*q;
		d = d/10;
		q = N/d;
		resultado[ind++] = A_char(q);
		
		N = N - d*q;
		resultado[ind++] = A_char(N);
		resultado[ind++] = ' ';
	 }
	 

void Depurar_resultado () // depura el resultado con el fin de expresarlo correctamente
     {
		Nodo *temp = colaR;
		Nodo *eli = NULL;
		
		while ( temp->info == 0 )
			  {
				colaR = temp->ant;
				colaR->sig = NULL;
				eli = temp;
				delete eli;
				temp = colaR;
			  }
		if ( temp->ant == NULL ) 
		   {
		    cabezaR->info = 1; 
		    Agregar_nodoR(0);
		   }
     }
     

void Dif() // guarda  |  |N1| - |N2|  |   en la lista resultado
	 {
		Nodo *temp1 = NULL;
		Nodo *temp2 = NULL;
		int N1, N2, N, ad=0;
		
		if (min == 1)
		   {
			temp1 = cabeza1->sig;
			temp2 = cabeza2->sig;
		   }
		else
		   {
			temp1 = cabeza2->sig;
			temp2 = cabeza1->sig;
		   }
		
		Agregar_nodoR(1);
		while ( temp2 != NULL )
			  {
			    if (temp1 != NULL) N1 = temp1->info;
			    else N1=0;
			    N2 = temp2->info;
			    
			    N = N2 - N1 + ad;
			    if (N < 0) 
				   {
				    Agregar_nodoR(N+1000);
				    ad=-1;
				   }
				else 
				   {
				    Agregar_nodoR(N);
				    ad=0;
				   }
				if (temp1 == NULL) 
				    temp1 = NULL;
				else temp1 = temp1->sig;
				temp2 = temp2->sig;
			  }
	 }
	 

void Gracias ()
     {
	  printf("\n\n");
	  printf("\t==================== GRACIAS ======================\n");	 
	 }
	 
	
void Ingresar_entero1 () // procedimiento para ingresar el entero N1
	 {
		int index = 0, error = 0, p = 1, cont = 0, ne = 0, cont0 = 0;
		int pp = 0;
		char car;
		
		while (p<2) // cuando el ingreso sea válido, p=2
		      {
			    if (error == 1) 
			       printf("\tERROR : Ingreso incorrecto.\n\n");
			    error = 0;
			    printf("\n\n\n");
			    printf("\tIngrese el primer entero, N1, y "); 
			    printf("presione enter:\n\n\n\tN1 = ");
			    while ( ( car = getchar() ) != '\n' )
				      entero1[index++] = car;
			    printf("\n\n");
			    
			    for ( int i=0 ; i<index ; i++ )
                    {
					  car = entero1[i];
					  switch (car)
						{
						 case ' ' :  break;
						 case '-' :  {
								     if ( (cont > 0) || (ne > 0) ) 
									    { 
										  error = 1; 
										  i = index;
									    }
									 ne++;
									 }
								     break;
						 case '0' :  {
									 if ( (cont == 0) || ( (cont == 0) & (cont0 > 0) )  )
										    { 
											  error = 1; 
											  i = index;
										    }
										 cont0++;
									 }
									 break;
						 case '1' :  cont++; break;
						 case '2' :  cont++; break;  
						 case '3' :  cont++; break;
						 case '4' :  cont++; break;
						 case '5' :  cont++; break;
						 case '6' :  cont++; break;
						 case '7' :  cont++; break;
						 case '8' :  cont++; break;
						 case '9' :  cont++; break;
						 default  :  { 
									  error = 1; 
									  i = index; 
									 }
							 }	 
				    }
			    if ( error == 0 ) 
			        {
					  if ( (ne == 1) & (cont0 == 0) & (cont == 0) )
					     {
					       error = 1;
						   ne = 0;
						   index = 0;
					     }
					  else      
			             p++;
			        } 
			    else 
			        {
					  if ( (ne == 0) & (cont0 == 1)  & (cont == 0) )
					     {							
						    for ( int k=0 ; k<index ; k++ )
								{
								  car = entero1[k];
					              switch (car)
						            {
							         case ' ' : break;
							         case '0' : pp++; break;
							         default  : pp++;
								    }
								}
							if (pp==1)
			                   p++;
			                else
			                   error = 1;
			                   cont0 = 0;
			                   index = 0;
			                   pp = 0;
			             }
			          else
						 cont = 0;
			             cont0 = 0;
			             ne = 0;
			             index = 0;
				    }
			  }
		 index1 = --index;
		 printf("\tMENSAJE: Numero correctamente ingresado.");
	 } 


void Ingresar_entero2 () // procedimiento para ingresar el entero N2
	 {
		int index = 0, error = 0, p = 1, cont = 0, ne = 0, cont0 = 0;
		int pp = 0;
		char car;
		
		while (p<2) // cuando el ingreso sea válido, p=2
		   {
			  if (error == 1) 
			     printf("\tERROR : Ingreso incorrecto.\n\n");
			  error = 0;
			  printf("\n\n\n");
			  printf("\tIngrese el segundo entero, N2, y "); 
			  printf("presione enter:\n\n\n\tN2 = ");
			  while ( ( car = getchar() ) != '\n' )
				    entero2[index++] = car;
			  printf("\n\n");
			  
			  for ( int i=0 ; i<index ; i++ )
                  {
				    car = entero2[i];
					switch (car)
					  {
					   case ' ' :  break;
					   case '-' :  {
					    		     if ( (cont > 0) || (ne > 0) ) 
									    { 
											  error = 1; 
											  i = index;
										    }
										 ne++;
									   }
									   break;
					   case '0' :  {
									 if ( (cont == 0) || ( (cont == 0) & (cont0 > 0) )  )
									    { 
										  error = 1; 
										  i = index;
									    }
									 cont0++;
								   }
								   break;
					   case '1' :  cont++; break;
					   case '2' :  cont++; break;  
					   case '3' :  cont++; break;
					   case '4' :  cont++; break;
					   case '5' :  cont++; break;
					   case '6' :  cont++; break;
					   case '7' :  cont++; break;
					   case '8' :  cont++; break;
					   case '9' :  cont++; break;
					   default  :  { 
						     		 error = 1; 
									 i = index; 
								   }
						 }	 
			      }
		    if ( error == 0 ) 
		        {
				  if ( (ne == 1) & (cont0 == 0) & (cont == 0) )
				     {
				       error = 1;
					   ne = 0;
					   index = 0;
				     }
				  else      
		             p++;
		        } 
		    else 
		        {
				  if ( (ne == 0) & (cont0 == 1)  & (cont == 0) )
				     {							
					    for ( int k=0 ; k<index ; k++ )
							{
							  car = entero2[k];
				              switch (car)
					            {
						         case ' ' : break;
						         case '0' : pp++; break;
						         default  : pp++;
							    }
							}
						if (pp==1)
		                   p++;
		                else
		                   error = 1;
		                   cont0 = 0;
		                   index = 0;
		                   pp = 0;
		             }
		          else
					 cont = 0;
		             cont0 = 0;
		             ne = 0;
		             index = 0;
			    }
		  }
	    index2 = --index;
	    printf("\tMENSAJE: Numero correctamente ingresado.");
	 } 


void Ingresar_opcion ()
	{
	 char cara[1], car, car1, car2;
	 int index=0, op=0;
	
     while (op == 0)
         {
	       printf("\t Ingrese su opcion y presione enter: ");	
		   while ( ( car = getchar() ) != '\n' )
		   cara[index++] = car;
		   if (index == 2)
			{ 
			  car1 = cara[0];
			  car2 = cara[1];
			  switch (car1)
			  {
			   case 'L' : {
							if (car2 == 'I')
			                   op = 1;
			                else
			                   op = 0;
			              }
			              break;
			   case 'I' : {
							switch (car2)
			                   {
								   case '1': op = 2; break;
								   case '2': op = 5; break;
								   default : op = 0;
							   }
						  } 
						  break;
		       case 'M' : {
							switch (car2)
			                   {
								   case '1': op = 3; break;
								   case '2': op = 6; break;
								   case 'R': op = 8; break;
								   default : op = 0;
							   }
						  } 
						  break;
		       case 'B' : {
							switch (car2)
			                   {
								   case '1': op = 4; break;
								   case '2': op = 7; break;
								   default : op = 0;
							   }
						  } 
						  break;
		       case 'S' : {
							if (car2 == 'A')
			                   op = 9;
			                else
			                   op = 0;
			              }
			              break;
		       default  : op = 0;
			  }
		     }
	       index = 0;
	     }
	 opcion = op;
	}


void Iniciar_listas () // iniciando las listas
     {
		cabeza1 = cola1 = NULL;
		cabeza2 = cola2 = NULL; 
		cabezaR = colaR = NULL;
     }

	 
void Leer_entero1 () // Lee N1
	 {
		int ini=0,valor=0,cont=0,i,a;
		char car;
		
		car = entero1[ini++];
		while ( (car==' ') || (car=='-') ) 
			  {
				if (car=='-') 
				   Agregar_nodo1(-1);
				car = entero1[ini++];
			  }
		--ini;
		if (cabeza1 == NULL) 
		   Agregar_nodo1(1); 				
		for ( i=index1 ; i>=ini ; i-- )
			{
				car = entero1[i];
				if (cont==3)
				   {
					Agregar_nodo1 (valor);
					valor = 0;
					cont = 0;
				   }
				if (car!=' ') 
				   {
					a = A_entero(car);
					valor = valor + a*pow(10,cont);
					cont++;
				   }
			}
		Agregar_nodo1 (valor);
	 }

void Leer_entero2 () // Lee N2
	 {
		int ini=0,valor=0,cont=0,i,a;
		char car;
		
		car = entero2[ini++];
		while ( (car==' ') || (car=='-') ) 
			  {
				if (car=='-') 
				   Agregar_nodo2(-1);
				car = entero2[ini++];
			  }
		--ini;
		if (cabeza2 == NULL) 
		   Agregar_nodo2(1); 			
		for ( i=index2 ; i>=ini ; i-- )
			{
				car = entero2[i];
				if (cont==3)
				   {
					Agregar_nodo2 (valor);
					valor = 0;
					cont = 0;
				   }
				if (car!=' ') 
				   {
					a = A_entero(car);
					valor = valor + a*pow(10,cont);
					cont++;
				   }
			}
		Agregar_nodo2 (valor);
	 }
	 
	 
void Leer_instrucciones ()
     {
	  printf("\n\n");
	  printf("\t\t\t INSTRUCCIONES: \n");
	  printf("\n\n");
	  printf("\t El siguiente programa permite manipular numeros \n");
	  printf("\t enteros arbitrariamente grandes.\n");
	  printf("\n");
	  printf("\t Se requiere el ingreso de dos enteros grandes, \n");
	  printf("\t denotemoslos N1 y N2. \n");
	  printf("\t Donde cada uno sera almacenado en una lista \n");
	  printf("\t lineal doblemente ligada.\n");
	  printf("\n");
	  printf("\t El programa muestra como resultados de N1 y N2:\n\n");
	  printf("\t @ El minimo de sus valores absolutos \n");
	  printf("\t @ La diferencia de ellos \n");
	  printf("\t @ La suma de ellos \n");
	  printf("\n\n");
	  printf("\t e.g. si ingresamos: \n");
	  printf("\n");
	  printf("\t N1 = 10 000 540 \n");
	  printf("\t N2 = - 15 100 650 \n");
	  printf("\n");
	  printf("\t El programa nos mostraria: \n");
	  printf("\n");
	  printf("\t min{|N1|,|N2|} = 10 000 540 \n");
	  printf("\n");
	  printf("\t N1 - N2 = 25 101 190 \n");
	  printf("\n");
	  printf("\t N2 + N2 = - 5 100 110 \n");
	  printf("\n\n");
	  printf("\t OBSERVACION: Los enteros deben ser ingresados \n");
	  printf("\t correctamente, para tal fin: \n");
	  printf("\n");
	  printf("\t @ Utilize solo los caracteres: \n");
	  printf("\t   '0','1','2','3','4','5','6','7','8','9','-',' ' \n");
	  printf("\n");
	  printf("\t @ No esta permito ingresos como: \n");
	  printf("\n");
  	  printf("\t $ - \n");
	  printf("\t $ + \n");
	  printf("\t $ 00 \n");
	  printf("\t $ 01 \n");
	  printf("\t $ - 0 \n");
	  printf("\t $ + 0 \n");
	  printf("\t $ + 01 \n");
	  printf("\t $ + 100 \n");
	  printf("\n\n");
	 }
	  
	
void Minimo() // guarda min{|N1|,|N2|} en la lista resultado
	 {
		int g1=cola1->grado , g2=cola2->grado;

		Nodo *temp = NULL;
		
		if (g1 == g2)
		   {
			Nodo *temp1 = cola1;
			Nodo *temp2 = cola2;
			  
			while (temp1->grado >= 0)
				  {
				   if (temp1->info < temp2->info) 
					  {
					   min = 1;
					   temp1->grado = -1;
					  }
				   else if (temp1->info > temp2->info) 
					   temp1->grado = -1;
				   else
					  {
					   temp1 = temp1->ant;
					   temp2 = temp2->ant;
					  }
				  }
		   }
		else if (g1 < g2)	min = 1;
		   
		Agregar_nodoR(1);
		if (min == 1) 
		   {
			temp = cabeza1->sig;
			while (temp != NULL)
				  {
				   Agregar_nodoR(temp->info);
				   temp = temp->sig;
				  }
		   }
		else
		   {
			temp = cabeza2->sig;
			while (temp != NULL)
				  {
				   Agregar_nodoR(temp->info);
				   temp = temp->sig;
				  }
		   }
		
	 }
	 

void Mostrar_entero1 () // Muestra N1
     {
		Nodo *temp = cola1->ant;
		Nodo *imp = NULL;
		if (cabeza1->info == -1) resultado[ind++] = '-';
		resultado[ind++] = ' ';
		Convertir_pb( cola1->info );
		while (temp->ant != NULL) 
	       {
			imp = temp;
			temp = temp->ant;
			Convertir( imp->info );
	       }
	    printf("\n\n\n");
	    printf("\t N1 = ");
	    for (int i=0 ; i<ind ; i++)
			printf("%c",resultado[i]);
		ind = 0;
     }
     
      
void Mostrar_entero2 () // Muestra N2
     {
		Nodo *temp = cola2->ant;
		Nodo *imp = NULL;
		if (cabeza2->info == -1) resultado[ind++] = '-';
		resultado[ind++] = ' ';
		Convertir_pb( cola2->info );
		while (temp->ant != NULL) 
	       {
			imp = temp;
			temp = temp->ant;
			Convertir( imp->info );
	       }
	    printf("\n\n\n");
	    printf("\t N2 = ");
	    for (int i=0 ; i<ind ; i++)
			printf("%c",resultado[i]);
		ind = 0;
     }
     
   
void Mostrar_menu ()
	 {
      printf("\n\n");
	  printf("\t###################################################\n");
	  printf("\t#                                                 #\n"); 
	  printf("\t#                                                 #\n");
	  printf("\t#         ============================            #\n"); 
      printf("\t#                   PROGRAMA :                    #\n");
	  printf("\t#           OPERANDO ENTEROS GRANDES              #\n");
	  printf("\t#         ============================            #\n");
	  printf("\t#                                                 #\n"); 
	  printf("\t#                                                 #\n");
	  printf("\t#                                                 #\n");  
	  printf("\t#                     MENU:                       #\n");
	  printf("\t#                                                 #\n");
	  printf("\t#                                                 #\n");
	  printf("\t#         (LI)  :  Leer Instrucciones             #\n");
	  printf("\t#                                                 #\n");
	  printf("\t#         (I1)  :  Ingresar N1                    #\n");
	  printf("\t#         (M1)  :  Mostrar N1                     #\n");
	  printf("\t#         (B1)  :  Borrar N1                      #\n");
	  printf("\t#                                                 #\n");
	  printf("\t#         (I2)  :  Ingresar N2                    #\n");
	  printf("\t#         (M2)  :  Mostrar N2                     #\n");
	  printf("\t#         (B2)  :  Borrar N2                      #\n");
	  printf("\t#                                                 #\n");
	  printf("\t#         (MR)  :  Mostrar Resultados             #\n");
	  printf("\t#                                                 #\n");
	  printf("\t#         (SA)  :  Salir                          #\n");	  
	  printf("\t#                                                 #\n");
	  printf("\t#                                                 #\n");
	  printf("\t###################################################\n");
	  printf("\n\n\n");
     }
     
       
void Mostrar_resultado () // Muestra el resultado
     {
		Nodo *temp = colaR->ant;
		Nodo *imp = NULL;
		if (cabezaR->info == -1) resultado[ind++] = '-';
		resultado[ind++] = ' ';
		Convertir_pb( colaR->info );
		while (temp->ant != NULL) 
	       {
			imp = temp;
			temp = temp->ant;
			Convertir( imp->info );
	       }
	    for (int i=0 ; i<ind ; i++)
			printf("%c",resultado[i]);
		ind = 0;
		printf("\n\n");
     }
	 

void Restar_enteros () // guarda  N1 - N2  en la lista resultado  
     {
		cabeza2->info = - cabeza2->info;
		Sumar_enteros();
	 }
	 
	 
void Sum() // guarda  |N1| + |N2|  en la lista resultado
	 {
		Nodo *temp1 = cabeza1->sig;
		Nodo *temp2 = cabeza2->sig;
		int N1, N2, N, ad=0;
		
		Agregar_nodoR(1);
		while ( (temp1 != NULL) || (temp2 != NULL) )
			  {
			    if (temp1 != NULL) N1 = temp1->info;
			    else N1=0;
			    
			    if (temp2 != NULL) N2 = temp2->info;
			    else N2=0;
			    
			    N = N1 + N2 + ad;
			    if (N > 999) 
				   {
				    Agregar_nodoR(N-1000);
				    ad=1;
				   }
				else 
				   {
				    Agregar_nodoR(N);
				    ad=0;
				   }
				if (temp1 == NULL) 
				    temp1 = NULL;
				else temp1 = temp1->sig;
				if (temp2 == NULL) 
				    temp2 = NULL;
				else temp2 = temp2->sig;
			  }
		if (ad == 1) 
		   Agregar_nodoR(1);
	 }  
	 

void Sumar_enteros () // guarda  N1 + N2  en la lista resultado
	 {
		int s1 = cabeza1->info; 
		int s2 = cabeza2->info; 
		int s = s1*s2;

		if (s>0) 
		   {
			Sum();
			if (s1>0) 
			   cabezaR->info = 1;
			else cabezaR->info = -1;
		   }
		else
		   {  
			Dif();
			if (min == 1) 
			   cabezaR->info = cabeza2->info;
			else
			   cabezaR->info = cabeza1->info;
		   }
     }


//---------------------------- FIN DE LA DEFINICION ---------------------------------//
