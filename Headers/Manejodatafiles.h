/*
 * Manejodatafiles.h
 *
 *  Created on: 29 jun. 2018
 *      Author: asrc
 */

#ifndef HEADERS_MANEJODATAFILES_H_
#define HEADERS_MANEJODATAFILES_H_

//Prototipo de función para recibir datos en forma de array más la longitud del
//mismo para luego ser guardados en archivos con nombres consecutivos en formato
//"aaaammddhhmmss_DataSetCMS2000.dat".
int GuardarDataFile(char *, int);

//Prototipo de función para leer archivos de datos con nombre en formato
//"aaaammddhhmmss_DataSetCMS2000.dat".
int LeerDataFile(char *);

//Prototipo de función para leer archivos en formato hexadecimal en STRING y
//convertirlos a formato JSON bajo el nombre "aaaammddhhmmss_DataSetCMS2000.json".
int GuardarDataFileJSON(char *, int);

//Prototipo de función para convertir los valores recibidos en Hexadecimal a
//formato JSON.
char *HexAJson(char *, char *);

#endif /* HEADERS_MANEJODATAFILES_H_ */
