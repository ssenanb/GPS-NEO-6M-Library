/*
 * GPS_NEO_6M.h
 *
 *  Created on: Sep 30, 2025
 *      Author: sssen
 */

#ifndef INC_GPS_NEO_6M_H_
#define INC_GPS_NEO_6M_H_

#include "main.h"

typedef struct{
	char utc_time[11];
	double latitude;
	char latitude_dir;
	double longitude;
	char longitude_dir;
	int fix_quality;
	int satellites;
	float HDOP;
	float altitude;
	char altitude_unit;
	float geoid_seperation;
	char geoid_seperation_unit;
	char DGPS;
	char DGPS_ID;
	char checksum;
}GPGGA_Data;

typedef struct{
	char utc_time[11];
	char status;
	double latitude;
	char latitude_dir;
	double longitude;
	char longitude_dir;
	float speed_knots;
	float track_angle;
	char date[7];
	float magnetic_variation;
	char magnetic_variation_dir;
	char checksum;
}GPRMC_Data;

typedef enum{
	GPGGA_SUCCESS = 1,
	GPGGA_FAIL = 0,
}GPGGA_Status;

typedef enum{
	GPRMC_SUCCESS = 1,
	GPRMC_FAIL = 0,
}GPRMC_Status;

GPGGA_Status GPS_GPGGA_Data(GPGGA_Data *gpgga_data);
//GPRMC_Status GPS_GPRMC_Data(GPRMC_Data *gprmc_data);
#endif /* INC_GPS_NEO_6M_H_ */
