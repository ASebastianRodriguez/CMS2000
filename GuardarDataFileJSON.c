/*
 ============================================================================
 Name        : 20180904_GuardarDataFileJSON.c
 Author      : ASRC
 Version     : 1.0
 Copyright   : HB
 Description : Función para recibir un archivo en formato hexadecimal junto a
 	 	 	   la cantidad de datos incluidos dentro del mismo, para luego ser
 	 	 	   guardados en formato JSON bajo el nombre
 	 	 	   "aaaammddhhmmss_DataSetCMS2000.json".
 	 	 	   La conversión de datos en hexadecimal a los respectivos formatos
 	 	 	   numéricos dentro del archivo JSON se realiza dentro de esta
 	 	 	   función.
 ============================================================================
 */
/*******************************************************************************
PENDIENTES GuardarDataFileJSON:
	- MAXFILESJSON debería ser un parámetro dentro del archivo de configuración
	  .ini.
*******************************************************************************/

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

//Cantidad de archivos en formato JSON que se escribirán en el directorio.
#define MAXFILESJSON 1000;

//Función para recibir un archivo en formato hexadecimal junto a la cantidad de
//datos incluidos dentro del mismo, para luego ser guardados en formato JSON
//bajo el nombre "aaaammddhhmmss_DataSetCMS2000.json".
//La conversión de datos en hexadecimal a los respectivos formatos de cada dato
//se realiza dentro de la función "Hex2Json()".
//
//La función devuelve:
// 			 0: Archivo creado satisfactoriamente.
// 			 1: Error al crear el archivo.

