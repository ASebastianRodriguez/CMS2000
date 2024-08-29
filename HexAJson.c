/*
 ============================================================================
 Name        : 20180906_Hex2Json.c
 Author      : ASRC
 Version     : 1.0
 Copyright   : HB
 Description : Función para recibir timestamp, un array en formato hexadecimal
 	 	 	   y la longitud del array en hexadecimal y luego convertir todos
 	 	 	   los datos a formato JSON.
			   La conversión de datos en hexadecimal a los respectivos
 	 	 	   formatos de datos se realiza dentro de esta función.
 ============================================================================
 */
/*******************************************************************************
PENDIENTES HexAJson:
	- Enviar el tamaño final del array JSON a la función GuardarDataFilesJSON.
	-
*******************************************************************************/
//******************************************************************************
//Función para recibir timestamp, un array en formato hexadecimal y la longitud
//del array en hexadecimal y luego convertir todos los datos a formato JSON.
//La conversión de datos en hexadecimal a los respectivos formatos de datos se
//realiza dentro de esta función.
//******************************************************************************

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
#include <float.h>

#include "Headers/Manejodatafiles.h"

char *HexAJson(char *timestampext, char *arrayhex)
{
	//**************************
	// Declaración de variables.
	//**************************
	//Contadores.
	int a = 0; //Utilizada para pruebas.
	int i = 0; //Utilizada para pruebas.

	//Variables de la misma función.
	char timestampextrcv[20] 		= {0}; //Timestamp extraido del sistema (en nuestro caso Yocto Linux).
	char *arrayhexrcv 				= arrayhex;
	char *arrayjson 				= NULL;
	int sizeofarrayjson 			= 0; //"sizeofarrayjson" es sólo para pruebas.

	//Declaración de variables recibidas por del CMS2000.
	//Header:
	char timestamp[11] 				= {0};
	char userdatalenght[11] 		= {0};
	char indextelegram[11] 			= {0};
	//User data:
	char operatingmode[4] 			= {0};
	char statusledgreen[4] 			= {0};
	char statusledyellow[4] 		= {0};
	char statusledred[4] 			= {0};
	char activeprocessalarms[4] 	= {0};
	char activesystemalarms[4] 		= {0};
	char activeprocesswarnings[4] 	= {0};
	char activesystemwarnings[4] 	= {0};
	char processmessagestobeack[4] 	= {0};
	char systemmessagestobeack[4] 	= {0};
	//Measured values:
	char speed[13] 					= {0};
	char oprhours[13] 				= {0};
	char ai1[13] 					= {0};
	char ai2[13] 					= {0};
	char temp11[13] 				= {0};
	char temp12[13] 				= {0};
	char temp13[13] 				= {0};
	char temp21[13] 				= {0};
	char temp22[13] 				= {0};
	char temp23[13] 				= {0};
	char vib1rms[13] 				= {0};
	char vib11rms[13] 				= {0};
	char vib12rms[13] 				= {0};
	char vib13rms[13] 				= {0};
	char vib14rms[13] 				= {0};
	char vib15rms[13] 				= {0};
	char vib16rms[13] 				= {0};
	char vib17rms[13] 				= {0};
	char vib18rms[13] 				= {0};
	char vib2rms[13] 				= {0};
	char vib21rms[13] 				= {0};
	char vib22rms[13] 				= {0};
	char vib23rms[13] 				= {0};
	char vib24rms[13] 				= {0};
	char vib25rms[13] 				= {0};
	char vib26rms[13] 				= {0};
	char vib27rms[13] 				= {0};
	char vib28rms[13] 				= {0};
	char vib1dkw[13] 				= {0};
	char vib11dkw[13] 				= {0};
	char vib12dkw[13] 				= {0};
	char vib13dkw[13] 				= {0};
	char vib14dkw[13] 				= {0};
	char vib15dkw[13] 				= {0};
	char vib16dkw[13] 				= {0};
	char vib17dkw[13] 				= {0};
	char vib18dkw[13] 				= {0};
	char vib2dkw[13] 				= {0};
	char vib21dkw[13] 				= {0};
	char vib22dkw[13] 				= {0};
	char vib23dkw[13] 				= {0};
	char vib24dkw[13] 				= {0};
	char vib25dkw[13] 				= {0};
	char vib26dkw[13] 				= {0};
	char vib27dkw[13] 				= {0};
	char vib28dkw[13] 				= {0};
	//Measured values status:
	char speed_status[6] 			= {0};
	char oprhours_status[6] 		= {0};
	char ai1_status[6] 				= {0};
	char ai2_status[6] 				= {0};
	char temp11_status[6] 			= {0};
	char temp12_status[6] 			= {0};
	char temp13_status[6] 			= {0};
	char temp21_status[6] 			= {0};
	char temp22_status[6] 			= {0};
	char temp23_status[6] 			= {0};
	char vib1rms_status[6] 			= {0};
	char vib11rms_status[6] 		= {0};
	char vib12rms_status[6] 		= {0};
	char vib13rms_status[6] 		= {0};
	char vib14rms_status[6] 		= {0};
	char vib15rms_status[6] 		= {0};
	char vib16rms_status[6] 		= {0};
	char vib17rms_status[6] 		= {0};
	char vib18rms_status[6] 		= {0};
	char vib2rms_status[6] 			= {0};
	char vib21rms_status[6] 		= {0};
	char vib22rms_status[6] 		= {0};
	char vib23rms_status[6] 		= {0};
	char vib24rms_status[6] 		= {0};
	char vib25rms_status[6] 		= {0};
	char vib26rms_status[6] 		= {0};
	char vib27rms_status[6] 		= {0};
	char vib28rms_status[6] 		= {0};
	char vib1dkw_status[6] 			= {0};
	char vib11dkw_status[6] 		= {0};
	char vib12dkw_status[6] 		= {0};
	char vib13dkw_status[6] 		= {0};
	char vib14dkw_status[6] 		= {0};
	char vib15dkw_status[6] 		= {0};
	char vib16dkw_status[6] 		= {0};
	char vib17dkw_status[6] 		= {0};
	char vib18dkw_status[6] 		= {0};
	char vib2dkw_status[6] 			= {0};
	char vib21dkw_status[6] 		= {0};
	char vib22dkw_status[6] 		= {0};
	char vib23dkw_status[6] 		= {0};
	char vib24dkw_status[6] 		= {0};
	char vib25dkw_status[6] 		= {0};
	char vib26dkw_status[6] 		= {0};
	char vib27dkw_status[6] 		= {0};
	char vib28dkw_status[6] 		= {0};
	// Spectrum status:
	char vib1vf[6] 					= {0};
	char vib11vf[6] 				= {0};
	char vib12vf[6] 				= {0};
	char vib13vf[6] 				= {0};
	char vib14vf[6] 				= {0};
	char vib15vf[6] 				= {0};
	char vib16vf[6] 				= {0};
	char vib17vf[6] 				= {0};
	char vib18vf[6] 				= {0};
	char vib2vf[6] 					= {0};
	char vib21vf[6] 				= {0};
	char vib22vf[6] 				= {0};
	char vib23vf[6] 				= {0};
	char vib24vf[6] 				= {0};
	char vib25vf[6] 				= {0};
	char vib26vf[6] 				= {0};
	char vib27vf[6] 				= {0};
	char vib28vf[6] 				= {0};
	char vib1af[6] 					= {0};
	char vib11af[6]					= {0};
	char vib12af[6] 				= {0};
	char vib13af[6] 				= {0};
	char vib14af[6] 				= {0};
	char vib15af[6] 				= {0};
	char vib16af[6] 				= {0};
	char vib17af[6] 				= {0};
	char vib18af[6] 				= {0};
	char vib2af[6] 					= {0};
	char vib21af[6] 				= {0};
	char vib22af[6] 				= {0};
	char vib23af[6] 				= {0};
	char vib24af[6] 				= {0};
	char vib25af[6] 				= {0};
	char vib26af[6] 				= {0};
	char vib27af[6] 				= {0};
	char vib28af[6] 				= {0};
	char vib1envf[6] 				= {0};
	char vib11envf[6] 				= {0};
	char vib12envf[6] 				= {0};
	char vib13envf[6] 				= {0};
	char vib14envf[6] 				= {0};
	char vib15envf[6] 				= {0};
	char vib16envf[6] 				= {0};
	char vib17envf[6] 				= {0};
	char vib18envf[6] 				= {0};
	char vib2envf[6] 				= {0};
	char vib21envf[6] 				= {0};
	char vib22envf[6] 				= {0};
	char vib23envf[6] 				= {0};
	char vib24envf[6] 				= {0};
	char vib25envf[6] 				= {0};
	char vib26envf[6] 				= {0};
	char vib27envf[6] 				= {0};
	char vib28envf[6] 				= {0};
	// End code:
	char endcode[9] 				= {0};

	//Variables temporales utilizadas para conversión:
	char temp1[4] 					= {0};
	char temp2[1] 					= {0};
	char temp3[4] 					= {0};
	char temp4[2] 					= {0};
	char temp5[2] 					= {0};
	char temp6[4] 					= {0};

	//Encabezados y nombres de variables del archivo JSON:
	char label0[] = "\"Header\":";
		char label000[] = "\"Tiempo_externo\":";
		char label001[] = "\"Time_stamp_[uS]\":";
		char label002[] = "\"User_data_lenght\":";
		char label003[] = "\"Index\":";
	char label1[] = "\"User_data\":";
		char label100[] = "\"Operating_mode\":";
		char label101[] = "\"Status_LED_normal_green\":";
		char label102[] = "\"Status_LED_warning_yellow\":";
		char label103[] = "\"Status_LED_alarm_red\":";
		char label104[] = "\"Active_process_alarms\":";
		char label105[] = "\"Active_system_alarms\":";
		char label106[] = "\"Active_process_warnings\":";
		char label107[] = "\"Active_system_warnings\":";
		char label108[] = "\"Process_messages_to_be_acknowledged\":";
		char label109[] = "\"System_messages_to_be_acknowledge\":";
	char label2[] = "\"Measured_values\":";
		char label200[] = "\"SPEED\":";
		char label201[] = "\"OPR_HOURS\":";
		char label202[] = "\"AI1\":";
		char label203[] = "\"AI2\":";
		char label204[] = "\"TEMP1.1\":";
		char label205[] = "\"TEMP1.2\":";
		char label206[] = "\"TEMP1.3\":";
		char label207[] = "\"TEMP2.1\":";
		char label208[] = "\"TEMP2.2\":";
		char label209[] = "\"TEMP2.3\":";
		char label210[] = "\"VIB1:RMS\":";
		char label211[] = "\"VIB1.1:RMS\":";
		char label212[] = "\"VIB1.2:RMS\":";
		char label213[] = "\"VIB1.3:RMS\":";
		char label214[] = "\"VIB1.4:RMS\":";
		char label215[] = "\"VIB1.5:RMS\":";
		char label216[] = "\"VIB1.6:RMS\":";
		char label217[] = "\"VIB1.7:RMS\":";
		char label218[] = "\"VIB1.8:RMS\":";
		char label219[] = "\"VIB2:RMS\":";
		char label220[] = "\"VIB2.1:RMS\":";
		char label221[] = "\"VIB2.2:RMS\":";
		char label222[] = "\"VIB2.3:RMS\":";
		char label223[] = "\"VIB2.4:RMS\":";
		char label224[] = "\"VIB2.5:RMS\":";
		char label225[] = "\"VIB2.6:RMS\":";
		char label226[] = "\"VIB2.7:RMS\":";
		char label227[] = "\"VIB2.8:RMS\":";
		char label228[] = "\"VIB1:DKW\":";
		char label229[] = "\"VIB1.1:DKW\":";
		char label230[] = "\"VIB1.2:DKW\":";
		char label231[] = "\"VIB1.3:DKW\":";
		char label232[] = "\"VIB1.4:DKW\":";
		char label233[] = "\"VIB1.5:DKW\":";
		char label234[] = "\"VIB1.6:DKW\":";
		char label235[] = "\"VIB1.7:DKW\":";
		char label236[] = "\"VIB1.8:DKW\":";
		char label237[] = "\"VIB2:DKW\":";
		char label238[] = "\"VIB2.1:DKW\":";
		char label239[] = "\"VIB2.2:DKW\":";
		char label240[] = "\"VIB2.3:DKW\":";
		char label241[] = "\"VIB2.4:DKW\":";
		char label242[] = "\"VIB2.5:DKW\":";
		char label243[] = "\"VIB2.6:DKW\":";
		char label244[] = "\"VIB2.7:DKW\":";
		char label245[] = "\"VIB2.8:DKW\":";
	char label3[] = "\"Measured_value_status\":";
		char label300[] = "\"SPEED\":";
		char label301[] = "\"OPR_HOURS\":";
		char label302[] = "\"AI1\":";
		char label303[] = "\"AI2\":";
		char label304[] = "\"TEMP1.1\":";
		char label305[] = "\"TEMP1.2\":";
		char label306[] = "\"TEMP1.3\":";
		char label307[] = "\"TEMP2.1\":";
		char label308[] = "\"TEMP2.2\":";
		char label309[] = "\"TEMP2.3\":";
		char label310[] = "\"VIB1:RMS\":";
		char label311[] = "\"VIB1.1:RMS\":";
		char label312[] = "\"VIB1.2:RMS\":";
		char label313[] = "\"VIB1.3:RMS\":";
		char label314[] = "\"VIB1.4:RMS\":";
		char label315[] = "\"VIB1.5:RMS\":";
		char label316[] = "\"VIB1.6:RMS\":";
		char label317[] = "\"VIB1.7:RMS\":";
		char label318[] = "\"VIB1.8:RMS\":";
		char label319[] = "\"VIB2:RMS\":";
		char label320[] = "\"VIB2.1:RMS\":";
		char label321[] = "\"VIB2.2:RMS\":";
		char label322[] = "\"VIB2.3:RMS\":";
		char label323[] = "\"VIB2.4:RMS\":";
		char label324[] = "\"VIB2.5:RMS\":";
		char label325[] = "\"VIB2.6:RMS\":";
		char label326[] = "\"VIB2.7:RMS\":";
		char label327[] = "\"VIB2.8:RMS\":";
		char label328[] = "\"VIB1:DKW\":";
		char label329[] = "\"VIB1.1:DKW\":";
		char label330[] = "\"VIB1.2:DKW\":";
		char label331[] = "\"VIB1.3:DKW\":";
		char label332[] = "\"VIB1.4:DKW\":";
		char label333[] = "\"VIB1.5:DKW\":";
		char label334[] = "\"VIB1.6:DKW\":";
		char label335[] = "\"VIB1.7:DKW\":";
		char label336[] = "\"VIB1.8:DKW\":";
		char label337[] = "\"VIB2:DKW\":";
		char label338[] = "\"VIB2.1:DKW\":";
		char label339[] = "\"VIB2.2:DKW\":";
		char label340[] = "\"VIB2.3:DKW\":";
		char label341[] = "\"VIB2.4:DKW\":";
		char label342[] = "\"VIB2.5:DKW\":";
		char label343[] = "\"VIB2.6:DKW\":";
		char label344[] = "\"VIB2.7:DKW\":";
		char label345[] = "\"VIB2.8:DKW\":";
	char label4[] = "\"Spectrum_status\":";
		char label400[] = "\"VIB1:v(f)\":";
		char label401[] = "\"VIB1.1:v(f)\":";
		char label402[] = "\"VIB1.2:v(f)\":";
		char label403[] = "\"VIB1.3:v(f)\":";
		char label404[] = "\"VIB1.4:v(f)\":";
		char label405[] = "\"VIB1.5:v(f)\":";
		char label406[] = "\"VIB1.6:v(f)\":";
		char label407[] = "\"VIB1.7:v(f)\":";
		char label408[] = "\"VIB1.8:v(f)\":";
		char label409[] = "\"VIB2:v(f)\":";
		char label410[] = "\"VIB2.1:v(f)\":";
		char label411[] = "\"VIB2.2:v(f)\":";
		char label412[] = "\"VIB2.3:v(f)\":";
		char label413[] = "\"VIB2.4:v(f)\":";
		char label414[] = "\"VIB2.5:v(f)\":";
		char label415[] = "\"VIB2.6:v(f)\":";
		char label416[] = "\"VIB2.7:v(f)\":";
		char label417[] = "\"VIB2.8:v(f)\":";
		char label418[] = "\"VIB1:a(f)\":";
		char label419[] = "\"VIB1.1:a(f)\":";
		char label420[] = "\"VIB1.2:a(f)\":";
		char label421[] = "\"VIB1.3:a(f)\":";
		char label422[] = "\"VIB1.4:a(f)\":";
		char label423[] = "\"VIB1.5:a(f)\":";
		char label424[] = "\"VIB1.6:a(f)\":";
		char label425[] = "\"VIB1.7:a(f)\":";
		char label426[] = "\"VIB1.8:a(f)\":";
		char label427[] = "\"VIB2:a(f)\":";
		char label428[] = "\"VIB2.1:a(f)\":";
		char label429[] = "\"VIB2.2:a(f)\":";
		char label430[] = "\"VIB2.3:a(f)\":";
		char label431[] = "\"VIB2.4:a(f)\":";
		char label432[] = "\"VIB2.5:a(f)\":";
		char label433[] = "\"VIB2.6:a(f)\":";
		char label434[] = "\"VIB2.7:a(f)\":";
		char label435[] = "\"VIB2.8:a(f)\":";
		char label436[] = "\"VIB1:env(f)\":";
		char label437[] = "\"VIB1.1:env(f)\":";
		char label438[] = "\"VIB1.2:env(f)\":";
		char label439[] = "\"VIB1.3:env(f)\":";
		char label440[] = "\"VIB1.4:env(f)\":";
		char label441[] = "\"VIB1.5:env(f)\":";
		char label442[] = "\"VIB1.6:env(f)\":";
		char label443[] = "\"VIB1.7:env(f)\":";
		char label444[] = "\"VIB1.8:env(f)\":";
		char label445[] = "\"VIB2:env(f)\":";
		char label446[] = "\"VIB2.1:env(f)\":";
		char label447[] = "\"VIB2.2:env(f)\":";
		char label448[] = "\"VIB2.3:env(f)\":";
		char label449[] = "\"VIB2.4:env(f)\":";
		char label450[] = "\"VIB2.5:env(f)\":";
		char label451[] = "\"VIB2.6:env(f)\":";
		char label452[] = "\"VIB2.7:env(f)\":";
		char label453[] = "\"VIB2.8:env(f)\":";
	char label5[] = "\"End_code\":";
	// Caracteres de separación.
	char llavea[] 		= "{";
	char llavec[] 		= "}";
	char coma[] 		= ",";
	char comilla[] 		= "\"";
	char tab[] 			= "\t";
	char newline[] 		= "\n";
	char nullchar[] 	= "\0";
	//******************************
	// Fin declaración de variables.
	//******************************

	/**************************************************************************
	//Conversión de datos hexadecimales a los diferentes tipos de valores.
	//
	//NOTA IMPORTANTE:
	//					TENER EN CUENTA QUE LOS VALORES VIENEN DEL ARCHIVO
	//EN FORMATO ASCII. ES POR ESTO QUE HABRÁ QUE CONVERTIRLOS DE ASCII A
	//HEXADECIMAL Y LUEGO A VALORES NUMÉRICOS.
	//
	//ÍNDICE DE GRUPOS DE DATOS:
	// 							- Header.
	//							- User data.
	//					 		- Measured values.
	//					 		- Measured values status.
	//					 		- Spectrum status.
	//************************************************************************/
	//Timestamp Externo.
	timestampextrcv[0] = timestampext[0];
	timestampextrcv[1] = timestampext[1];
	timestampextrcv[2] = timestampext[2];
	timestampextrcv[3] = timestampext[3];
	timestampextrcv[4] = '-';
	timestampextrcv[5] = timestampext[4];
	timestampextrcv[6] = timestampext[5];
	timestampextrcv[7] = '-';
	timestampextrcv[8] = timestampext[6];
	timestampextrcv[9] = timestampext[7];
	timestampextrcv[10] = 'T';
	timestampextrcv[11] = timestampext[8];
	timestampextrcv[12] = timestampext[9];
	timestampextrcv[13] = ':';
	timestampextrcv[14] = timestampext[10];
	timestampextrcv[15] = timestampext[11];
	timestampextrcv[16] = ':';
	timestampextrcv[17] = timestampext[12];
	timestampextrcv[18] = timestampext[13];
	timestampextrcv[19] = '\0';
//	printf("Timestamp externo: %s\n", timestampextrcv);

	//**************************************************************************
	//Header:
	//**************************************************************************
	//Timestamp.
	temp1[0] = arrayhexrcv[0];
	temp1[1] = arrayhexrcv[1];
	temp1[2] = arrayhexrcv[2];
	temp1[3] = arrayhexrcv[3];
	a = snprintf(timestamp, 11, "%lu", *(unsigned long int *)temp1);
	//printf("Timestamp: %s\n", timestamp);

	//User data lenght.
	temp1[0] = arrayhexrcv[4];
	temp1[1] = arrayhexrcv[5];
	temp1[2] = arrayhexrcv[6];
	temp1[3] = arrayhexrcv[7];
	a = snprintf(userdatalenght, 11, "%lu", *(unsigned long int *)temp1);
	//printf("User data lenght: %s\n", userdatalenght);

	//Index.
	temp1[0] = arrayhexrcv[8];
	temp1[1] = arrayhexrcv[9];
	temp1[2] = arrayhexrcv[10];
	temp1[3] = arrayhexrcv[11];
	a = snprintf(indextelegram, 11, "%lu", *(unsigned long int *)temp1);
	//printf("Index: %s\n", indextelegram);

	//**************************************************************************
	//User data:
	//**************************************************************************
	//Operating mode.
	temp2[0] = arrayhexrcv[12];
	a = snprintf(operatingmode, 4, "%u", *(unsigned char *)temp2);
	//printf("Operating mode: %s\n", operatingmode);

	//Status LED green (Normal).
	temp2[0] = arrayhexrcv[13];
	a = snprintf(statusledgreen, 4, "%u", *(unsigned char *)temp2);
	//printf("Status LED green: %s\n", statusledgreen);

	//Status LED yellow (Warning).
	temp2[0] = arrayhexrcv[14];
	a = snprintf(statusledyellow, 4, "%u", *(unsigned char *)temp2);
	//printf("Status LED yellow: %s\n", statusledyellow);

	//Status LED red (Alarm).
	temp2[0] = arrayhexrcv[15];
	a = snprintf(statusledred, 4, "%u", *(unsigned char *)temp2);
	//printf("Status LED red: %s\n", statusledred);

	//Active process alarms.
	temp2[0] = arrayhexrcv[16];
	a = snprintf(activeprocessalarms, 4, "%u", *(unsigned char *)temp2);
	//printf("Active process alarms: %s\n", activeprocessalarms);

	//Active system alarms.
	temp2[0] = arrayhexrcv[17];
	a = snprintf(activesystemalarms, 4, "%u", *(unsigned char *)temp2);
	//printf("Active system alarms: %s\n", activesystemalarms);

	//Active process warnings.
	temp2[0] = arrayhexrcv[18];
	a = snprintf(activeprocesswarnings, 4, "%u", *(unsigned char *)temp2);
	//printf("Active process warnings: %s\n", activeprocesswarnings);

	//Active system warnings.
	temp2[0] = arrayhexrcv[19];
	a = snprintf(activesystemwarnings, 4, "%u", *(unsigned char *)temp2);
	//printf("Active system warnings: %s\n", activesystemwarnings);

	//Process messages to be acknowledge.
	temp2[0] = arrayhexrcv[20];
	a = snprintf(processmessagestobeack, 4, "%u", *(unsigned char *)temp2);
	//printf("Process messages to be ack: %s\n", processmessagestobeack);

	//System messages to be acknowledge.
	temp2[0] = arrayhexrcv[21];
	a = snprintf(systemmessagestobeack, 4, "%u", *(unsigned char *)temp2);
	//printf("System messages to be ack: %s\n", systemmessagestobeack);

	//**************************************************************************
	//Measured values:
	//**************************************************************************
	//Speed.
	temp3[0] = arrayhexrcv[28];
	temp3[1] = arrayhexrcv[29];
	temp3[2] = arrayhexrcv[30];
	temp3[3] = arrayhexrcv[31];
	a = snprintf(speed, 13, "%e", *(float *)temp3);
//	printf("Longitud de string speed: %i\n", a);
//	i = 0;
//	while (speed[i]!='\0')
//	{
//	    printf("%c", speed[i]);
//	    i++;
//	}
//	printf("\n");

	//Operation hours.
	temp3[0] = arrayhexrcv[32];
	temp3[1] = arrayhexrcv[33];
	temp3[2] = arrayhexrcv[34];
	temp3[3] = arrayhexrcv[35];
	a = snprintf(oprhours, 13, "%e", *(float *)temp3);
	//printf("Opr. hours: %s\n", oprhours);

	//Analog Input 1.
	temp3[0] = arrayhexrcv[36];
	temp3[1] = arrayhexrcv[37];
	temp3[2] = arrayhexrcv[38];
	temp3[3] = arrayhexrcv[39];
	a = snprintf(ai1, 13, "%e", *(float *)temp3);
	//printf("Analog input 1: %s\n", ai1);

	//Analog Input 2.
	temp3[0] = arrayhexrcv[40];
	temp3[1] = arrayhexrcv[41];
	temp3[2] = arrayhexrcv[42];
	temp3[3] = arrayhexrcv[43];
	a = snprintf(ai2, 13, "%e", *(float *)temp3);
	//printf("Analog input 2: %s\n", ai2);

	//Temp 1.1.
	temp3[0] = arrayhexrcv[44];
	temp3[1] = arrayhexrcv[45];
	temp3[2] = arrayhexrcv[46];
	temp3[3] = arrayhexrcv[47];
	a = snprintf(temp11, 13, "%e", *(float *)temp3);
	//printf("Temp. 1.1: %s\n", temp11);

	//Temp 1.2.
	temp3[0] = arrayhexrcv[48];
	temp3[1] = arrayhexrcv[49];
	temp3[2] = arrayhexrcv[50];
	temp3[3] = arrayhexrcv[51];
	a = snprintf(temp12, 13, "%e", *(float *)temp3);
	//printf("Temp. 1.2: %s\n", temp12);

	//Temp 1.3.
	temp3[0] = arrayhexrcv[52];
	temp3[1] = arrayhexrcv[53];
	temp3[2] = arrayhexrcv[54];
	temp3[3] = arrayhexrcv[55];
	a = snprintf(temp13, 13, "%e", *(float *)temp3);
	//printf("Temp. 1.3: %s\n", temp13);

	//Temp 2.1.
	temp3[0] = arrayhexrcv[56];
	temp3[1] = arrayhexrcv[57];
	temp3[2] = arrayhexrcv[58];
	temp3[3] = arrayhexrcv[59];
	a = snprintf(temp21, 13, "%e", *(float *)temp3);
	//printf("Temp. 2.1: %s\n", temp21);

	//Temp 2.2.
	temp3[0] = arrayhexrcv[60];
	temp3[1] = arrayhexrcv[61];
	temp3[2] = arrayhexrcv[62];
	temp3[3] = arrayhexrcv[63];
	a = snprintf(temp22, 13, "%e", *(float *)temp3);
	//printf("Temp. 2.2: %s\n", temp22);

	//Temp 2.3.
	temp3[0] = arrayhexrcv[64];
	temp3[1] = arrayhexrcv[65];
	temp3[2] = arrayhexrcv[66];
	temp3[3] = arrayhexrcv[67];
	a = snprintf(temp23, 13, "%e", *(float *)temp3);
	//printf("Temp. 2.3: %s\n", temp23);

	//VIB 1:RMS.
	temp3[0] = arrayhexrcv[100];
	temp3[1] = arrayhexrcv[101];
	temp3[2] = arrayhexrcv[102];
	temp3[3] = arrayhexrcv[103];
	a = snprintf(vib1rms, 13, "%e", *(float *)temp3);
	//printf("VIB 1:RMS: %s\n", vib1rms);


	//VIB 1.1:RMS.
	temp3[0] = arrayhexrcv[104];
	temp3[1] = arrayhexrcv[105];
	temp3[2] = arrayhexrcv[106];
	temp3[3] = arrayhexrcv[107];
	a = snprintf(vib11rms, 13, "%e", *(float *)temp3);
	//printf("VIB 1.1:RMS: %s\n", vib11rms);

	//VIB 1.2:RMS.
	temp3[0] = arrayhexrcv[108];
	temp3[1] = arrayhexrcv[109];
	temp3[2] = arrayhexrcv[110];
	temp3[3] = arrayhexrcv[111];
	a = snprintf(vib12rms, 13, "%e", *(float *)temp3);
	//printf("VIB 1.2:RMS: %s\n", vib12rms);

	//VIB 1.3:RMS.
	temp3[0] = arrayhexrcv[112];
	temp3[1] = arrayhexrcv[113];
	temp3[2] = arrayhexrcv[114];
	temp3[3] = arrayhexrcv[115];
	a = snprintf(vib13rms, 13, "%e", *(float *)temp3);
	//printf("VIB 1.3:RMS: %s\n", vib13rms);

	//VIB 1.4:RMS.
	temp3[0] = arrayhexrcv[116];
	temp3[1] = arrayhexrcv[117];
	temp3[2] = arrayhexrcv[118];
	temp3[3] = arrayhexrcv[119];
	a = snprintf(vib14rms, 13, "%e", *(float *)temp3);
	//printf("VIB 1.4:RMS: %s\n", vib14rms);

	//VIB 1.5:RMS.
	temp3[0] = arrayhexrcv[120];
	temp3[1] = arrayhexrcv[121];
	temp3[2] = arrayhexrcv[122];
	temp3[3] = arrayhexrcv[123];
	a = snprintf(vib15rms, 13, "%e", *(float *)temp3);
	//printf("VIB 1.5:RMS: %s\n", vib15rms);

	//VIB 1.6:RMS.
	temp3[0] = arrayhexrcv[124];
	temp3[1] = arrayhexrcv[125];
	temp3[2] = arrayhexrcv[126];
	temp3[3] = arrayhexrcv[127];
	a = snprintf(vib16rms, 13, "%e", *(float *)temp3);
	//printf("VIB 1.6:RMS: %s\n", vib16rms);

	//VIB 1.7:RMS.
	temp3[0] = arrayhexrcv[128];
	temp3[1] = arrayhexrcv[129];
	temp3[2] = arrayhexrcv[130];
	temp3[3] = arrayhexrcv[131];
	a = snprintf(vib17rms, 13, "%e", *(float *)temp3);
	//printf("VIB 1.7:RMS: %s\n", vib17rms);

	//VIB 1.8:RMS.
	temp3[0] = arrayhexrcv[132];
	temp3[1] = arrayhexrcv[133];
	temp3[2] = arrayhexrcv[134];
	temp3[3] = arrayhexrcv[135];
	a = snprintf(vib18rms, 13, "%e", *(float *)temp3);
	//printf("VIB 1.8:RMS: %s\n", vib18rms);

	//VIB 2:RMS.
	temp3[0] = arrayhexrcv[136];
	temp3[1] = arrayhexrcv[137];
	temp3[2] = arrayhexrcv[138];
	temp3[3] = arrayhexrcv[139];
	a = snprintf(vib2rms, 13, "%e", *(float *)temp3);
	//printf("VIB 2:RMS: %s\n", vib2rms);

	//VIB 2.1:RMS.
	temp3[0] = arrayhexrcv[140];
	temp3[1] = arrayhexrcv[141];
	temp3[2] = arrayhexrcv[142];
	temp3[3] = arrayhexrcv[143];
	a = snprintf(vib21rms, 13, "%e", *(float *)temp3);
	//printf("VIB 2.1:RMS: %s\n", vib21rms);

	//VIB 2.2:RMS.
	temp3[0] = arrayhexrcv[144];
	temp3[1] = arrayhexrcv[145];
	temp3[2] = arrayhexrcv[146];
	temp3[3] = arrayhexrcv[147];
	a = snprintf(vib22rms, 13, "%e", *(float *)temp3);
	//printf("VIB 2.2:RMS: %s\n", vib22rms);

	//VIB 2.3:RMS.
	temp3[0] = arrayhexrcv[148];
	temp3[1] = arrayhexrcv[149];
	temp3[2] = arrayhexrcv[150];
	temp3[3] = arrayhexrcv[151];
	a = snprintf(vib23rms, 13, "%e", *(float *)temp3);
	//printf("VIB 2.3:RMS: %s\n", vib23rms);

	//VIB 2.4:RMS.
	temp3[0] = arrayhexrcv[152];
	temp3[1] = arrayhexrcv[153];
	temp3[2] = arrayhexrcv[154];
	temp3[3] = arrayhexrcv[155];
	a = snprintf(vib24rms, 13, "%e", *(float *)temp3);
	//printf("VIB 2.4:RMS: %s\n", vib24rms);

	//VIB 2.5:RMS.
	temp3[0] = arrayhexrcv[156];
	temp3[1] = arrayhexrcv[157];
	temp3[2] = arrayhexrcv[158];
	temp3[3] = arrayhexrcv[159];
	a = snprintf(vib25rms, 13, "%e", *(float *)temp3);
	//printf("VIB 2.5:RMS: %s\n", vib25rms);

	//VIB 2.6:RMS.
	temp3[0] = arrayhexrcv[160];
	temp3[1] = arrayhexrcv[161];
	temp3[2] = arrayhexrcv[162];
	temp3[3] = arrayhexrcv[163];
	a = snprintf(vib26rms, 13, "%e", *(float *)temp3);
	//printf("VIB 2.6:RMS: %s\n", vib26rms);

	//VIB 2.7:RMS.
	temp3[0] = arrayhexrcv[164];
	temp3[1] = arrayhexrcv[165];
	temp3[2] = arrayhexrcv[166];
	temp3[3] = arrayhexrcv[167];
	a = snprintf(vib27rms, 13, "%e", *(float *)temp3);
	//printf("VIB 2.7:RMS: %s\n", vib27rms);

	//VIB 2.8:RMS.
	temp3[0] = arrayhexrcv[168];
	temp3[1] = arrayhexrcv[169];
	temp3[2] = arrayhexrcv[170];
	temp3[3] = arrayhexrcv[171];
	a = snprintf(vib28rms, 13, "%e", *(float *)temp3);
	//printf("VIB 2.8:RMS: %s\n", vib28rms);

	//VIB 1:DKW.
	temp3[0] = arrayhexrcv[172];
	temp3[1] = arrayhexrcv[173];
	temp3[2] = arrayhexrcv[174];
	temp3[3] = arrayhexrcv[175];
	a = snprintf(vib1dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 1:DKW: %s\n", vib1dkw);

	//VIB 1.1:DKW.
	temp3[0] = arrayhexrcv[176];
	temp3[1] = arrayhexrcv[177];
	temp3[2] = arrayhexrcv[178];
	temp3[3] = arrayhexrcv[179];
	a = snprintf(vib11dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 1.1:DKW: %s\n", vib11dkw);

	//VIB 1.2:DKW.
	temp3[0] = arrayhexrcv[180];
	temp3[1] = arrayhexrcv[181];
	temp3[2] = arrayhexrcv[182];
	temp3[3] = arrayhexrcv[183];
	a = snprintf(vib12dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 1.2:DKW: %s\n", vib12dkw);

	//VIB 1.3:DKW.
	temp3[0] = arrayhexrcv[184];
	temp3[1] = arrayhexrcv[185];
	temp3[2] = arrayhexrcv[186];
	temp3[3] = arrayhexrcv[187];
	a = snprintf(vib13dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 1.3:DKW: %s\n", vib13dkw);

	//VIB 1.4:DKW.
	temp3[0] = arrayhexrcv[188];
	temp3[1] = arrayhexrcv[189];
	temp3[2] = arrayhexrcv[190];
	temp3[3] = arrayhexrcv[191];
	a = snprintf(vib14dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 1.4:DKW: %s\n", vib14dkw);

	//VIB 1.5:DKW.
	temp3[0] = arrayhexrcv[192];
	temp3[1] = arrayhexrcv[193];
	temp3[2] = arrayhexrcv[194];
	temp3[3] = arrayhexrcv[195];
	a = snprintf(vib15dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 1.5:DKW: %s\n", vib15dkw);

	//VIB 1.6:DKW.
	temp3[0] = arrayhexrcv[196];
	temp3[1] = arrayhexrcv[197];
	temp3[2] = arrayhexrcv[198];
	temp3[3] = arrayhexrcv[199];
	a = snprintf(vib16dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 1.6:DKW: %s\n", vib16dkw);

	//VIB 1.7:DKW.
	temp3[0] = arrayhexrcv[200];
	temp3[1] = arrayhexrcv[201];
	temp3[2] = arrayhexrcv[202];
	temp3[3] = arrayhexrcv[203];
	a = snprintf(vib17dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 1.7:DKW: %s\n", vib17dkw);

	//VIB 1.8:DKW.
	temp3[0] = arrayhexrcv[204];
	temp3[1] = arrayhexrcv[205];
	temp3[2] = arrayhexrcv[206];
	temp3[3] = arrayhexrcv[207];
	a = snprintf(vib18dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 1.8:DKW: %s\n", vib18dkw);

	//VIB 2:DKW.
	temp3[0] = arrayhexrcv[208];
	temp3[1] = arrayhexrcv[209];
	temp3[2] = arrayhexrcv[210];
	temp3[3] = arrayhexrcv[211];
	a = snprintf(vib2dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 2:DKW: %s\n", vib2dkw);

	//VIB 2.1:DKW.
	temp3[0] = arrayhexrcv[212];
	temp3[1] = arrayhexrcv[213];
	temp3[2] = arrayhexrcv[214];
	temp3[3] = arrayhexrcv[215];
	a = snprintf(vib21dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 2.1:DKW: %s\n", vib21dkw);

	//VIB 2.2:DKW.
	temp3[0] = arrayhexrcv[216];
	temp3[1] = arrayhexrcv[217];
	temp3[2] = arrayhexrcv[218];
	temp3[3] = arrayhexrcv[219];
	a = snprintf(vib22dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 2.2:DKW: %s\n", vib22dkw);

	//VIB 2.3:DKW.
	temp3[0] = arrayhexrcv[220];
	temp3[1] = arrayhexrcv[221];
	temp3[2] = arrayhexrcv[222];
	temp3[3] = arrayhexrcv[223];
	a = snprintf(vib23dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 2.3:DKW: %s\n", vib23dkw);

	//VIB 2.4:DKW.
	temp3[0] = arrayhexrcv[224];
	temp3[1] = arrayhexrcv[225];
	temp3[2] = arrayhexrcv[226];
	temp3[3] = arrayhexrcv[227];
	a = snprintf(vib24dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 2.4:DKW: %s\n", vib24dkw);

	//VIB 2.5:DKW.
	temp3[0] = arrayhexrcv[228];
	temp3[1] = arrayhexrcv[229];
	temp3[2] = arrayhexrcv[230];
	temp3[3] = arrayhexrcv[231];
	a = snprintf(vib25dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 2.5:DKW: %s\n", vib25dkw);

	//VIB 2.6:DKW.
	temp3[0] = arrayhexrcv[232];
	temp3[1] = arrayhexrcv[233];
	temp3[2] = arrayhexrcv[234];
	temp3[3] = arrayhexrcv[235];
	a = snprintf(vib26dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 2.6:DKW: %s\n", vib26dkw);

	//VIB 2.7:DKW.
	temp3[0] = arrayhexrcv[236];
	temp3[1] = arrayhexrcv[237];
	temp3[2] = arrayhexrcv[238];
	temp3[3] = arrayhexrcv[239];
	a = snprintf(vib27dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 2.7:DKW: %s\n", vib27dkw);

	//VIB 2.8:DKW.
	temp3[0] = arrayhexrcv[240];
	temp3[1] = arrayhexrcv[241];
	temp3[2] = arrayhexrcv[242];
	temp3[3] = arrayhexrcv[243];
	a = snprintf(vib28dkw, 13, "%e", *(float *)temp3);
	//printf("VIB 2.8:DKW: %s\n", vib28dkw);

	//**************************************************************************
	//Measured values status:
	//**************************************************************************
	//Speed status.
	temp4[0] = arrayhexrcv[284];
	temp4[1] = arrayhexrcv[285];
	a = snprintf(speed_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("Speed status: %s\n", speed_status);

	//Operation hours status.
	temp4[0] = arrayhexrcv[286];
	temp4[1] = arrayhexrcv[287];
	a = snprintf(oprhours_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("Opr. hours status: %s\n", oprhours_status);

	//AI1 status.
	temp4[0] = arrayhexrcv[288];
	temp4[1] = arrayhexrcv[289];
	a = snprintf(ai1_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("Analog input 1 status: %s\n", ai1_status);

	//AI2 status.
	temp4[0] = arrayhexrcv[290];
	temp4[1] = arrayhexrcv[291];
	a = snprintf(ai2_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("Analog input 2 status: %s\n", ai2_status);

	//Temp. 1.1 status.
	temp4[0] = arrayhexrcv[292];
	temp4[1] = arrayhexrcv[293];
	a = snprintf(temp11_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("Temp. 1.1 status: %s\n", temp11_status);

	//Temp. 1.2 status.
	temp4[0] = arrayhexrcv[294];
	temp4[1] = arrayhexrcv[295];
	a = snprintf(temp12_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("Temp. 1.2 status: %s\n", temp12_status);

	//Temp. 1.3 status.
	temp4[0] = arrayhexrcv[296];
	temp4[1] = arrayhexrcv[297];
	a = snprintf(temp13_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("Temp. 1.3 status: %s\n", temp13_status);

	//Temp. 2.1 status.
	temp4[0] = arrayhexrcv[298];
	temp4[1] = arrayhexrcv[299];
	a = snprintf(temp21_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("Temp. 2.1 status: %s\n", temp21_status);

	//Temp. 2.2 status.
	temp4[0] = arrayhexrcv[300];
	temp4[1] = arrayhexrcv[301];
	a = snprintf(temp22_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("Temp. 2.2 status: %s\n", temp22_status);

	//Temp. 2.3 status.
	temp4[0] = arrayhexrcv[302];
	temp4[1] = arrayhexrcv[303];
	a = snprintf(temp23_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("Temp. 2.3 status: %s\n", temp23_status);

	//VIB 1:RMS status.
	temp4[0] = arrayhexrcv[320];
	temp4[1] = arrayhexrcv[321];
	a = snprintf(vib1rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1:RMS status: %s\n", vib1rms_status);

	//VIB 1.1:RMS status.
	temp4[0] = arrayhexrcv[322];
	temp4[1] = arrayhexrcv[323];
	a = snprintf(vib11rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.1:RMS status: %s\n", vib11rms_status);

	//VIB 1.2:RMS status.
	temp4[0] = arrayhexrcv[324];
	temp4[1] = arrayhexrcv[325];
	a = snprintf(vib12rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.2:RMS status: %s\n", vib12rms_status);

	//VIB 1.3:RMS status.
	temp4[0] = arrayhexrcv[326];
	temp4[1] = arrayhexrcv[327];
	a = snprintf(vib13rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.3:RMS status: %s\n", vib13rms_status);

	//VIB 1.4:RMS status.
	temp4[0] = arrayhexrcv[328];
	temp4[1] = arrayhexrcv[329];
	a = snprintf(vib14rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.4:RMS status: %s\n", vib14rms_status);

	//VIB 1.5:RMS status.
	temp4[0] = arrayhexrcv[330];
	temp4[1] = arrayhexrcv[331];
	a = snprintf(vib15rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.5:RMS status: %s\n", vib15rms_status);

	//VIB 1.6:RMS status.
	temp4[0] = arrayhexrcv[332];
	temp4[1] = arrayhexrcv[333];
	a = snprintf(vib16rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.6:RMS status: %s\n", vib16rms_status);

	//VIB 1.7:RMS status.
	temp4[0] = arrayhexrcv[334];
	temp4[1] = arrayhexrcv[335];
	a = snprintf(vib17rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.7:RMS status: %s\n", vib17rms_status);

	//VIB 1.8:RMS status.
	temp4[0] = arrayhexrcv[336];
	temp4[1] = arrayhexrcv[337];
	a = snprintf(vib18rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.8:RMS status: %s\n", vib18rms_status);

	//VIB 2:RMS status.
	temp4[0] = arrayhexrcv[338];
	temp4[1] = arrayhexrcv[339];
	a = snprintf(vib2rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2:RMS status: %s\n", vib2rms_status);

	//VIB 2.1:RMS status.
	temp4[0] = arrayhexrcv[340];
	temp4[1] = arrayhexrcv[341];
	a = snprintf(vib21rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.1:RMS status: %s\n", vib21rms_status);

	//VIB 2.2:RMS status.
	temp4[0] = arrayhexrcv[342];
	temp4[1] = arrayhexrcv[343];
	a = snprintf(vib22rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.2:RMS status: %s\n", vib22rms_status);

	//VIB 2.3:RMS status.
	temp4[0] = arrayhexrcv[344];
	temp4[1] = arrayhexrcv[345];
	a = snprintf(vib23rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.3:RMS status: %s\n", vib23rms_status);

	//VIB 2.4:RMS status.
	temp4[0] = arrayhexrcv[346];
	temp4[1] = arrayhexrcv[347];
	a = snprintf(vib24rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.4:RMS status: %s\n", vib24rms_status);

	//VIB 2.5:RMS status.
	temp4[0] = arrayhexrcv[348];
	temp4[1] = arrayhexrcv[349];
	a = snprintf(vib25rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.5:RMS status: %s\n", vib25rms_status);

	//VIB 2.6:RMS status.
	temp4[0] = arrayhexrcv[350];
	temp4[1] = arrayhexrcv[351];
	a = snprintf(vib26rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.6:RMS status: %s\n", vib26rms_status);

	//VIB 2.7:RMS status.
	temp4[0] = arrayhexrcv[352];
	temp4[1] = arrayhexrcv[353];
	a = snprintf(vib27rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.7:RMS status: %s\n", vib27rms_status);

	//VIB 2.8:RMS status.
	temp4[0] = arrayhexrcv[354];
	temp4[1] = arrayhexrcv[355];
	a = snprintf(vib28rms_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.8:RMS status: %s\n", vib28rms_status);

	//VIB 1:DKW status.
	temp4[0] = arrayhexrcv[356];
	temp4[1] = arrayhexrcv[357];
	a = snprintf(vib1dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1:DKW status: %s\n", vib1dkw_status);

	//VIB 1.1:DKW status.
	temp4[0] = arrayhexrcv[358];
	temp4[1] = arrayhexrcv[359];
	a = snprintf(vib11dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.1:DKW status: %s\n", vib11dkw_status);

	//VIB 1.2:DKW status.
	temp4[0] = arrayhexrcv[360];
	temp4[1] = arrayhexrcv[361];
	a = snprintf(vib12dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.2:DKW status: %s\n", vib12dkw_status);

	//VIB 1.3:DKW status.
	temp4[0] = arrayhexrcv[362];
	temp4[1] = arrayhexrcv[363];
	a = snprintf(vib13dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.3:DKW status: %s\n", vib13dkw_status);

	//VIB 1.4:DKW status.
	temp4[0] = arrayhexrcv[364];
	temp4[1] = arrayhexrcv[365];
	a = snprintf(vib14dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.4:DKW status: %s\n", vib14dkw_status);

	//VIB 1.5:DKW status.
	temp4[0] = arrayhexrcv[366];
	temp4[1] = arrayhexrcv[367];
	a = snprintf(vib15dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.5:DKW status: %s\n", vib15dkw_status);

	//VIB 1.6:DKW status.
	temp4[0] = arrayhexrcv[368];
	temp4[1] = arrayhexrcv[369];
	a = snprintf(vib16dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.6:DKW status: %s\n", vib16dkw_status);

	//VIB 1.7:DKW status.
	temp4[0] = arrayhexrcv[370];
	temp4[1] = arrayhexrcv[371];
	a = snprintf(vib17dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.7:DKW status: %s\n", vib17dkw_status);

	//VIB 1.8:DKW status.
	temp4[0] = arrayhexrcv[372];
	temp4[1] = arrayhexrcv[373];
	a = snprintf(vib18dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 1.8:DKW status: %s\n", vib18dkw_status);

	//VIB 2:DKW status.
	temp4[0] = arrayhexrcv[374];
	temp4[1] = arrayhexrcv[375];
	a = snprintf(vib2dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2:DKW status: %s\n", vib2dkw_status);

	//VIB 2.1:DKW status.
	temp4[0] = arrayhexrcv[376];
	temp4[1] = arrayhexrcv[377];
	a = snprintf(vib21dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.1:DKW status: %s\n", vib21dkw_status);

	//VIB 2.2:DKW status.
	temp4[0] = arrayhexrcv[378];
	temp4[1] = arrayhexrcv[379];
	a = snprintf(vib22dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.2:DKW status: %s\n", vib22dkw_status);

	//VIB 2.3:DKW status.
	temp4[0] = arrayhexrcv[380];
	temp4[1] = arrayhexrcv[381];
	a = snprintf(vib23dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.3:DKW status: %s\n", vib23dkw_status);

	//VIB 2.4:DKW status.
	temp4[0] = arrayhexrcv[382];
	temp4[1] = arrayhexrcv[383];
	a = snprintf(vib24dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.4:DKW status: %s\n", vib24dkw_status);

	//VIB 2.5:DKW status.
	temp4[0] = arrayhexrcv[384];
	temp4[1] = arrayhexrcv[385];
	a = snprintf(vib25dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.5:DKW status: %s\n", vib25dkw_status);

	//VIB 2.6:DKW status.
	temp4[0] = arrayhexrcv[386];
	temp4[1] = arrayhexrcv[387];
	a = snprintf(vib26dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.6:DKW status: %s\n", vib26dkw_status);

	//VIB 2.7:DKW status.
	temp4[0] = arrayhexrcv[388];
	temp4[1] = arrayhexrcv[389];
	a = snprintf(vib27dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.7:DKW status: %s\n", vib27dkw_status);

	//VIB 2.8:DKW status.
	temp4[0] = arrayhexrcv[390];
	temp4[1] = arrayhexrcv[391];
	a = snprintf(vib28dkw_status, 6, "%u", *(unsigned short int *)temp4);
	//printf("VIB 2.8:DKW status: %s\n", vib28dkw_status);

	//**************************************************************************
	//Spectrum status:
	//**************************************************************************
	//VIB 1:v(f) status.
	temp5[0] = arrayhexrcv[412];
	temp5[1] = arrayhexrcv[413];
	a = snprintf(vib1vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1:v(f): %s\n", vib1vf);

	//VIB 1.1:v(f) status.
	temp5[0] = arrayhexrcv[414];
	temp5[1] = arrayhexrcv[415];
	a = snprintf(vib11vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.1:v(f): %s\n", vib11vf);

	//VIB 1.2:v(f) status.
	temp5[0] = arrayhexrcv[416];
	temp5[1] = arrayhexrcv[417];
	a = snprintf(vib12vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.2:v(f): %s\n", vib12vf);

	//VIB 1.3:v(f) status.
	temp5[0] = arrayhexrcv[418];
	temp5[1] = arrayhexrcv[419];
	a = snprintf(vib13vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.3:v(f): %s\n", vib13vf);

	//VIB 1.4:v(f) status.
	temp5[0] = arrayhexrcv[420];
	temp5[1] = arrayhexrcv[421];
	a = snprintf(vib14vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.4:v(f): %s\n", vib14vf);

	//VIB 1.5:v(f) status.
	temp5[0] = arrayhexrcv[422];
	temp5[1] = arrayhexrcv[423];
	a = snprintf(vib15vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.5:v(f): %s\n", vib15vf);

	//VIB 1.6:v(f) status.
	temp5[0] = arrayhexrcv[424];
	temp5[1] = arrayhexrcv[425];
	a = snprintf(vib16vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.6:v(f): %s\n", vib16vf);

	//VIB 1.7:v(f) status.
	temp5[0] = arrayhexrcv[426];
	temp5[1] = arrayhexrcv[427];
	a = snprintf(vib17vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.7:v(f): %s\n", vib17vf);

	//VIB 1.8:v(f) status.
	temp5[0] = arrayhexrcv[428];
	temp5[1] = arrayhexrcv[429];
	a = snprintf(vib18vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.8:v(f): %s\n", vib18vf);

	//VIB 2:v(f) status.
	temp5[0] = arrayhexrcv[430];
	temp5[1] = arrayhexrcv[431];
	a = snprintf(vib2vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2:v(f): %s\n", vib2vf);

	//VIB 2.1:v(f) status.
	temp5[0] = arrayhexrcv[432];
	temp5[1] = arrayhexrcv[433];
	a = snprintf(vib21vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.1:v(f): %s\n", vib21vf);

	//VIB 2.2:v(f) status.
	temp5[0] = arrayhexrcv[434];
	temp5[1] = arrayhexrcv[435];
	a = snprintf(vib22vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.2:v(f): %s\n", vib22vf);

	//VIB 2.3:v(f) status.
	temp5[0] = arrayhexrcv[436];
	temp5[1] = arrayhexrcv[437];
	a = snprintf(vib23vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.3:v(f): %s\n", vib23vf);

	//VIB 2.4:v(f) status.
	temp5[0] = arrayhexrcv[438];
	temp5[1] = arrayhexrcv[439];
	a = snprintf(vib24vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.4:v(f): %s\n", vib24vf);

	//VIB 2.5:v(f) status.
	temp5[0] = arrayhexrcv[440];
	temp5[1] = arrayhexrcv[441];
	a = snprintf(vib25vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.5:v(f): %s\n", vib25vf);

	//VIB 2.6:v(f) status.
	temp5[0] = arrayhexrcv[442];
	temp5[1] = arrayhexrcv[443];
	a = snprintf(vib26vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.6:v(f): %s\n", vib26vf);

	//VIB 2.7:v(f) status.
	temp5[0] = arrayhexrcv[444];
	temp5[1] = arrayhexrcv[445];
	a = snprintf(vib27vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.7:v(f): %s\n", vib27vf);

	//VIB 2.8:v(f) status.
	temp5[0] = arrayhexrcv[446];
	temp5[1] = arrayhexrcv[447];
	a = snprintf(vib28vf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.8:v(f): %s\n", vib28vf);

	//VIB 1:a(f) status.
	temp5[0] = arrayhexrcv[448];
	temp5[1] = arrayhexrcv[449];
	a = snprintf(vib1af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1:a(f): %s\n", vib1af);

	//VIB 1.1:a(f) status.
	temp5[0] = arrayhexrcv[450];
	temp5[1] = arrayhexrcv[451];
	a = snprintf(vib11af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.1:a(f): %s\n", vib11af);

	//VIB 1.2:a(f) status.
	temp5[0] = arrayhexrcv[452];
	temp5[1] = arrayhexrcv[453];
	a = snprintf(vib12af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.2:a(f): %s\n", vib12af);

	//VIB 1.3:a(f) status.
	temp5[0] = arrayhexrcv[454];
	temp5[1] = arrayhexrcv[455];
	a = snprintf(vib13af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.3:a(f): %s\n", vib13af);

	//VIB 1.4:a(f) status.
	temp5[0] = arrayhexrcv[456];
	temp5[1] = arrayhexrcv[457];
	a = snprintf(vib14af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.4:a(f): %s\n", vib14af);

	//VIB 1.5:a(f) status.
	temp5[0] = arrayhexrcv[458];
	temp5[1] = arrayhexrcv[459];
	a = snprintf(vib15af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.5:a(f): %s\n", vib15af);

	//VIB 1.6:a(f) status.
	temp5[0] = arrayhexrcv[460];
	temp5[1] = arrayhexrcv[461];
	a = snprintf(vib16af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.6:a(f): %s\n", vib16af);

	//VIB 1.7:a(f) status.
	temp5[0] = arrayhexrcv[462];
	temp5[1] = arrayhexrcv[463];
	a = snprintf(vib17af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.7:a(f): %s\n", vib17af);

	//VIB 1.8:a(f) status.
	temp5[0] = arrayhexrcv[464];
	temp5[1] = arrayhexrcv[465];
	a = snprintf(vib18af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.8:a(f): %s\n", vib18af);

	//VIB 2:a(f) status.
	temp5[0] = arrayhexrcv[466];
	temp5[1] = arrayhexrcv[467];
	a = snprintf(vib2af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2:a(f): %s\n", vib2af);

	//VIB 2.1:a(f) status.
	temp5[0] = arrayhexrcv[468];
	temp5[1] = arrayhexrcv[469];
	a = snprintf(vib21af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.1:a(f): %s\n", vib21af);

	//VIB 2.2:a(f) status.
	temp5[0] = arrayhexrcv[470];
	temp5[1] = arrayhexrcv[471];
	a = snprintf(vib22af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.2:a(f): %s\n", vib22af);

	//VIB 2.3:a(f) status.
	temp5[0] = arrayhexrcv[472];
	temp5[1] = arrayhexrcv[473];
	a = snprintf(vib23af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.3:a(f): %s\n", vib23af);

	//VIB 2.4:a(f) status.
	temp5[0] = arrayhexrcv[474];
	temp5[1] = arrayhexrcv[475];
	a = snprintf(vib24af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.4:a(f): %s\n", vib24af);

	//VIB 2.5:a(f) status.
	temp5[0] = arrayhexrcv[476];
	temp5[1] = arrayhexrcv[477];
	a = snprintf(vib25af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.5:a(f): %s\n", vib25af);

	//VIB 2.6:a(f) status.
	temp5[0] = arrayhexrcv[478];
	temp5[1] = arrayhexrcv[479];
	a = snprintf(vib26af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.6:a(f): %s\n", vib26af);

	//VIB 2.7:a(f) status.
	temp5[0] = arrayhexrcv[480];
	temp5[1] = arrayhexrcv[481];
	a = snprintf(vib27af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.7:a(f): %s\n", vib27af);

	//VIB 2.8:a(f) status.
	temp5[0] = arrayhexrcv[482];
	temp5[1] = arrayhexrcv[483];
	a = snprintf(vib28af, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.8:a(f): %s\n", vib28af);

	//VIB 1:env(f) status.
	temp5[0] = arrayhexrcv[484];
	temp5[1] = arrayhexrcv[485];
	a = snprintf(vib1envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1:env(f): %s\n", vib1envf);

	//VIB 1.1:env(f) status.
	temp5[0] = arrayhexrcv[486];
	temp5[1] = arrayhexrcv[487];
	a = snprintf(vib11envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.1:env(f): %s\n", vib11envf);

	//VIB 1.2:env(f) status.
	temp5[0] = arrayhexrcv[488];
	temp5[1] = arrayhexrcv[489];
	a = snprintf(vib12envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.2:env(f): %s\n", vib12envf);

	//VIB 1.3:env(f) status.
	temp5[0] = arrayhexrcv[490];
	temp5[1] = arrayhexrcv[491];
	a = snprintf(vib13envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.3:env(f): %s\n", vib13envf);

	//VIB 1.4:env(f) status.
	temp5[0] = arrayhexrcv[492];
	temp5[1] = arrayhexrcv[493];
	a = snprintf(vib14envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.4:env(f): %s\n", vib14envf);

	//VIB 1.5:env(f) status.
	temp5[0] = arrayhexrcv[494];
	temp5[1] = arrayhexrcv[495];
	a = snprintf(vib15envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.5:env(f): %s\n", vib15envf);

	//VIB 1.6:env(f) status.
	temp5[0] = arrayhexrcv[496];
	temp5[1] = arrayhexrcv[497];
	a = snprintf(vib16envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.6:env(f): %s\n", vib16envf);

	//VIB 1.7:env(f) status.
	temp5[0] = arrayhexrcv[498];
	temp5[1] = arrayhexrcv[499];
	a = snprintf(vib17envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.7:env(f): %s\n", vib17envf);

	//VIB 1.8:env(f) status.
	temp5[0] = arrayhexrcv[500];
	temp5[1] = arrayhexrcv[501];
	a = snprintf(vib18envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 1.8:env(f): %s\n", vib18envf);

	//VIB 2:env(f) status.
	temp5[0] = arrayhexrcv[502];
	temp5[1] = arrayhexrcv[503];
	a = snprintf(vib2envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2:env(f): %s\n", vib2envf);

	//VIB 2.1:env(f) status.
	temp5[0] = arrayhexrcv[504];
	temp5[1] = arrayhexrcv[505];
	a = snprintf(vib21envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.1:env(f): %s\n", vib21envf);

	//VIB 2.2:env(f) status.
	temp5[0] = arrayhexrcv[506];
	temp5[1] = arrayhexrcv[507];
	a = snprintf(vib22envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.2:env(f): %s\n", vib22envf);

	//VIB 2.3:env(f) status.
	temp5[0] = arrayhexrcv[508];
	temp5[1] = arrayhexrcv[509];
	a = snprintf(vib23envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.3:env(f): %s\n", vib23envf);

	//VIB 2.4:env(f) status.
	temp5[0] = arrayhexrcv[510];
	temp5[1] = arrayhexrcv[511];
	a = snprintf(vib24envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.4:env(f): %s\n", vib24envf);

	//VIB 2.5:env(f) status.
	temp5[0] = arrayhexrcv[512];
	temp5[1] = arrayhexrcv[513];
	a = snprintf(vib25envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.5:env(f): %s\n", vib25envf);

	//VIB 2.6:env(f) status.
	temp5[0] = arrayhexrcv[514];
	temp5[1] = arrayhexrcv[515];
	a = snprintf(vib26envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.6:env(f): %s\n", vib26envf);

	//VIB 2.7:env(f) status.
	temp5[0] = arrayhexrcv[516];
	temp5[1] = arrayhexrcv[517];
	a = snprintf(vib27envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.7:env(f): %s\n", vib27envf);

	//VIB 2.8:env(f) status.
	temp5[0] = arrayhexrcv[518];
	temp5[1] = arrayhexrcv[519];
	a = snprintf(vib28envf, 6, "%u", *(unsigned short int *)temp5);
	//printf("VIB 2.8:env(f): %s\n", vib28envf);

	//**************************************************************************
	//End code:
	//**************************************************************************
	//End code.
	temp6[0] = arrayhexrcv[540];
	temp6[1] = arrayhexrcv[541];
	temp6[2] = arrayhexrcv[542];
	temp6[3] = arrayhexrcv[543];
	a = snprintf(endcode, 9, "%02X", *(unsigned int *)temp6);
	//printf("End code en hexadecimal: %s\n", endcode);

	//**************************************************************************
	//Fin conversión de datos hexadecimales a los valores reales.
	//**************************************************************************

	//**************************************************************************
	//Armado del archivo JSON a ser devuelto por la función.
	//**************************************************************************
	//Reservamos memoria para alojar el contenido convertido a JSON.
	arrayjson = (char *)malloc(	3 + \
								strlen(label0) +
								5 + \
								strlen(label000) + \
								4 + \
								strlen(timestampextrcv) + \
								6 + \
								strlen(label001) + \
								3 + \
								strlen(timestamp) + \
								5 + \
								strlen(label002) + \
								3 + \
								strlen(userdatalenght) + \
								5 + \
								strlen(label003) + \
								4 + \
								strlen(indextelegram) + \
								6 + \
								strlen(label1) + \
								5 + \
								strlen(label100) + \
								4 + \
								strlen(operatingmode) + \
								6 + \
								strlen(label101) + \
								3 + \
								strlen(statusledgreen) + \
								6 + \
								strlen(label102) + \
								3 + \
								strlen(statusledyellow) + \
								6 + \
								strlen(label103) + \
								4 + \
								strlen(statusledred) + \
								6 + \
								strlen(label104) + \
								3 + \
								strlen(activeprocessalarms) + \
								6 + \
								strlen(label105) + \
								4 + \
								strlen(activesystemalarms) + \
								6 + \
								strlen(label106) + \
								3 + \
								strlen(activeprocesswarnings) + \
								6 + \
								strlen(label107) + \
								3 + \
								strlen(activesystemwarnings) + \
								6 + \
								strlen(label108) + \
								2 + \
								strlen(processmessagestobeack) + \
								6 + \
								strlen(label109) + \
								2 + \
								strlen(systemmessagestobeack) + \
								7 + \
								strlen(label2) + \
								5 + \
								strlen(label200) + \
								4 + \
								strlen(speed) + \
								5 + \
								strlen(label201) + \
								4 + \
								strlen(oprhours) + \
								5 + \
								strlen(label202) + \
								5 + \
								strlen(ai1) + \
								5 + \
								strlen(label203) + \
								5 + \
								strlen(ai2) + \
								5 + \
								strlen(label204) + \
								4 + \
								strlen(temp11) + \
								5 + \
								strlen(label205) + \
								4 + \
								strlen(temp12) + \
								5 + \
								strlen(label206) + \
								4 + \
								strlen(temp13) + \
								5 + \
								strlen(label207) + \
								4 + \
								strlen(temp21) + \
								5 + \
								strlen(label208) + \
								4 + \
								strlen(temp22) + \
								5 + \
								strlen(label209) + \
								4 + \
								strlen(temp23) + \
								5 + \
								strlen(label210) + \
								4 + \
								strlen(vib1rms) + \
								5 + \
								strlen(label211) + \
								4 + \
								strlen(vib11rms) + \
								5 + \
								strlen(label212) + \
								4 + \
								strlen(vib12rms) + \
								5 + \
								strlen(label213) + \
								4 + \
								strlen(vib13rms) + \
								5 + \
								strlen(label214) + \
								4 + \
								strlen(vib14rms) + \
								5 + \
								strlen(label215) + \
								4 + \
								strlen(vib15rms) + \
								5 + \
								strlen(label216) + \
								4 + \
								strlen(vib16rms) + \
								5 + \
								strlen(label217) + \
								4 + \
								strlen(vib17rms) + \
								5 + \
								strlen(label218) + \
								4 + \
								strlen(vib18rms) + \
								5 + \
								strlen(label219) + \
								4 + \
								strlen(vib2rms) + \
								5 + \
								strlen(label220) + \
								4 + \
								strlen(vib21rms) + \
								5 + \
								strlen(label221) + \
								4 + \
								strlen(vib22rms) + \
								5 + \
								strlen(label222) + \
								4 + \
								strlen(vib23rms) + \
								5 + \
								strlen(label223) + \
								4 + \
								strlen(vib24rms) + \
								5 + \
								strlen(label224) + \
								4 + \
								strlen(vib25rms) + \
								5 + \
								strlen(label225) + \
								4 + \
								strlen(vib26rms) + \
								5 + \
								strlen(label226) + \
								4 + \
								strlen(vib27rms) + \
								5 + \
								strlen(label227) + \
								4 + \
								strlen(vib28rms) + \
								5 + \
								strlen(label228) + \
								4 + \
								strlen(vib1dkw) + \
								5 + \
								strlen(label229) + \
								4 + \
								strlen(vib11dkw) + \
								5 + \
								strlen(label230) + \
								4 + \
								strlen(vib12dkw) + \
								5 + \
								strlen(label231) + \
								4 + \
								strlen(vib13dkw) + \
								5 + \
								strlen(label232) + \
								4 + \
								strlen(vib14dkw) + \
								5 + \
								strlen(label233) + \
								4 + \
								strlen(vib15dkw) + \
								5 + \
								strlen(label234) + \
								4 + \
								strlen(vib16dkw) + \
								5 + \
								strlen(label235) + \
								4 + \
								strlen(vib17dkw) + \
								5 + \
								strlen(label236) + \
								4 + \
								strlen(vib18dkw) + \
								5 + \
								strlen(label237) + \
								4 + \
								strlen(vib2dkw) + \
								5 + \
								strlen(label238) + \
								4 + \
								strlen(vib21dkw) + \
								5 + \
								strlen(label239) + \
								4 + \
								strlen(vib22dkw) + \
								5 + \
								strlen(label240) + \
								4 + \
								strlen(vib23dkw) + \
								5 + \
								strlen(label241) + \
								4 + \
								strlen(vib24dkw) + \
								5 + \
								strlen(label242) + \
								4 + \
								strlen(vib25dkw) + \
								5 + \
								strlen(label243) + \
								4 + \
								strlen(vib26dkw) + \
								5 + \
								strlen(label244) + \
								4 + \
								strlen(vib27dkw) + \
								5 + \
								strlen(label245) + \
								4 + \
								strlen(vib28dkw) + \
								6 + \
								strlen(label3) + \
								5 + \
								strlen(label300) + \
								4 + \
								strlen(speed_status) + \
								5 + \
								strlen(label301) + \
								4 + \
								strlen(oprhours_status) + \
								5 + \
								strlen(label302) + \
								5 + \
								strlen(ai1_status) + \
								5 + \
								strlen(label303) + \
								5 + \
								strlen(ai2_status) + \
								5 + \
								strlen(label304) + \
								4 + \
								strlen(temp11_status) + \
								5 + \
								strlen(label305) + \
								4 + \
								strlen(temp12_status) + \
								5 + \
								strlen(label306) + \
								4 + \
								strlen(temp13_status) + \
								5 + \
								strlen(label307) + \
								4 + \
								strlen(temp21_status) + \
								5 + \
								strlen(label308) + \
								4 + \
								strlen(temp22_status) + \
								5 + \
								strlen(label309) + \
								4 + \
								strlen(temp23_status) + \
								5 + \
								strlen(label310) + \
								4 + \
								strlen(vib1rms_status) + \
								5 + \
								strlen(label311) + \
								4 + \
								strlen(vib11rms_status) + \
								5 + \
								strlen(label312) + \
								4 + \
								strlen(vib12rms_status) + \
								5 + \
								strlen(label313) + \
								4 + \
								strlen(vib13rms_status) + \
								5 + \
								strlen(label314) + \
								4 + \
								strlen(vib14rms_status) + \
								5 + \
								strlen(label315) + \
								4 + \
								strlen(vib15rms_status) + \
								5 + \
								strlen(label316) + \
								4 + \
								strlen(vib16rms_status) + \
								5 + \
								strlen(label317) + \
								4 + \
								strlen(vib17rms_status) + \
								5 + \
								strlen(label318) + \
								4 + \
								strlen(vib18rms_status) + \
								5 + \
								strlen(label319) + \
								4 + \
								strlen(vib2rms_status) + \
								5 + \
								strlen(label320) + \
								4 + \
								strlen(vib21rms_status) + \
								5 + \
								strlen(label321) + \
								4 + \
								strlen(vib22rms_status) + \
								5 + \
								strlen(label322) + \
								4 + \
								strlen(vib23rms_status) + \
								5 + \
								strlen(label323) + \
								4 + \
								strlen(vib24rms_status) + \
								5 + \
								strlen(label324) + \
								4 + \
								strlen(vib25rms_status) + \
								5 + \
								strlen(label325) + \
								4 + \
								strlen(vib26rms_status) + \
								5 + \
								strlen(label326) + \
								4 + \
								strlen(vib27rms_status) + \
								5 + \
								strlen(label327) + \
								4 + \
								strlen(vib28rms_status) + \
								5 + \
								strlen(label328) + \
								4 + \
								strlen(vib1dkw_status) + \
								5 + \
								strlen(label329) + \
								4 + \
								strlen(vib11dkw_status) + \
								5 + \
								strlen(label330) + \
								4 + \
								strlen(vib12dkw_status) + \
								5 + \
								strlen(label331) + \
								4 + \
								strlen(vib13dkw_status) + \
								5 + \
								strlen(label332) + \
								4 + \
								strlen(vib14dkw_status) + \
								5 + \
								strlen(label333) + \
								4 + \
								strlen(vib15dkw_status) + \
								5 + \
								strlen(label334) + \
								4 + \
								strlen(vib16dkw_status) + \
								5 + \
								strlen(label335) + \
								4 + \
								strlen(vib17dkw_status) + \
								5 + \
								strlen(label336) + \
								4 + \
								strlen(vib18dkw_status) + \
								5 + \
								strlen(label337) + \
								4 + \
								strlen(vib2dkw_status) + \
								5 + \
								strlen(label338) + \
								4 + \
								strlen(vib21dkw_status) + \
								5 + \
								strlen(label339) + \
								4 + \
								strlen(vib22dkw_status) + \
								5 + \
								strlen(label340) + \
								4 + \
								strlen(vib23dkw_status) + \
								5 + \
								strlen(label341) + \
								4 + \
								strlen(vib24dkw_status) + \
								5 + \
								strlen(label342) + \
								4 + \
								strlen(vib25dkw_status) + \
								5 + \
								strlen(label343) + \
								4 + \
								strlen(vib26dkw_status) + \
								5 + \
								strlen(label344) + \
								4 + \
								strlen(vib27dkw_status) + \
								5 + \
								strlen(label345) + \
								4 + \
								strlen(vib28dkw_status) + \
								6 + \
								strlen(label4) + \
								5 + \
								strlen(label400) + \
								4 + \
								strlen(vib1vf) + \
								5 + \
								strlen(label401) + \
								4 + \
								strlen(vib11vf) + \
								5 + \
								strlen(label402) + \
								4 + \
								strlen(vib12vf) + \
								5 + \
								strlen(label403) + \
								4 + \
								strlen(vib13vf) + \
								5 + \
								strlen(label404) + \
								4 + \
								strlen(vib14vf) + \
								5 + \
								strlen(label405) + \
								4 + \
								strlen(vib15vf) + \
								5 + \
								strlen(label406) + \
								4 + \
								strlen(vib16vf) + \
								5 + \
								strlen(label407) + \
								4 + \
								strlen(vib17vf) + \
								5 + \
								strlen(label408) + \
								4 + \
								strlen(vib18vf) + \
								5 + \
								strlen(label409) + \
								4 + \
								strlen(vib2vf) + \
								5 + \
								strlen(label410) + \
								4 + \
								strlen(vib21vf) + \
								5 + \
								strlen(label411) + \
								4 + \
								strlen(vib22vf) + \
								5 + \
								strlen(label412) + \
								4 + \
								strlen(vib23vf) + \
								5 + \
								strlen(label413) + \
								4 + \
								strlen(vib24vf) + \
								5 + \
								strlen(label414) + \
								4 + \
								strlen(vib25vf) + \
								5 + \
								strlen(label415) + \
								4 + \
								strlen(vib26vf) + \
								5 + \
								strlen(label416) + \
								4 + \
								strlen(vib27vf) + \
								5 + \
								strlen(label417) + \
								4 + \
								strlen(vib28vf) + \
								5 + \
								strlen(label418) + \
								4 + \
								strlen(vib1af) + \
								5 + \
								strlen(label419) + \
								4 + \
								strlen(vib11af) + \
								5 + \
								strlen(label420) + \
								4 + \
								strlen(vib12af) + \
								5 + \
								strlen(label421) + \
								4 + \
								strlen(vib13af) + \
								5 + \
								strlen(label422) + \
								4 + \
								strlen(vib14af) + \
								5 + \
								strlen(label423) + \
								4 + \
								strlen(vib15af) + \
								5 + \
								strlen(label424) + \
								4 + \
								strlen(vib16af) + \
								5 + \
								strlen(label425) + \
								4 + \
								strlen(vib17af) + \
								5 + \
								strlen(label426) + \
								4 + \
								strlen(vib18af) + \
								5 + \
								strlen(label427) + \
								4 + \
								strlen(vib2af) + \
								5 + \
								strlen(label428) + \
								4 + \
								strlen(vib21af) + \
								5 + \
								strlen(label429) + \
								4 + \
								strlen(vib22af) + \
								5 + \
								strlen(label430) + \
								4 + \
								strlen(vib23af) + \
								5 + \
								strlen(label431) + \
								4 + \
								strlen(vib24af) + \
								5 + \
								strlen(label432) + \
								4 + \
								strlen(vib25af) + \
								5 + \
								strlen(label433) + \
								4 + \
								strlen(vib26af) + \
								5 + \
								strlen(label434) + \
								4 + \
								strlen(vib27af) + \
								5 + \
								strlen(label435) + \
								4 + \
								strlen(vib28af) + \
								5 + \
								strlen(label436) + \
								4 + \
								strlen(vib1envf) + \
								5 + \
								strlen(label437) + \
								3 + \
								strlen(vib11envf) + \
								5 + \
								strlen(label438) + \
								3 + \
								strlen(vib12envf) + \
								5 + \
								strlen(label439) + \
								3 + \
								strlen(vib13envf) + \
								5 + \
								strlen(label440) + \
								3 + \
								strlen(vib14envf) + \
								5 + \
								strlen(label441) + \
								3 + \
								strlen(vib15envf) + \
								5 + \
								strlen(label442) + \
								3 + \
								strlen(vib16envf) + \
								5 + \
								strlen(label443) + \
								3 + \
								strlen(vib17envf) + \
								5 + \
								strlen(label444) + \
								3 + \
								strlen(vib18envf) + \
								5 + \
								strlen(label445) + \
								4 + \
								strlen(vib2envf) + \
								5 + \
								strlen(label446) + \
								3 + \
								strlen(vib21envf) + \
								5 + \
								strlen(label447) + \
								3 + \
								strlen(vib22envf) + \
								5 + \
								strlen(label448) + \
								3 + \
								strlen(vib23envf) + \
								5 + \
								strlen(label449) + \
								3 + \
								strlen(vib24envf) + \
								5 + \
								strlen(label450) + \
								3 + \
								strlen(vib25envf) + \
								5 + \
								strlen(label451) + \
								3 + \
								strlen(vib26envf) + \
								5 + \
								strlen(label452) + \
								3 + \
								strlen(vib27envf) + \
								5 + \
								strlen(label453) + \
								3 + \
								strlen(vib28envf) + \
								6 + \
								strlen(label5) + \
								5 + \
								strlen(endcode) + \
								4 \
							);

	//printf("Tamaño malloc de arrayjson: %lu\n", sizeof(arrayjson));
	//Generamos el string completo con las variables convertidas a JSON.
	strcpy(arrayjson, llavea);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, label0);
	strcat(arrayjson, llavea);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label000);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, timestampextrcv);
	strcat(arrayjson, comilla);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label001);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, timestamp);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label002);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, userdatalenght);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label003);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, indextelegram);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, llavec);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, label1);
	strcat(arrayjson, llavea);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label100);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, operatingmode);
	strcat(arrayjson, comilla);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label101);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, statusledgreen);
	strcat(arrayjson, comilla);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label102);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, statusledyellow);
	strcat(arrayjson, comilla);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label103);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, statusledred);
	strcat(arrayjson, comilla);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label104);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, activeprocessalarms);
	strcat(arrayjson, comilla);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label105);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, activesystemalarms);
	strcat(arrayjson, comilla);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label106);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, activeprocesswarnings);
	strcat(arrayjson, comilla);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label107);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, activesystemwarnings);
	strcat(arrayjson, comilla);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label108);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, processmessagestobeack);
	strcat(arrayjson, comilla);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label109);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, systemmessagestobeack);
	strcat(arrayjson, comilla);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, llavec);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, label2);
	strcat(arrayjson, llavea);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label200);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, speed);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label201);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, oprhours);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label202);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, ai1);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label203);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, ai2);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label204);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp11);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label205);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp12);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label206);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp13);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label207);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp21);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label208);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp22);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label209);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp23);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label210);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib1rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label211);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib11rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label212);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib12rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label213);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib13rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label214);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib14rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label215);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib15rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label216);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib16rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label217);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib17rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label218);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib18rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label219);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib2rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label220);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib21rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label221);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib22rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label222);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib23rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label223);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib24rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label224);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib25rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label225);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib26rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label226);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib27rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label227);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib28rms);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label228);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib1dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label229);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib11dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label230);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib12dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label231);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib13dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label232);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib14dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label233);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib15dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label234);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib16dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label235);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib17dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label236);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib18dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label237);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib2dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label238);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib21dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label239);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib22dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label240);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib23dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label241);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib24dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label242);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib25dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label243);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib26dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label244);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib27dkw);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label245);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib28dkw);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, llavec);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, label3);
	strcat(arrayjson, llavea);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label300);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, speed_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label301);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, oprhours_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label302);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, ai1_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label303);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, ai2_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label304);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp11_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label305);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp12_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label306);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp13_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label307);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp21_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label308);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp22_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label309);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, temp23_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label310);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib1rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label311);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib11rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label312);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib12rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label313);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib13rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label314);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib14rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label315);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib15rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label316);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib16rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label317);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib17rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label318);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib18rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label319);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib2rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label320);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib21rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label321);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib22rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label322);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib23rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label323);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib24rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label324);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib25rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label325);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib26rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label326);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib27rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label327);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib28rms_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label328);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib1dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label329);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib11dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label330);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib12dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label331);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib13dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label332);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib14dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label333);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib15dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label334);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib16dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label335);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib17dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label336);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib18dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label337);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib2dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label338);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib21dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label339);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib22dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label340);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib23dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label341);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib24dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label342);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib25dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label343);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib26dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label344);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib27dkw_status);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label345);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib28dkw_status);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, llavec);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, label4);
	strcat(arrayjson, llavea);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label400);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib1vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label401);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib11vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label402);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib12vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label403);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib13vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label404);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib14vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label405);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib15vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label406);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib16vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label407);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib17vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label408);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib18vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label409);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib2vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label410);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib21vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label411);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib22vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label412);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib23vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label413);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib24vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label414);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib25vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label415);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib26vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label416);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib27vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label417);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib28vf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label418);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib1af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label419);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib11af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label420);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib12af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label421);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib13af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label422);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib14af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label423);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib15af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label424);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib16af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label425);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib17af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label426);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib18af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label427);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib2af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label428);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib21af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label429);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib22af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label430);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib23af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label431);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib24af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label432);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib25af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label433);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib26af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label434);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib27af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label435);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib28af);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label436);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib1envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label437);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib11envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label438);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib12envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label439);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib13envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label440);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib14envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label441);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib15envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label442);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib16envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label443);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib17envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label444);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib18envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label445);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib2envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label446);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib21envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label447);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib22envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label448);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib23envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label449);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib24envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label450);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib25envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label451);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib26envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label452);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib27envf);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, label453);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, vib28envf);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, llavec);
	strcat(arrayjson, coma);
	strcat(arrayjson, newline);
	strcat(arrayjson, tab);
	strcat(arrayjson, label5);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, tab);
	strcat(arrayjson, comilla);
	strcat(arrayjson, endcode);
	strcat(arrayjson, comilla);
	strcat(arrayjson, newline);
	strcat(arrayjson, llavec);
	strcat(arrayjson, nullchar);

	//Devuelvo el tamaño del array.
	sizeofarrayjson = strlen(arrayjson);
	//printf("La longitud de arrayjson es: %i\n", sizeofarrayjson);


	//**************************************************************************
	//Verificación y devolución del string JSON.
	//**************************************************************************
//	printf("Tamaño del array recibido: %d\n", sizeofarrayhexrcv);
//	printf("Array recibido: ");
//	for(i=0;i<544;i++)
//		printf("%02X", arrayhexrcv[i] & 0xFF);
//	printf("\n\n");

//PARA PRUEBAS:
//	printf("Contenido del array JSON en Hex2Json: %i\n", sizeofarrayjsonrcv);
//	printf("Dirección del array JSON en Hex2Json: %p\n", &sizeofarrayjson);
	//printf("La dirección en HexAJson de arrayjson es: %p\n", &arrayjson);
	return arrayjson;
	//return arrayjson;
}
