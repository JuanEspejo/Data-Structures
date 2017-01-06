#include<stdio.h>
#include<string.h>
#include<math.h>


char posfija[100];  
// Declarando la variable global "posfija", que almacenara la notacion posfija.  

class charst   
// Definimos la pila "charst", que almacenara caracteres.
 {
             char chars[100];
             int top;
             
             public:
             
             bool pila_llena()
			  {
				if (top == 99)
					return true;
				else
					return false;
			  }
        
			 bool pila_vacia()
			  {
				if (top == -1)
					return true;
			    else
					return false;
			  }
			 
             void crear_pila()
              {
                top = -1;
              }
             
             void apilar(char x)
              {
				if(pila_llena())
				 {
                    return;
                 }
                else
                 {
					chars[++top] = x;
				 }
			  }
              
             void desempilar()
              {
				if(pila_vacia())
				 {
					--top;  
// Esto se hace con el fin de evaluar el anidamiento de los parentesis.
					return;
				 }
                else
					--top;
              }
              
             char accesar_tope()
              {
				if(pila_vacia())
				 {
					return '(';
// Esto se hace para evitar el inconveniente de que la pila de 
// caracteres en la funci\'{o}n "apos", definida m\'{a}s abajo, quede
// vacia al exigir el valor de precedencia o prioridad del tope de 
// dicha pila.   
				 }
                else
					return chars[top];
              }
              
             int tamanio()
              {
				if(pila_vacia())
				 {
					return 0;
				 }
				else
					return top+1;
			  }
 };

class floatst  
// Definimos la pila "floatst", que almacenara reales.
 {
             float floa[100];
             int top;
             
             public:
             
             bool pila_llena()
			  {
				if (top == 99)
					return true;
				else
					return false;
			  }
        
			 bool pila_vacia()
			  {
				if (top == -1)
					return true;
			    else
					return false;
			  }
			 
             void crear_pila()
              {
                top = -1;
              }
             
             void apilar(float x)
              {
				if(pila_llena())
				 {
                    return;
                 }
                else
                 {
					floa[++top] = x;
				 }
			  }
              
             void desempilar()
              {
				if(pila_vacia())
				 {
					return;
				 }
                else
					--top;
              }
              
             float accesar_tope()
              {
				if(pila_vacia())
				 {
					return 0; 
// Esto porque tenemos que retornar un entero,
// este valor de retorno es irrelevante.
				 }
                else
					return floa[top];
              }
              
             int tamanio()
              {
				if(pila_vacia())
				 {
					return 0;
				 }
				else
					return top+1;
			  }
 };

class operador 
// Definos la clase "operador".
 {
	public:
	char simbolo;  
// Simbolo del operador, e.g., 
// el s\'{i}mbolo del operador adici\'{o}n es +.
	int  nivel;    
// Nivel de precedencia o prioridad del operador, e.g.,
// la prioridad del operador adici\'{o}n es 2.
 };

operador ope[100];   
// Declaramos la variable global "ope", que almacenara a los operadores 
// con sus recpectivos niveles de precedencia.
 
class operando  
// Definos la clase "operando".
 {
	public:
	char simbolo;  
// Simbolo del operando, e.g., A.
	float  valor;  
// Valor del operando, e.g., el valor del operando A es  5.
 };

operando vara[100];  
// Declaramos la variable global "vara", que almacenara a los operandos 
// con sus recpectivos valores.

