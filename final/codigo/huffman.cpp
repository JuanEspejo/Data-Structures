#include <stdio.h>
#include <string.h>
#include "huffman.h"

void CABECERA::Byte(unsigned char Cual)
// sirven para leer o escribir un byte en el buffer
{
	short *Temp = (short*)&Buf[nIndice/8],Mascara=0x00FF;
	Mascara = Mascara << (nIndice%8);
	*Temp = *Temp & (~Mascara);
	Mascara = (short) Cual;
	Mascara = Mascara << nIndice %8;
	*Temp = *Temp | Mascara;
	nIndice += 8;
}

unsigned char CABECERA::Byte()
{
	unsigned short Temp = Buf[nIndice/8],Mascara=0x00FF;
	Mascara = Mascara << (nIndice%8);
	Mascara = Mascara & Temp;
	Mascara = Mascara >> (nIndice%8);
	nIndice += 8;
	return (unsigned char)Mascara;
}

bool CABECERA::Bit()
{
	unsigned char Mascara=0x01;
	Mascara = Mascara<<(nIndice%8);
	Mascara = Mascara & Buf[nIndice/8];
	nIndice++;
	return Mascara?1:0;
}

void CABECERA::Bit(bool Cual)
// sirven para leer o escribir un bit en el buffer
{
	unsigned char Mascara=0x01;
	Mascara = Mascara<<(nIndice%8);
	if(Cual)
		Buf[nIndice/8] = Mascara|Buf[nIndice/8];
	else
		Buf[nIndice/8] = (~Mascara)&Buf[nIndice/8];
	nIndice++;
}


ARCH_IN::ARCH_IN(unsigned char* Nombre, unsigned char *Atrib)
// Abre el archivo y pone a cero el índice.
{
	Arch=fopen((char*)Nombre,(char*)Atrib);
	indice=0;
	byte=0;
}

ARCH_IN::~ARCH_IN()
// Cierra el archivo
{
	if(Arch)
		fclose(Arch);
}

unsigned int ARCH_IN::Bit()
// Se fija si hay bits en el buffer. Si los hay, lee el que 
// corresponde e incrementa el índice.
{
	unsigned int res;
	if((!indice)&&(!feof(Arch)))
	{
		byte = fgetc(Arch);
		indice = 8;
	}
	res = 0x01&byte;
	byte = byte>>1;
	indice--;
	return res;
}

unsigned int ARCH_IN::Byte()
// Leer un byte desde el archivo. 
{
	unsigned int res;
	unsigned char m = 0xFF;
	if((!indice)&&(!feof(Arch)))
		return fgetc(Arch);
	else
	{
		res = fgetc(Arch);
		res = res<<indice;
		res = res|(unsigned int)(byte&(m>>(8-indice)));
		byte = res>>8;
		res = res&0x00FF;
		return res;
	}
}


ARCH_OUT::ARCH_OUT(unsigned char *Nombre, unsigned char *Atributos)
// constructor se encarga de crear el archivo con el 
// nombre y atributos especificados                         
{ 
   	Arch = fopen((char*)Nombre,(char*)Atributos);
	indice = 0;
	byte = 0;
}

ARCH_OUT::~ARCH_OUT()
// Escribe lo último que nos quedó en el buffer (si es que quedó) y 
// cierra el archivo.
{
	if(indice)
		fputc(byte,Arch);
	fclose(Arch);
}

void ARCH_OUT::Bit(unsigned int Valor)
// recibe un bit y lo almacena en el buffer para guardarlo al archivo
{
	byte = byte|(Valor<<indice++);
	if(indice==8)
	{
		fputc(byte,Arch);
		byte = NULL;
		indice = 0;
	}
}

void ARCH_OUT::Buffer(unsigned char *Buf, unsigned int Bits)
// de escribe un buffer de bits al archivo
{
	unsigned char B[35],mask = 0xFF;
	unsigned short *Punt,Temp1,Temp2;
	unsigned int nBytes,BitsExt;
	nBytes = (Bits+indice)/8;
	BitsExt = (Bits+indice)%8;
	memcpy(B,Buf,(Bits/8)+((Bits%8)?1:0));
	Punt = (unsigned short*)&B[0];
	Temp1 = *Punt;
	Temp1 = Temp1<<indice;
	Temp1 = Temp1|(unsigned short)(byte&(mask>>(8-indice)));
	for(unsigned int i=0;i<nBytes;i++)
	{
		fputc((unsigned char)Temp1,Arch);
		Temp1 = Temp1>>8;
		if(i<nBytes-1)
		{
			Punt = (unsigned short*)&B[i+1];
            Temp2 = *Punt;
			Temp2 = Temp2<<indice;
			Temp2 = Temp2&0xFF00;
			Temp1 = Temp2|Temp1;
		}
	}
	byte = (unsigned char)Temp1;
	byte = (0xFF>>(8-BitsExt))&byte;
	indice = BitsExt;
}


