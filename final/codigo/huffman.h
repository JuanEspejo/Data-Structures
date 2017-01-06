#ifndef __HUFFMAN_H
#define __HUFFMAN_H

#include <stdio.h>
#include <string.h>

struct CODIGO
// Esta estructura guarda el código binario que representará al caracter dado.
{
	unsigned char *Cod;
	unsigned int Tam;
};

class CABECERA
// Esta clase es utilizada por la clase "HOJA" para ir guardando el código de 
// cómo fue armado el árbol para luego ser volcada al archivo. 
{
	unsigned char Buf[322];
	unsigned int nIndice;
public:
	CABECERA(){nIndice=0;}
	bool Bit();
	void Bit(bool);
	unsigned char Byte();
	void Byte(unsigned char);
	unsigned int Tamano(){return nIndice;} // devuelve el tamaño en bits del buffer
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
	unsigned int cCod; // Almacenará el código del carácter correspondiente a esa hoja 
	class HOJA *HojaIzquierda;
	class HOJA *HojaDerecha;
	// Ambas apuntarán a la hoja inmediatamente a la izquierda o derecha mientras 
    // dure el proceso de conteo de frecuencias y ordenación según frecuencia.
    class HOJA *pNIzq;
	class HOJA *pNDer;
	// Ambas apuntarán a la hoja u nodo que se encuentre inmediatamente abajo a la 
    // derecha o abajo a la izquierda del nodo dado.
	unsigned int lFrec; // Almacenará cuantas veces se repite ese carácter en el archivo
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
// Se encargará de definir todas las otras e inclusive creará y manejará los 
// archivos con solo pasarle el nombre.
{
	unsigned int lFrec[257]; // array que contiene la frecuencia con la que se repite cada valor
	HOJA *pUltima; // puntero a la última hoja de nuestra alfombra
	CODIGO Caracter[257]; // puntero a las estructuras que contienen el código que ahora representará a cada carácter 	
	void UnoMas(unsigned char Cual){lFrec[Cual]++;} // avisa que apareció una vez más dicho caracter
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