void cabecera()  
// Definiendo la funcion "cabecera", que muestra al usuario las 
// indicaciones iniciales del programa.
 {
	printf("\t##############################################################\n");
	printf("\t#                                                            #\n");
	printf("\t#                  ALGORITMO: NOTACION POLACA                #\n");
	printf("\t#                                                            #\n");
	printf("\t##############################################################\n"); 
	printf("\n\n");
	printf("\t##############################################################\n");
	printf("\t#                                                            #\n");  
	printf("\t#   Use solo, los siguientes simbolos como variables:        #\n");
	printf("\t#                                                            #\n");
	printf("\t#                A     B     C     D     E                   #\n");
	printf("\t#                F     G     H     I     J                   #\n");
	printf("\t#                K     L     M     N     P                   #\n");
	printf("\t#                Q     R     S     T     U                   #\n");
	printf("\t#                V     W     X     Y     Z                   #\n");
	printf("\t#                                                            #\n");
	printf("\t#                                                            #\n");
	printf("\t#   los agrupadores:                                         #\n");
	printf("\t#                                                            #\n");
	printf("\t#                 (  :  abre parentesis                      #\n");
	printf("\t#                 )  :  cierra parentesis                    #\n");
	printf("\t#                                                            #\n");
	printf("\t#                                                            #\n");
	printf("\t#   los operadores:                                          #\n");
	printf("\t#                                                            #\n");
	printf("\t#                 +  :  adicion                              #\n");
	printf("\t#                 -  :  sustraccion                          #\n");
	printf("\t#                 *  :  multiplicacion                       #\n");
	printf("\t#                 /  :  division                             #\n");
	printf("\t#                 @  :  potenciacion                         #\n");
	printf("\t#                                                            #\n");
	printf("\t#   y finalmente el espaciador ' '                           #\n");
	printf("\t#                                                            #\n");
	printf("\t##############################################################\n");
	printf("\n\n");
 };
 
int validar(char infija[], int index)  
// Definiendo la funcion "validar", que valida la expresi\'{o}n infija,
// tanto de simbolos extra\~{n}os como del anidamiento de los parentesis.
//
// Entrada: 
//  infija   :  cadena que contiene la notacion infija.
//  index    :  n\'{u}mero de caracteres de la cadena "infija".
//
// Salida:
//     0     :  indica que la notaci\'{o}n es v\'{a}lida.
//     1     :  indica que la notaci\'{o}n no est\'{a} bien anidada.
//     2     :  indica la presencia de s\'{i}mbolos extra\~{n}os.
//     1     :  indica "1" y "2".
 {
	int a=0,i;
	charst anida;
	char symbol;
	
	anida.crear_pila();  // Creando la pila "anida", que almacenara los abre parentesis.
	for ( i=0 ; i<index ; i++ )
	 {
		symbol = infija[i];
		switch(symbol)
		 {
			case 'A' : case 'B' : case 'C' : case 'D' : case 'E' : 
			case 'F' : case 'G' : case 'H' : case 'I' : case 'J' : 
			case 'K' : case 'L' : case 'M' : case 'N' : case 'P' : 
			case 'Q' : case 'R' : case 'S' : case 'T' : case 'U' : 
			case 'V' : case 'W' : case 'X' : case 'Y' : case 'Z' : 
			case ' ' : case '+' : case '-' : case '*' : case '/' : 
			case '@' : 
						break;
			case '(' :  anida.apilar(symbol); break;
			case ')' :  anida.desempilar(); break;
			default  :  a = 2;   
			// Cuando encuentra s\'{i}mbolos extra\~{n}os. 
		 } 
	 }
	if ( anida.tamanio()!=0 ) ++a;  
	// Cuando los par\'{e}ntesis no est\'{a}n bien anidados. 
	return a;
 };
 
void asignacion(char infija[], int index)  
// Definiendo la funcion "asignacion", que recibe un operador y le 
// asigna un nivel de precedencia o prioridad de acuerdo a 
// la siguiente tabla:
//
// ------------------------------------------------------------
// |  simbolo             |  (  |  +  |  -  |  *  |  /  |  @  |
// ------------------------------------------------------------
// | nivel de preferencia |  1  |  2  |  2  |  3  |  3  |  4  |
// ------------------------------------------------------------
//
// Entrada: 
//  infija    :  cadena que contiene la notacion infija.
//  index     :  n\'{u}mero de caracteres de la cadena "infija".
 {
	int i;
	char symbol;
	
	for ( i=0 ; i<index ; i++)
	 {
		symbol = infija[i];
		switch(symbol)
		 {
			case '(' : { 
						ope[0].simbolo = symbol; 
						ope[0].nivel = 1;
					   } break;
			case '+' : {
						ope[1].simbolo = symbol;
						ope[1].nivel = 2;
					   } break;
			case '-' : {
						ope[2].simbolo = symbol;
						ope[2].nivel = 2;
					   } break;
			case '*' : {
						ope[3].simbolo = symbol;
						ope[3].nivel = 3;
					   } break;
			case '/' : {
						ope[4].simbolo = symbol;
						ope[4].nivel = 3;
					   } break;
			case '@' : {
						ope[5].simbolo = symbol;
						ope[5].nivel = 4;
					   } break;
		 }
	 }
 };

