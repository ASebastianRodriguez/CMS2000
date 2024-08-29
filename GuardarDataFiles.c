/*
 ============================================================================
 Name        : 20180629_GuardarDataFiles.c
 Author      : ASRC
 Version     : 1.0
 Copyright   : HB
 Description : Función para recibir datos en forma de array más la longitud
 	 	 	   del mismo para luego ser guardados en archivos con nombres
 	 	 	   consecutivos en formato "aaaammddhhmmss_DataSetCMS2000.dat".
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>

#include "Headers/Manejodatafiles.h"

#define MAXFILES 1000;

//La función GuardarDataFile se utiliza para guardar cada set de datos recibidos
//por el CMS2000 en un archivo con nombre "aaaammddhhmmss_DataSetCMS2000.dat" y
//dentro del directorio "~/MuestrasCMS2000".
//
//La función devuelve:
// 			 0: Archivo creado satisfactoriamente.
// 			 1: Error al crear el archivo.

int GuardarDataFile(char *array, int sizeofarray)
{
	//**************************
	// Declaración de variables.
	//**************************
	int i = 0;
	int retunlink; //Retorna estado de la función borrar archivo.
	int maxfilebuffer = MAXFILES; //Cantidad de archivos en el buffer.

	//Obtengo el directorio HOME del usuario actual.
    struct passwd *pw = getpwuid(getuid()); //Leo la estructura passwd que contiene el dirmuestras HOME del usuario.
	char *homedir = pw->pw_dir; //Guardo el directorio HOME del usuario actual en la variable "homedir".

	//Estructura para verificar si el directorio ya existe.
	struct stat dircomp;

	//PARA PRUEBAS. Anular en versión Release.
	//printf("\n\nDirectorio HOME: %s \n", homedir);
	//i = sizeof(homedir);
	//printf("%i\n", i);

	//Declaración de nombres de archivo y directorio de muestras.
	const char nombase[] 		= "_DataCMS2000.dat"; //Nombre base del archivo.
	const char barra[] 			= "/";
	const char dirmuestras[] 	= "MuestrasCMS2000"; //Directorio en donde van los archivos con los valores de aceleración.

	FILE *fcrear; 	//Archivo a crear (FIFO).

	//Variables de directorio.
	DIR *dir;
    struct dirent **namelist;
    int n;

    //Variables de hora y fecha.
    time_t now;
    struct tm *ts;
    char buf[80];

    //Obtengo la hora actual.
    now = time(0);
    //Formateo e imprimo fecha y hora en fromato "aaaammddhhmmss".
    ts = localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", ts);
//  printf("%s\n", buf);

    //Creo la variable "directorio" para verificar si el mismo existe antes de crearlo.
    char *directorio = malloc(strlen(homedir) + strlen(barra) + strlen(dirmuestras)); //Nombre del directorio en donde irían las muestras.
    strcpy(directorio, homedir);
    strcat(directorio, barra);
    strcat(directorio, dirmuestras);
    strcat(directorio, barra);

    //PARA PRUEBAS. Anular en versión Release.
    //printf("Nombre del directorio de muestras: %s\n", directorio);

    //Armo el path completo más el nombre del archivo que se creará.
	char *nomarch = malloc(strlen(homedir) + strlen(barra) + strlen(dirmuestras) + \
			strlen(barra) + strlen(buf) + strlen(nombase)); //Nombre archivo + path completo.
	strcpy(nomarch, homedir);
	strcat(nomarch, barra);
	strcat(nomarch, dirmuestras);
	strcat(nomarch, barra);
	strcat(nomarch, buf);
	strcat(nomarch, nombase);

	//Mido la longitud del path incluyendo nombre del archivo que se borrará.
	char *nombaseborrar = malloc(strlen(directorio) + strlen(buf) + strlen(nombase));
	//******************************
	// Fin declaración de variables.
	//******************************

    //Chequeo y luego creo el directorio de muestras.
    if(stat(directorio, &dircomp) == -1)
    {
    	mkdir(directorio, 0755);
//    	printf("Directorio creado correctamente: %s\n", directorio);
    }
    else
    {
//    	printf("El directorio ya fue creado\n");
    }

    //**********************************************************************
    //**************Cola circular del tipo FIFO de 1000 archivos************
    //**********************************************************************
    //Verifico si existe el directorio en donde se graban las muestras, sino lo creo.
    if((dir = opendir(directorio)) == NULL)
    {
    	printf("Falló opendir().\n");
    	return EXIT_FAILURE;
    }
    else
    {
		if ((n = scandir(directorio, &namelist, NULL, alphasort)) == -1)
		{
			//Si scandir da -1 hubo un error.
			printf("Falló función \"scandir\".\n");
			return EXIT_FAILURE;
		}
		//Si la cantidad de archivos del directorio de muestras es menor a 1000, guardo los archivos en la cola FIFO.
		else if (n > 0 && n < (maxfilebuffer+2))
		{
		    //Abro el archivo dentro del directorio "~/MuestrasCMS2000" iterando los nombres de los mismos por segundo.
		    if ((fcrear = fopen(nomarch, "wb")) == NULL)
			{
		    	//Falla al crear directorio.
		    	printf("El archivo no pudo ser creado.\n");
				return EXIT_FAILURE;
			}
			else
			{
				//Si el directorio se creó, creo el archivo con el contenido en hexadecimal.
				for(i = 0; i <= sizeofarray - 1; i++)
					fprintf(fcrear, "%02X", array[i] & 0xFF);
				//PARA PRUEBAS. No anular en versión Release.
				//printf("\nCantidad de datos del array a guardar en archivo: %d.\n", sizeofarray);
				//printf("Datos del array guardado:\n");
				//for(i = 0; i <= sizeofarray - 1; i++)
				//	printf("%c", array[i]);
				fclose(fcrear);
				free(namelist);
				closedir(dir);
			}
		}
		//Si llegué a tener más de 1000 archivos en el directorio, empiezo a borrar en orden FIFO.
		else if (n >= (maxfilebuffer+2)) //Debido a los directorios . y .. se suman dos directorios.
		{
			//Creo el path completo incluyendo el nombre del archivo a borrar.
			strcpy(nombaseborrar, directorio);
			strcat(nombaseborrar, namelist[2]->d_name);
//			printf("Path completo archivo a borrar: %s\n", nombaseborrar);
			//Borro el archivo.
			if((retunlink = unlink(nombaseborrar)) < 0)
				{
					//Error al querer borrar el archivo.
					printf("No se ha podido borrar el archivo.\n");
//					printf("%d", retunlink);
					free(namelist);
					closedir(dir);
					exit (EXIT_FAILURE);
				}
			else
				{
					//Archivo borrado en forma correcta.
					//printf("Archivo borrado correctamente.\n");
					//printf("%d\n", retunlink);
				}
		    //Borro un archivo y creo otro archivo dentro del directorio "~/MuestrasCMS2000" iterando los nombres de los mismos por segundo.
		    if ((fcrear = fopen(nomarch, "wb")) == NULL)
			{
		    	//Error al querer crear un archivo.
		    	printf("El archivo no pudo ser creado.\n");
				return EXIT_FAILURE;
			}
			else
			{
				//Creo el archivo correctamente.
				for(i = 0; i <= sizeofarray - 1; i++)
					fprintf(fcrear, "%02X", array[i] & 0xFF);
				fclose(fcrear);
				free(namelist);
				closedir(dir);
			}
		}
		else
		{
			//Error general de la función GuardarDataFiles.
			printf("Error de la función GuardarDataFiles");
			free(namelist);
			closedir(dir);
			exit(EXIT_FAILURE);
		}
    }
    //Finalizó sin error.
    return EXIT_SUCCESS;
}