HOJA_DESC::HOJA_DESC(class ARCH_IN* Arch)
{
	EsNodo = !Arch->Bit();
	if(!EsNodo)
	{
		pHIzq = NULL;
		pHDer = NULL;
		Cod = Arch->Byte();
	}
	else
	{
		pHIzq = new HOJA_DESC(Arch);
		pHDer = new HOJA_DESC(Arch);
	}
}

HOJA_DESC::~HOJA_DESC()
{
	if(EsNodo)
	{
		delete pHIzq;
		delete pHDer;
	}
}

unsigned int HOJA_DESC::Descomprimir(class ARCH_IN* ArchIn,
             FILE* ArchOut, unsigned int BytesRest)
{
	if(!BytesRest)
		return BytesRest;
	if(EsNodo)
	{
		if(!ArchIn->Bit())
			BytesRest = pHIzq->Descomprimir
            (ArchIn,ArchOut,BytesRest);
		else
			BytesRest = pHDer->Descomprimir
            (ArchIn,ArchOut,BytesRest);
		return BytesRest;
	}
	else
	{
		fputc(Cod,ArchOut);
		return --BytesRest;
	}
}

HOJA::HOJA(HOJA *Izquierda, HOJA *Derecha)
{
	EsNodo = true;
	cCod = NULL;
	Frecuencia(Izquierda->Frecuencia() +
               Derecha->Frecuencia());
	pNDer = Derecha;
	pNIzq = Izquierda;
	HojaIzq(Izquierda->HojaIzq());
	HojaDer(Derecha->HojaDer());
	Derecha->HojaDer(NULL);
	Derecha->HojaIzq(NULL);
	Izquierda->HojaIzq(NULL);
	Izquierda->HojaDer(NULL);
	if(HojaIzq())
		HojaIzq()->HojaDer(this);
	if(HojaDer())
		HojaDer()->HojaIzq(this);
}

HOJA::~HOJA()
// destruye primero las hojas u nodos que tenga abajo, 
// si es que los tiene
{
	if(pNDer)
		delete pNDer;
	if(pNIzq)
		delete pNIzq;
}

void HOJA::CrearCabecera(class ARCH_OUT* ArchOut)
// Éste se encargará de ir llamando a cada nodo y hoja 
// para que vayan escribiendo en el archivo su parte del 
// código de la composición del árbol, que debe ser leído 
// después por el descompresor para saber como era el árbol
{
	if(EsNodo)
	{
		ArchOut->Bit(0);
		pNIzq->CrearCabecera(ArchOut);
		pNDer->CrearCabecera(ArchOut);
	}
	else
	{
		ArchOut->Bit(1);
		ArchOut->Buffer((unsigned char*)&cCod,8);
	}
}

void HOJA::CrearCodigo(class CABECERA* Cab,struct CODIGO* Cod)
// se encarga de crear los nuevos códigos para cada carácter de 
// acuerdo a su ubicación en el árbol.
{
	if(EsNodo)
	{
		Cab->Bit(0);
		pNIzq->CrearCodigo(Cab,Cod);
		Cab->Bit(1);
		pNDer->CrearCodigo(Cab,Cod);
		Cab->Atras(1);
	}
	else
	{
		Cod[cCod].Cod = new unsigned char[(Cab->Tamano()/8)+
                        ((Cab->Tamano()%8)?1:0)];
		memcpy(Cod[cCod].Cod,Cab->Buffer(),(Cab->Tamano()/8)+
                        ((Cab->Tamano()%8)?1:0));
		Cod[cCod].Tam = Cab->Tamano();
		Cab->Atras(1);
	}
}

bool HOJA::MoverADer()
{
	if(!HojaDer())
		return false;
	else
	{
		if(HojaIzq())
			HojaIzquierda->HojaDer(HojaDer());
		HojaDerecha->HojaIzq(HojaIzq());
		HojaIzq(HojaDer());
		HojaDer(HojaDerecha->HojaDer());
		if(HojaDer())
			HojaDerecha->HojaIzq(this);
		HojaIzquierda->HojaDer(this);	
		return true;
	}
}

bool HOJA::MoverAIzq()
{
	if(!HojaIzq())
		return false;
	else
	{
		if(HojaDer())
			HojaDerecha->HojaIzq(HojaIzq());
		HojaIzquierda->HojaDer(HojaDer());
		HojaIzq(HojaIzquierda->HojaIzq());
		HojaDer(HojaIzq());
		if(HojaIzq())
			HojaIzquierda->HojaDer(this);
		HojaDerecha->HojaIzq(this);	
		return true;
	}
}


HUFFMAN::HUFFMAN()
{
	for(unsigned int i=0;i<256;i++)
	{
		lFrec[i] = 0;
		Caracter[i].Cod = NULL;
		Caracter[i].Tam = 0;
	}
	pUltima = NULL;
}

HUFFMAN::~HUFFMAN()
{
	delete pUltima;
}