void variables(char valores[], int index)
// Definiendo la funci\'{o}n "variables", que almacena el valor de los 
// operandos.
//
// Entrada:
//  valores   :  cadena de caracteres con el siguiente formato, e.g.,
//               A 5    B 2    E 3    D -1    F 4    C 0
//  index     :  n\'{u}mero de caracteres de la cadena "valores".
 {
	int i,j=0,k;
	float v;
	char symbol;
	
	for ( i=0 ; i<index ; i=i+k )
	 {
		symbol = valores[i];
		if ( symbol == ' ' ) k = 1;
		else
		 {
			vara[j].simbolo = symbol;
			symbol = valores[++i];
			while ( symbol == ' ' )
				symbol = valores[++i];
			if ( symbol == '-' )
			 {
					symbol = valores[i+1];
					switch(symbol)
					 {
						case '1' :  v = -1; break;
						case '2' :  v = -2; break;
						case '3' :  v = -3; break;
						case '4' :  v = -4; break;
						case '5' :  v = -5; break;
						case '6' :  v = -6; break;
						case '7' :  v = -7; break;
						case '8' :  v = -8; break;
						case '9' :  v = -9; break;
					 }
					vara[j++].valor = v;
					k=2;
			 }
			else
			 {
					switch(symbol)
					 {
						case '0' :  v = 0; break; 
						case '1' :  v = 1; break;
						case '2' :  v = 2; break;
						case '3' :  v = 3; break;
						case '4' :  v = 4; break;
						case '5' :  v = 5; break;
						case '6' :  v = 6; break;
						case '7' :  v = 7; break;
						case '8' :  v = 8; break;
						case '9' :  v = 9; break;
					 }
					vara[j++].valor = v;
					k=1;				 
			 }
		 }
	 }
 };

int priori(char oper)
// Definiendo la funci\'{o}n "priori", que retorna el nivel de 
// precedencia o prioridad de un operador (oper), e.g., priori(+) = 2. 
 {
	int i=0;
	
	while ( ope[i].simbolo != oper )
	++i;
	return ope[i].nivel;  
 };

float value(char variable)
// Definiendo la funci\'{o}n "value", que retorna el valor de un   
// operando (variable), e.g., value(A) = 2.
 {
	int i=0;
	
	while ( vara[i].simbolo != variable )
	++i;
	return vara[i].valor;  
 };
 
int apos(char infija[], int index)
// Definiendo la funci\'{o}n "apos", que almacena la notaci\'{o}n
// posfija de la cadena "infija" en la cadena "posfija".
//
// Entrada: 
//  infija    :  cadena que contiene la notacion infija.
//  index     :  n\'{u}mero de caracteres de la cadena "infija".
//
// Salida:
//  n\'{u}mero de caracteres de la  cadena "posfija".
 {
	int i,j=0;
	char sym;
	charst st;
	
	st.crear_pila();
	for ( i=0 ; i<index ; i++ )
	 {
		sym = infija[i];
		switch(sym)
		 {
			case 'A' : case 'B' : case 'C' : case 'D' : case 'E' : 
			case 'F' : case 'G' : case 'H' : case 'I' : case 'J' : 
			case 'K' : case 'L' : case 'M' : case 'N' : case 'P' : 
			case 'Q' : case 'R' : case 'S' : case 'T' : case 'U' : 
			case 'V' : case 'W' : case 'X' : case 'Y' : case 'Z' : 
					   posfija[j++] = sym ; 
					   break;
			case ' ' : break;
			case '(' : st.apilar(sym) ; 
					   break;
			case ')' : while ( st.accesar_tope() != '(' )
						{
							posfija[j++] = st.accesar_tope() ;
							st.desempilar() ;
						}				
					   st.desempilar(); break;
			case '@' : st.apilar(sym) ; 
					   break;
			default  : while ( priori(st.accesar_tope()) >= priori(sym) )
						{
							posfija[j++] = st.accesar_tope() ;
							st.desempilar() ;
						}
					   st.apilar(sym); 
		 }
	 }
	while ( !( st.pila_vacia() ) )
	 {
		posfija[j++] = st.accesar_tope() ;
		st.desempilar() ;
	 } 
	return j;
 };

