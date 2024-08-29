/*
 ============================================================================
 Name        : 20180630_LeerDataFiles.c
 Author      : ASRC
 Version     : 1.0
 Copyright   : HB
 Description : Función para leer archivos de datos con nombre en formato
 	 	 	   "aaaammddhhmmss_DataSetCMS2000.dat".
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "Headers/Manejodatafiles.h"

//La función LeerDataFile se utiliza para leer archivos de datos con nombre en
//formato "aaaammddhhmmss_DataSetCMS2000.dat".
//
//La función devuelve:
// 			0: Archivo leído satisfactoriamente.
// 			1: Error al leer el archivo.

int LeerDataFile(char *nombre)
{
	int i = 0;
	int longfile = 1088; //La longitud del archivo es BUFFERDATOS*2.
	char p[longfile];
	FILE *fp;

	if ((fp = fopen("data.dat", "rb")) == NULL)
	{
		printf("El archivo no pudo ser leído.\n");
		return EXIT_FAILURE;
	}
	else
	{
		while(!feof(fp))
		{
			fread(&p, longfile, 1, fp);
			printf("\n\nDatos del array del archivo leído:\n");
			for(i = 0; i <= longfile - 1; i++)
				printf("%c", p[i]);
		}
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