bool HUFFMAN::Descomprimir(char *NArchIn)
// recibe como argumento el nombre del archivo a descomprimir
{
	class ARCH_IN *ArchIn = 
    new ARCH_IN((unsigned char*)NArchIn,(unsigned char*)"rb");
	FILE* ArchOut;
	class HOJA_DESC* HBase;
	unsigned char Sign[4], *NArchOut;
	unsigned int Tamanio;
	if(strcmp((char*)&NArchIn[strlen((char*)NArchIn)-4],".hfm"))
		return false;
	if(ArchIn->Fallo())
		return false;
	fread(Sign,3,1,ArchIn->Base());
	if(strncmp((char*)Sign,"hfm",3))
		return false;
	fread(&Tamanio,4,1,ArchIn->Base());
	if(!Tamanio)
		return false;
	NArchOut = new unsigned char[strlen((char*)NArchIn)+1];	
	strcpy((char*)NArchOut,(char*)NArchIn);	
	NArchOut[strlen((char*)NArchOut)-4]=NULL;
    sprintf((char*)NArchOut,"%s.dec",NArchOut);	
    ArchOut = fopen((char*)NArchOut,"wb");
	delete []NArchOut;
	if(!ArchOut)
		return false;
	HBase = new HOJA_DESC(ArchIn);
	while(Tamanio)
		Tamanio = HBase->Descomprimir(ArchIn,ArchOut,Tamanio);
	return true;
}

bool HUFFMAN::Comprimir(char* NombreArchivo)
// recibe como argumento el nombre del archivo a comprimir
{
	FILE *ArchIn;
	unsigned char *NombreArchOut;
	ARCH_OUT *ArchOut;
	unsigned int Tamanio=0,Car=0;
	NombreArchOut=new unsigned char[strlen((char*)NombreArchivo)];
		sprintf((char*)NombreArchOut,NombreArchivo);
	NombreArchOut[strlen((char*)NombreArchOut)-4]=NULL;
	sprintf((char*)NombreArchOut,"%s.hfm",NombreArchOut);	
    ArchIn = fopen((char*)NombreArchivo,"rb");
	ArchOut = new ARCH_OUT(NombreArchOut,(unsigned char*)"wb");
	if(!ArchIn || ArchOut->Fallo())
		return false;
	while(!feof(ArchIn))
	{
		fread(&Car,1,1,ArchIn);
		lFrec[Car]++;
		Tamanio++;
	}
	Tamanio--;
	fseek(ArchIn,0,SEEK_SET);
	CrearArbol();
	CrearCodigos();
	ArchOut->Buffer((unsigned char*)"hfm",24);
	ArchOut->Buffer((unsigned char*)&Tamanio,sizeof(Tamanio)*8);
	pUltima->CrearCabecera(ArchOut);
	for(unsigned int i=0;i<Tamanio;i++)
	{
		fread(&Car,1,1,ArchIn);
		ArchOut->Buffer(Caracter[Car].Cod,Caracter[Car].Tam);
	}
	delete ArchOut;
	for(int i=0;i<256;i++)
		if(!Caracter[i].Cod)
			delete Caracter[i].Cod;
	return true;
}

void HUFFMAN::CrearCodigos()
{
	CABECERA *Buf = new CABECERA();
	pUltima->CrearCodigo(Buf,Caracter);
	delete Buf;
}

void HUFFMAN::CrearArbol()
{
	HOJA *Temp;
	CrearHojas();
	OrdenarHojas();
	while(pUltima->HojaIzq())
	{
		Temp = new HOJA(pUltima->HojaIzq(),pUltima);
		pUltima = Temp;
		OrdenarHojas();
	}
}

void HUFFMAN::CrearHojas()
{
	HOJA *Temp;
	for(unsigned int i=0;i<256;i++)
	{
		if(lFrec[i]!=0)
		{
			if(pUltima==NULL)
				Temp = pUltima = new HOJA(i);
			else
			{
				Temp = new HOJA(i);
				Temp->HojaIzq(pUltima);
				pUltima->HojaDer(Temp);
				pUltima = Temp;
			}
			Temp->Frecuencia(lFrec[i]);
		}
	}
}

void HUFFMAN::OrdenarHojas()
{
	HOJA *Temp = pUltima;
	while(Temp->HojaIzq())
	{
		Temp = Temp->HojaIzq();
		while(Temp->HojaDer())
		{
			if(Temp->Frecuencia()<Temp->HojaDer()->Frecuencia())
			{
				Temp->MoverADer();
				if(!Temp->HojaDer())
					pUltima = Temp;
			}
			else
				break;
		}
	}
}

unsigned int HUFFMAN::Procesar(char* Archivo)
{
	// Retorna 0:fallo 1:comprimió 2:descomprimió
	if(!strcmp(&Archivo[strlen(Archivo)-4],".hfm"))
		return Descomprimir(Archivo);
	else
		return Comprimir(Archivo);
}