double calculus(char posfija[], int index)
// Definiendo la funci\'{o}n "calculus", que calcula el valor de la 
// expresi\'{o}n posfija de la cadena "posfija".
//
// Entrada: 
//  posfija   :  cadena que contiene la notacion posfija.
//  index     :  n\'{u}mero de caracteres de la cadena "posfija".
//
// Salida:
//  valor de la expresi\'{o}n posfija de la cadena "posfija".
 {
	int i;
	float P,Q,R;
	char sym;
	floatst st;
	
	st.crear_pila();
	for ( i=0 ; i<index ; i++ )
	 {
		sym = posfija[i];
		switch(sym)
		 {
			case 'A' : case 'B' : case 'C' : case 'D' : case 'E' : 
			case 'F' : case 'G' : case 'H' : case 'I' : case 'J' : 
			case 'K' : case 'L' : case 'M' : case 'N' : case 'P' : 
			case 'Q' : case 'R' : case 'S' : case 'T' : case 'U' : 
			case 'V' : case 'W' : case 'X' : case 'Y' : case 'Z' : 
					   st.apilar( value(sym) ); 
					   break;
			case '-' : Q = st.accesar_tope();
					   st.desempilar();
					   P = st.accesar_tope();
					   st.desempilar();
					   R = P - Q;
					   st.apilar(R); break;
			case '+' : Q = st.accesar_tope();
					   st.desempilar();
					   P = st.accesar_tope();
					   st.desempilar();
					   R = P + Q;
					   st.apilar(R); break;
			case '/' : Q = st.accesar_tope();
					   st.desempilar();
					   P = st.accesar_tope();
					   st.desempilar();
					   R = P / Q;
					   st.apilar(R); break;
			case '*' : Q = st.accesar_tope();
					   st.desempilar();
					   P = st.accesar_tope();
					   st.desempilar();
					   R = P * Q;
					   st.apilar(R); break;
			case '@' : Q = st.accesar_tope();
					   st.desempilar();
					   P = st.accesar_tope();
					   st.desempilar();			
					   R = pow(P,Q);
					   st.apilar(R); break;
		 }
		
	 }
	return st.accesar_tope();
 };

int main()
 {
	// Definiendo las variables que utilizaremos. 
	char symbol,infija[100],valores[100];
	int index,inde,a=1,M,i;
	float R;


    // Iniciando el programa.
    
    printf("\n\n");
	cabecera();  // Indicando las instrucciones iniciales.
	while ( a>0 )  // Validando la notaci\'{o}n. 
	 { 
		index = 0; 
		printf("\tIngrese la notacion infija:\n\n\t\t"); 
		while( (symbol=getchar()) != '\n' )
			infija[index++] = symbol;
			
		a = validar(infija,index);
		switch(a)
		 {
			case 1 : printf("\n\tVerifique el uso de los parentesis\n\n");
					 break;
			case 2 : printf("\n\tIngrese solo los simbolos permitidos\n\n"); 
					 break;
			case 3 : printf("\n\tVerifique el uso de los parentesis e ");
			         printf("ingrese solo los simbolos permitidos\n\n"); 
			         break;
		 }
	 }
	printf("\n\tExpresion valida\n\n");   
	
	// Asignando las prioridades a los respectivos operadores ingresados.
	asignacion ( infija , index ); 
	
	inde = 0;  // Inicializando.
	printf("\tMediante una cadena de caracteres del siguiente formato \n\n");
	printf("\t      A 5    B 2    E 3    D -1    F 4    C 0           \n\n");            
	printf("\tIngrese la cadena de variables con sus respectivos ");  
	printf("valores y presione enter: \n\n\t\t");
 	
 	// Ingresando la cadena de caracteres solicitada.
 	while( (symbol=getchar()) != '\n' )  
 		valores[inde++] = symbol;
 		
	// Asignando los valores a los respectivos operandos.
	variables( valores,inde ); 
	
	M = apos( infija,index );  // Hallando la notaci\'{o} posfija. 
	R = calculus( posfija,M ); // Hallando el valor de la expresi\'{o}n.
	
	// Imprimiendo resultados.
	printf("\n\tLa notacion posfija es: ");
	for ( i=0 ; i<M ; i++)
	printf("%c",posfija[i]);
	printf("\n\n\tSu valor es: %f\n\n",R);
	
	return 0;
 }
