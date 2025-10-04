/*
 * GPS_NEO_6M.c
 *
 *  Created on: Sep 30, 2025
 *      Author: sssen
 */

#include "GPS_NEO_6M.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#define BUFFER_SIZE 128

extern UART_HandleTypeDef huart1;


GPGGA_Status GPS_GPGGA_Data(GPGGA_Data *gpgga_data){
	static uint8_t gps_buffer[BUFFER_SIZE];
	static uint8_t indx = 0;
	uint8_t data;

	 if(HAL_UART_Receive(&huart1, &data, 1, 100) == HAL_OK) {
		 	gps_buffer[indx++] = data;

		    if (data == '\n') {
 	           gps_buffer[indx] = '\0';
 	           indx = 0;

 	           if(strncmp("$GPGGA", gps_buffer, 6) == 0){
 		           const char *token = strtok(gps_buffer, ",");
 	        	   int field = 0;

		 	       while(token != NULL){
		 	       	   switch(field){
		 	       	   case 1 : strncpy(gpgga_data-> utc_time, token, 10); break;
		 	       	   case 2 : gpgga_data->latitude = atof(token); break;
		 	       	   case 3 : gpgga_data->latitude_dir = token[0]; break;
		 	       	   case 4 : gpgga_data->longitude = atof(token); break;
		 	       	   case 5 : gpgga_data->longitude_dir = token[0]; break;
		 	       	   case 6 : gpgga_data->fix_quality = atoi(token); break;
		         	   case 7 : gpgga_data->satellites = atoi(token); break;
		        	   case 8 : gpgga_data->HDOP = atof(token); break;
	 	        	   case 9 : gpgga_data->altitude = atof(token); break;
	 	        	   case 10 :gpgga_data->altitude_unit = token[0]; break;
		 	           case 11 :gpgga_data->geoid_seperation = atof(token); break;
		 	       	   case 12 :gpgga_data->geoid_seperation_unit = token[0]; break;
		 	       	   case 13 :gpgga_data->DGPS = token[0]; break;
		 	       	   case 14 :gpgga_data->DGPS_ID = token[0]; break;
		 	       	   case 15 :gpgga_data->checksum = token[0]; break;
		 	    	   }

		 	        field++;
		 	     	token = strtok(NULL,",");

		 	        }
		 	        field = 0;
		 	     }
	        }
		    return GPGGA_SUCCESS;
	 }
	 return GPGGA_FAIL;
}
/*
GPRMC_Status GPS_GPRMC_Data(GPRMC_Data *gprmc_data){
	static uint8_t gps_buffer[BUFFER_SIZE];
	static uint8_t indx = 0;
	uint8_t data;

	 if(HAL_UART_Receive(&huart1, &data, 1, 100) == HAL_OK) {
		 	gps_buffer[indx++] = data;

		    if (data == '\n') {
 	           gps_buffer[indx] = '\0';
 	           indx = 0;

 	           if(strncmp("$GPRMC", gps_buffer, 6) == 0){
 		           const char *token = strtok(gps_buffer, ",");
 	        	   int field = 0;

		 	       while(token != NULL){
		 	       	   switch(field){
		 	       	   case 1 : strncpy(gprmc_data-> utc_time, token, 10); break;
		 	       	   case 2 : gprmc_data->status = token[0]; break;
		 	       	   case 3 : gprmc_data->latitude = atof(token); break;
		 	       	   case 4 : gprmc_data->latitude_dir = token[0]; break;
		 	       	   case 5 : gprmc_data->longitude = atof(token); break;
		 	       	   case 6 : gprmc_data->longitude_dir = token[0]; break;
		         	   case 7 : gprmc_data->speed_knots = atof(token); break;
		        	   case 8 : gprmc_data->track_angle = atof(token); break;
	 	        	   case 9 : strncpy(gprmc_data-> date, token, 6); break;
	 	        	   case 10 :gprmc_data->magnetic_variation = atof(token); break;
		 	           case 11 :gprmc_data->magnetic_variation_dir = token[0]; break;
		 	       	   case 12 :gprmc_data->checksum = token[0]; break;
		 	    	   }
		 	        field++;
		 	     	token = strtok(NULL,",");

		 	        }
		 	        field = 0;
		 	     }
	        }
		    return GPRMC_SUCCESS;
	 }
	 return GPRMC_FAIL;
}
*/