int GuardarDataFileJSON(char *arrayhex, int sizeofarrayhex)
{
	//**************************
	// Declaración de variables.
	//**************************
	int retunlink = 0; //Retorna estado de la función borrar archivo.
	int maxfilebuffer = MAXFILESJSON; //Cantidad de archivos en el buffer.

	//char arrayjson[10000] 		= {0};
			//malloc(10000); //Array recibido del la función Hex2Json que convierte de hexadecimal a JSON los datos.

	//Obtengo el directorio HOME del usuario actual.
    struct passwd *pw = getpwuid(getuid()); //Leo la estructura passwd que contiene el dirmuestras HOME del usuario.
	char *homedir = pw->pw_dir; //Guardo el directorio HOME del usuario actual en la variable "homedir".

	//Estructura para verificar si el directorio ya existe.
	struct stat dircomp;

	//Declaración de nombres de archivo y directorio de muestras.
	const char nombase[] 		= "_DataCMS2000.json"; //Nombre base del archivo.
	const char barra[] 			= "/";
	const char dirmuestras[] 	= "MuestrasCMS2000_JSON"; //Directorio en donde van los archivos con los valores de aceleración.

	FILE *fcrear; 	//Archivo a crear (FIFO).

	//Variables de directorio.
	DIR *dir;
    struct dirent **namelist;
    int n = 0;

    //Variables de hora y fecha.
    time_t now;
    struct tm *ts;
    char buf[80] = {0};
	char timestamp[16] = {0};

    //Obtengo la hora actual.
    now = time(0);
    //Formateo e imprimo fecha y hora en fromato "aaaammddhhmmss".
    ts = localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", ts);
    strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", ts);

    //Creo la variable "directorio" para verificar si el mismo existe antes de crearlo.
    char *directorio = malloc(strlen(homedir) + strlen(barra) + strlen(dirmuestras) + strlen(barra) + 1); //Nombre del directorio en donde irían las muestras.
    strcpy(directorio, homedir);
    strcat(directorio, barra);
    strcat(directorio, dirmuestras);
    strcat(directorio, barra);

    //Armo el path completo más el nombre del archivo que se creará.
	char *nomarch = malloc(strlen(homedir) + strlen(barra) + strlen(dirmuestras) + \
			strlen(barra) + strlen(buf) + strlen(nombase) + 1); //Nombre archivo + path completo.
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
    	//Si no existe creo el directorio con permisos de escritura para el usuario home.
    	mkdir(directorio, 0755);
    }

    //**********************************************************************
    //**************Cola circular del tipo FIFO de 1000 archivos************
    //**********************************************************************
    //Verifico si existe el directorio en donde se graban las muestras, sino lo creo.
    if((dir = opendir(directorio)) == NULL)
    {
    	printf("Falló opendir().\n");
		//Libero memoria.
    	//free(arrayjson);
		//arrayjson = NULL;
		closedir(dir);
		free(*namelist);
		free(directorio);
		directorio = NULL;
		free(nomarch);
		nomarch = NULL;
		free(nombaseborrar);
		nombaseborrar = NULL;
    	return EXIT_FAILURE;
    }
    else
    {
		if ((n = scandir(directorio, &namelist, NULL, alphasort)) == -1)
		{
			//Si scandir da -1 hubo un error.
			printf("Falló función \"scandir\".\n");
			//Libero memoria.
			//free(arrayjson);
			//arrayjson = NULL;
			closedir(dir);
			free(*namelist);
			free(directorio);
			directorio = NULL;
			free(nomarch);
			nomarch = NULL;
			free(nombaseborrar);
			nombaseborrar = NULL;
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
		    	//Libero memoria.
		    	fclose(fcrear);
				//free(arrayjson);
				//arrayjson = NULL;
				closedir(dir);
				free(*namelist);
				free(directorio);
				directorio = NULL;
				free(nomarch);
				nomarch = NULL;
				free(nombaseborrar);
				nombaseborrar = NULL;
		    	return EXIT_FAILURE;
			}
			else
			{
				//Acá se llama a la función de conversión de hexadecimal a JSON y se escribe el archivo JSON.
				//arrayjson = HexAJson(timestamp, arrayhex); //Acá se hace la conversión de HEXADECIMAL a JSON.
				//HexAJson(timestamp, arrayhex);
				//fprintf(fcrear, "%s", arrayjson); //Copia del array convertido de hexadecimal a JSON al archivo.
				//printf("Dirección ARRAYJSON: %p\n", &arrayjson);
				//fflush(fcrear);
			}
		}
		//Si llegué a tener más de 1000 archivos en el directorio, empiezo a borrar en orden FIFO.
		else if (n >= (maxfilebuffer+2)) //Debido a los directorios . y .. se suman dos directorios.
		{
			//Creo el path completo incluyendo el nombre del archivo a borrar.
			strcpy(nombaseborrar, directorio);
			strcat(nombaseborrar, namelist[2]->d_name);

			if((retunlink = unlink(nombaseborrar)) == -1)
				{
					//Error al querer borrar el archivo.
					printf("No se ha podido borrar el archivo.\n");
			    	//Libero memoria.
					//free(arrayjson);
					//arrayjson = NULL;
					closedir(dir);
					free(*namelist);
					free(directorio);
					directorio = NULL;
					free(nomarch);
					nomarch = NULL;
					free(nombaseborrar);
					nombaseborrar = NULL;
					return EXIT_FAILURE;
				}
			else
				{
					//Archivo borrado en forma correcta.
				}
		    //Borro un archivo y creo otro archivo dentro del directorio "~/MuestrasCMS2000" iterando los nombres de los mismos por segundo.
		    if ((fcrear = fopen(nomarch, "wb")) == NULL)
			{
		    	//Error al querer crear un archivo.
		    	printf("El archivo no pudo ser creado.\n");
		    	//Libero memoria.
		    	fclose(fcrear);
				//free(arrayjson);
				//arrayjson = NULL;
				closedir(dir);
				free(*namelist);
				free(directorio);
				directorio = NULL;
				free(nomarch);
				nomarch = NULL;
				free(nombaseborrar);
				nombaseborrar = NULL;
		    	return EXIT_FAILURE;
			}
			else
			{
				//Acá se llama a la función de conversión de hexadecimal a JSON y se escribe el archivo JSON.
				//arrayjson = HexAJson(timestamp, arrayhex); //Acá se hace la conversión de HEXADECIMAL a JSON.
				//HexAJson(timestamp, arrayhex);
				//fprintf(fcrear, "%s", arrayjson); //Copia del array convertido de hexadecimal a JSON al archivo.
				//printf("Dirección ARRAYJSON: %p\n", &arrayjson);
				//fflush(fcrear);
			}
		}
		else
		{
			//Error general de la función GuardarDataFileJSON.
			printf("Error de la función GuardarDataFileJSON");
	    	//Libero memoria.
			//free(arrayjson);
			//arrayjson = NULL;
			closedir(dir);
			free(*namelist);
			free(directorio);
			directorio = NULL;
			free(nomarch);
			nomarch = NULL;
			free(nombaseborrar);
			nombaseborrar = NULL;
			return EXIT_FAILURE;
		}
    }
	//Libero memoria.
    fclose(fcrear);
    //free(arrayjson);
	//arrayjson = NULL;
	closedir(dir);
	free(*namelist);
	free(directorio);
	directorio = NULL;
	free(nomarch);
	nomarch = NULL;
	free(nombaseborrar);
	nombaseborrar = NULL;
	//Finalizó sin error.
    return EXIT_SUCCESS;
}
