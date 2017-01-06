#include "huffman.h"
#include <iostream.h>

int main(int argc, char* argv[])
{	
    // Declarando la clase dinamica de HUFFMAN Compresor
    HUFFMAN *Compresor; 
    // Designando espacio para Compresor
	Compresor = new HUFFMAN(); 
	if(argc > 1) // Ingresando el archivo
		Compresor->Procesar(argv[1]);
	// Liberando el espacio reservado para Compresor 
    delete Compresor;  
    // Imprimiendo mensaje de confirmacion
    cout << "\n\n";
    cout << "\t#############################################################\n";
    cout << "\t#                                                           #\n";
    cout << "\t#    Mensaje: Archivo producido.                            #\n";
	cout << "\t#                                                           #\n";
	cout << "\t#############################################################\n";
	cout << "\n\n";
	cout << "\tPresione enter para continuar";
    getchar(); // Hacemos una pausa
	
    return 0;	
}
