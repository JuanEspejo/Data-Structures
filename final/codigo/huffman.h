#ifndef __HUFFMAN_H
#define __HUFFMAN_H

#include <stdio.h>
#include <string.h>

struct CODIGO
// Esta estructura guarda el c�digo binario que representar� al caracter dado.
{
	unsigned char *Cod;
	unsigned int Tam;
};

class CABECERA
// Esta clase es utilizada por la clase "HOJA" para ir guardando el c�digo de 
// c�mo fue armado el �rbol para luego ser volcada al archivo. 
{
	unsigned char Buf[322];
	unsigned int nIndice;
public:
	CABECERA(){nIndice=0;}
	bool Bit();
	void Bit(bool);
	unsigned char Byte();
	void Byte(unsigned char);
	unsigned int Tamano(){return nIndice;} // devuelve el tama�o en bits del buffer
	unsigned char *Buffer(){return Buf;}
	void Reset(){nIndice=0;}
	void Adelante(unsigned int nBits){nIndice+=nBits;}
	void Atras(unsigned int nBits){nIndice-=nBits;}
};

class ARCH_IN
{
	FILE *Arch; //Almacena el puntero al archivo abierto
	unsigned char indice; // indica en que bit del buffer vamos escribiendo
	unsigned char byte;   // Es el buffer en si 
public:
	ARCH_IN(unsigned char*,unsigned char*);
	~ARCH_IN();
	bool Fallo(){return !Arch;} // retorna verdadero si el archivo no pudo ser creado
	unsigned int Bit();
	unsigned int Byte();
	FILE *Base(){return Arch;} // devuelve un puntero al archivo abierto para 
    // que el descompresor pueda verificar por su cuenta los primeros caracteres del archivo. 
};

class ARCH_OUT
{
	FILE *Arch; //Almacena el puntero al archivo abierto
	unsigned char indice; // indica en que bit del buffer vamos escribiendo
	unsigned char byte;   // Es el buffer en si 
public:
	ARCH_OUT(unsigned char*,unsigned char*); 
	~ARCH_OUT();
	bool Fallo(){return !Arch;} // retorna verdadero si el archivo no pudo ser creado
	void Bit(unsigned int);
	void Buffer(unsigned char*,unsigned int); 
};

class HOJA_DESC
// Clase "HOJA_DESC", utilizada para descomprimir 
{
	class HOJA_DESC* pHDer;
	class HOJA_DESC* pHIzq;
	bool EsNodo;
	unsigned int Cod;
public:
	HOJA_DESC(class ARCH_IN*);
	~HOJA_DESC();
	unsigned int Descomprimir(class ARCH_IN*,FILE*, unsigned int);
};

class HOJA
// Clase "HOJA", utilizada para comprimir 
{
	unsigned int cCod; // Almacenar� el c�digo del car�cter correspondiente a esa hoja 
	class HOJA *HojaIzquierda;
	class HOJA *HojaDerecha;
	// Ambas apuntar�n a la hoja inmediatamente a la izquierda o derecha mientras 
    // dure el proceso de conteo de frecuencias y ordenaci�n seg�n frecuencia.
    class HOJA *pNIzq;
	class HOJA *pNDer;
	// Ambas apuntar�n a la hoja u nodo que se encuentre inmediatamente abajo a la 
    // derecha o abajo a la izquierda del nodo dado.
	unsigned int lFrec; // Almacenar� cuantas veces se repite ese car�cter en el archivo
	bool EsNodo; // Retorna verdadero si es un Nodo
public:
	HOJA(unsigned int Codigo){pNIzq=NULL;pNDer=NULL;HojaIzquierda=NULL;HojaDerecha=NULL;lFrec=0;cCod=Codigo;EsNodo=false;}
	HOJA(HOJA *Izquierda, HOJA *Derecha);
	~HOJA();
	unsigned int Frecuencia(){return lFrec;}
	void Frecuencia(unsigned int Cuanto){lFrec=Cuanto;}
	class HOJA *HojaDer(){return HojaDerecha;}
	void HojaDer(HOJA *Cual){HojaDerecha=Cual;}
	class HOJA *HojaIzq(){return HojaIzquierda;}
	void HojaIzq(HOJA *Cual){HojaIzquierda=Cual;}
	unsigned char Codigo(){return cCod;}
	bool MoverADer();
	bool MoverAIzq();
	void CrearCodigo(class CABECERA*,struct CODIGO*);
	void CrearCabecera(class ARCH_OUT*);
};

class HUFFMAN
// Se encargar� de definir todas las otras e inclusive crear� y manejar� los 
// archivos con solo pasarle el nombre.
{
	unsigned int lFrec[257]; // array que contiene la frecuencia con la que se repite cada valor
	HOJA *pUltima; // puntero a la �ltima hoja de nuestra alfombra
	CODIGO Caracter[257]; // puntero a las estructuras que contienen el c�digo que ahora representar� a cada car�cter 	
	void UnoMas(unsigned char Cual){lFrec[Cual]++;} // avisa que apareci� una vez m�s dicho caracter
	void CrearHojas();
	void OrdenarHojas();	
	void CrearArbol();
	void CrearCodigos();
public:
	HUFFMAN();
	~HUFFMAN();
	bool Comprimir(char*);
	bool Descomprimir(char*);
	unsigned int Procesar(char*);
};

#endif
