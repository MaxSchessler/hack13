/**
 * Author: Max Schessler
 * Date: 2024-12-2
 * 
 * This file contains method definitions for Airports
 */


#include <stdlib.h>
#include <stdio.h>
#include "airport.h"

/**
 * Author Max Schessler
 * Date 2024-11-15
 * 
 * This file holds my Airport Lib Functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "airport.h"


Airport* createAirport(const char* gpsId,
                       const char* type,
                       const char* name,
                       double latitude,
                       double longitude,
                       int elevationFeet,
                       const char* city,
                       const char* countryAbbrv) {

    if (gpsId == NULL) {
        fprintf(stderr, "ERROR invalid input (gpsID)\n");
        return NULL;
    }

    if (type == NULL) {
        fprintf(stderr, "ERROR invalid input (type) \n");
        return NULL;
    }

    if (name == NULL) {
        fprintf(stderr, "ERROR invalid input (name) \n");
        return NULL;
    }

    if (city == NULL) {
        fprintf(stderr, "ERROR invalid input (city) \n");
        return NULL;
    }

    if (countryAbbrv == NULL) {
        fprintf(stderr, "ERROR invalid input (countryAbbrv) \n");
        return NULL;
    }

    // validate latitude and longitude 
    if (latitude < -90 || latitude > 90) 
    {
        printf("Latitude value must be between -90 and 90 degrees.\n");
        return NULL;
    }
    if (longitude < -180 || longitude > 180) 
    {
        printf("Longitude value must be between -180 and 180 degrees.\n");
        return NULL;
    }

    Airport *airport = (Airport *) malloc(sizeof(Airport));

    initAirport(airport, gpsId, type, name, latitude, longitude, elevationFeet, city, countryAbbrv);

    return airport;
}


void initAirport(Airport* airport,
                 const char* gpsId,
                 const char* type,
                 const char* name,
                 double latitude,
                 double longitude,
                 int elevationFeet,
                 const char* city,
                 const char* countryAbbrv)
{
    if (airport == NULL) {
        fprintf(stderr, "ERROR invalid input (airport) \n");
        return;
    }

    if (gpsId == NULL) {
        fprintf(stderr, "ERROR invalid input (gpsID)\n");
        return;
    }

    if (type == NULL) {
        fprintf(stderr, "ERROR invalid input (type) \n");
        return;
    }

    if (name == NULL) {
        fprintf(stderr, "ERROR invalid input (name) \n");
        return;
    }

    if (city == NULL) {
        fprintf(stderr, "ERROR invalid input (city) \n");
        return;
    }

    if (countryAbbrv == NULL) {
        fprintf(stderr, "ERROR invalid input (countryAbbrv) \n");
        return;
    }

    // validate latitude and longitude 
    if (latitude < -90 || latitude > 90) 
    {
        printf("Latitude value must be between -90 and 90 degrees.\n");
        return;
    }
    if (longitude < -180 || longitude > 180) 
    {
        printf("Longitude value must be between -180 and 180 degrees.\n");
        return;
    }

    airport->gpsId = (char *) malloc(sizeof(char *) * strlen(gpsId));
    strcpy(airport->gpsId, gpsId);

    airport->type = (char *) malloc(sizeof(char *) * strlen(type));
    strcpy(airport->type, type);

    airport->name = (char *) malloc(sizeof(char *) * strlen(name));
    strcpy(airport->name, name);

    airport->city = (char *) malloc(sizeof(char *) * strlen(city));
    strcpy(airport->city, city);

    airport->countryAbbrv = (char *) malloc(sizeof(char *) * strlen(countryAbbrv));
    strcpy(airport->countryAbbrv, countryAbbrv);

    airport->latitude = latitude;
    airport->longitude = longitude;
    airport->elevationFeet = elevationFeet;
}


double getEstimatedTravelTime(const Airport* stops, int size, double aveKmsPerHour, double aveLayoverTimeHrs)
{
    // Data validation 
    if (size <= 0) {
        fprintf(stderr, "ERROR: Invalid size\n");
        return -1;
    }
    if (stops == NULL) {
        fprintf(stderr, "ERROR: Stops array is NULL\n");
        return -1;
    }
    if (aveKmsPerHour <= 0) {
        fprintf(stderr, "ERROR: Invalid average speed (must be > 0)\n");
        return -1;
    }
    if (aveLayoverTimeHrs < 0) {
        fprintf(stderr, "ERROR: Invalid layover time (must be >= 0)\n");
        return -1;
    }

   
    double travelTime = 0;
    double airDistance;
    // iterate from first to second to last stop has no layover time
    for (int i = 0; i < size - 1; i++) {
        // get air distance form current stop to next stop, if error return -1
        airDistance = getAirDistance(&stops[i], &stops[i + 1]);
        if (airDistance < 0) {
            return -1;
        }
        // compute the travel time by dividing distance / speed 
        travelTime += airDistance / aveKmsPerHour;
        // if the current stop is not the second to last stop add the layover time
        // second to last because the last stop is the destination and not included in the loop
        if (i < size - 2) {
            travelTime += aveLayoverTimeHrs;
        }
    }

    return travelTime;
}

double degreesToRadians(double degree) {
    return degree * M_PI / 180;
}


double getAirDistance(const Airport* origin, const Airport* destination)
{
    if (origin == NULL || destination == NULL) {
        fprintf(stderr, "ERROR, invalid inputs\n");
        return -1;
    }
    
    double lat1 = origin->latitude;
    double lon1 = origin->longitude;
    double lat2 = destination->latitude;
    double lon2 = destination->longitude;

    if (lat1 < -90 || lat1 > 90) 
    {
        printf("Origin Latitude value must be between -90 and 90 degrees.\n");
        return -1;
    }
    if (lon1 < -180 || lon1 > 180) 
    {
        printf("Origin Longitude value must be between -180 and 180 degrees.\n");
        return -1;
    }
    if (lat2 < -90 || lat2 > 90) 
    {
        printf("Destination Latitude value must be between -90 and 90 degrees.\n");
        return -1;
    }
    if (lon2 < -180 || lon2 > 180) 
    {
        printf("Destination Longitude value must be between -180 and 180 degrees.\n");
        return -1;
    }

    // Convert degrees to radians
    lat1 = degreesToRadians(lat1);
    lon1 = degreesToRadians(lon1);
    lat2 = degreesToRadians(lat2);
    lon2 = degreesToRadians(lon2);

    // calculate the distance using the haversine formula
    const double RADIUS = 6371;
    return acos(sin(lat1)*sin(lat2) + cos(lat1)*cos(lat2)*cos(lon1-lon2)) * RADIUS;
}

void freeAirport(Airport *airport) {
    if (airport != NULL) {
        free(airport->gpsId);
        free(airport->type);
        free(airport->name);
        free(airport->city);
        free(airport->countryAbbrv);
        free(airport);
    }
}

void generateReports(Airport *airports, int n) {

  char* airportString;

  printf("Airports (original): \n");
  printf("==============================\n");
  printAirports(airports, n);

  printf("\nAirports By GPS ID: \n");
  printf("==============================\n");
  qsort(airports, n, sizeof(Airport), cmpByGPSId);
  printAirports(airports, n);

  printf("\nAirports By Type: \n");
  printf("==============================\n");
  qsort(airports, n, sizeof(Airport), cmpByType);
  printAirports(airports, n);

  printf("\nAirports By Name: \n");
  printf("==============================\n");
  qsort(airports, n, sizeof(Airport), cmpByName);
  printAirports(airports, n);


  printf("\nAirports By Name - Reversed: \n");
  printf("==============================\n");
  qsort(airports, n, sizeof(Airport), cmpByNameDesc);
  printAirports(airports, n);

  printf("\nAirports By Country/City: \n");
  printf("==============================\n");
  qsort(airports, n, sizeof(Airport), cmpByCountryCity);
  printAirports(airports, n);

  printf("\nAirports By Latitude: \n");
  printf("==============================\n");
  qsort(airports, n, sizeof(Airport), cmpByLatitude);
  printAirports(airports, n);

  printf("\nAirports By Longitude: \n");
  printf("==============================\n");
  qsort(airports, n, sizeof(Airport), cmpByLongitude);
  printAirports(airports, n);

  printf("\nAirports By Distance from Lincoln: \n");
  printf("==============================\n");
  qsort(airports, n, sizeof(Airport), cmpByLincolnDistance);
  printAirports(airports, n);

  // airports are now in order from closes to lincoln to furthest

  printf("\nClosest Airport to Lincoln: \n");
  printf("==============================\n");
  airportString = airportToString(&airports[0]);
  if (airportString != NULL)  {
    printf("%s\n", airportString);
    free(airportString);
  } else {
    printf("No airports found!\n");
  }

  printf("\nFurthest Airport from Lincoln: \n");
  printf("==============================\n");
  airportString = airportToString(&airports[n-1]);
  if (airportString != NULL)  {
    printf("%s\n", airportString);
    free(airportString);
  } else {
    printf("No airports found!\n");
  }

  printf("\nEast-West Geographic Center: \n");
  printf("==============================\n");
  qsort(airports, n, sizeof(Airport), cmpByLongitude);
  // return middle value
  airportString = airportToString(&airports[n/2]);
  if (airportString != NULL)  {
    printf("%s\n", airportString);
    free(airportString);
  } else {
    printf("No airports found!\n");
  }


  printf("\nNew York, NY airport: \n");
  printf("==============================\n");
  //if none found, print: "No New York airport found!\n"
  int newYorkFound = 0;
  Airport *newYorkAirports = filterByCity(airports, n, "New York", "US", &newYorkFound);
  if (newYorkAirports == NULL) {
    printf("No New York airport found!\n");
  } else {
    printAirports(newYorkAirports, newYorkFound);
    free(newYorkAirports);
  }
  

  printf("\nLarge airport: \n");  
  printf("==============================\n");
  //if none found, print: "No large airport found!\n"
  int largeAirportFound = 0;
  Airport *largeAirports = filterBySize(airports, n, "large_airport", &largeAirportFound);
  if (largeAirports == NULL) {
    printf("No large airport found!\n");
  } else {
    printAirports(largeAirports, largeAirportFound);
    free(largeAirports);
  }
  

  return;
}

char* airportToString(const Airport* a) {
  char temp[1000];
  //this formatting is required but the code may need to be adapted
  // to your definiion of your Airport structure.
  sprintf(temp, "%-8s %-15s %-20s %.2f %.2f %d %-10s %-2s", a->gpsId, a->type, a->name,
          a->latitude, a->longitude, a->elevationFeet, a->city,
          a->countryAbbrv);
  char* result = (char*)malloc(sizeof(char) * (strlen(temp) + 1));
  strcpy(result, temp);
  return result;
}

void printAirports(Airport *airports, int n) {
  for(int i=0; i<n; i++) {
    char *s = airportToString(&airports[i]);
    printf("%s\n", s);
    free(s);
  }

  return;
}

int cmpByGPSId(const void* a, const void* b) {
  const char* a_gpsId = ((const Airport *)a)->gpsId;
  const char* b_gpsId = ((const Airport *)b)->gpsId;

  return strcmp(a_gpsId, b_gpsId);
}

int cmpByType(const void* a, const void* b) {
  const char* aType = ((const Airport*)a)->type;
  const char* bType = ((const Airport*)b)->type;

  return strcmp(aType, bType);
}

int cmpByName(const void* a, const void* b) {
  const char* aName = ((const Airport*)a)->name;
  const char* bName = ((const Airport*)b)->name;

  return strcmp(aName, bName);
}

int cmpByNameDesc(const void* a, const void* b) {
  const char* aName = ((const Airport*)a)->name;
  const char* bName = ((const Airport*)b)->name;

  return strcmp(bName, aName);
}


int cmpByCountryCity(const void* a, const void* b) {
  const Airport* aAirport = (const Airport*)a;
  const Airport* bAirport = (const Airport*)b;

  // check country, if the strings are equal it will return 0, else it will return number
  // if -1 or 1 returned, don't need to check city, return the result of strcmp
  int countryCmp = strcmp(aAirport->countryAbbrv, bAirport->countryAbbrv);
  if (countryCmp != 0) {
    return countryCmp;
  }

  // countries are equal, check cities
  return strcmp(aAirport->city, bAirport->city);
}

int cmpByLatitude(const void* a, const void* b) {
  const double aVal = ((const Airport*)a)->latitude;
  const double bVal = ((const Airport*)b)->latitude;

  if (aVal < bVal) return 1;
  else if (aVal > bVal) return -1;
  else return 0;
}

int cmpByLongitude(const void* a, const void* b) {
  const double aVal = ((const Airport*)a)->longitude;
  const double bVal = ((const Airport*)b)->longitude;

  if (aVal > bVal) return 1;
  else if (aVal < bVal) return -1;
  else return 0;
}

int cmpByLincolnDistance(const void* a, const void* b) {
  const Airport* _a = (const Airport*)a;
  const Airport* _b = (const Airport*)b;

  // create lincoln airport struct, calculate distance between these 2 points
  Airport lincoln = {"0R2", "", "", 40.846176, -96.75471, 4603, "Lincoln", "USA"};
  double distance_a = getAirDistance(&lincoln, _a);
  double distance_b = getAirDistance(&lincoln, _b);

  if (distance_a > distance_b) return 1;
  else if (distance_a < distance_b) return -1;
  else return 0;
}

Airport* filterByCity(Airport *airports, int n, char *city, char* countryAbbr, int *output_size) {
  int found = 0; 
  for (int i = 0; i<n; i++) {
    if (strcmp(airports[i].city, city) == 0 && 
        strcmp(airports[i].countryAbbrv, countryAbbr) == 0) {
      found++;
    }
  }

  if (found == 0) {
    return NULL;
  }

  int j = 0;
  Airport *result = (Airport *) malloc(sizeof(Airport) * found);
  for (int i = 0; i<n; i++) {
    if (strcmp(airports[i].city, city) == 0) {
      result[j] = airports[i];
      j++;
    }
  }
  
  *output_size = found;
  return result;
}

Airport* filterBySize(Airport *airports, int n, char *size, int *output_size) {
  int found = 0; 
  for (int i = 0; i<n; i++) {
    if (strcmp(airports[i].type, size) == 0) {
      found++;
    }
  }

  if (found == 0) {
    return NULL;
  }

  int j = 0;
  Airport *result = (Airport *) malloc(sizeof(Airport) * found);
  for (int i = 0; i<n; i++) {
    if (strcmp(airports[i].type, size) == 0) {
      result[j] = airports[i];
      j ++;
    }
  }
  
  *output_size = found;
  return result;
}