/**
 * Author: Max Schessler
 * Date: 2024-12-2
 * 
 * This file contains method declarations for Airports
 */



#ifndef AIRPORT_H
#define AIRPORT_H

/**
 * This is a collection of utility functions involving
 * and airport structure.
 */

typedef struct {
  char *gpsId;
  char *type;
  char *name;
  double latitude; 
  double longitude;
  int elevationFeet;
  char *city;
  char *countryAbbrv;
} Airport;

/**
 * A factory function to create a new Airport with the given
 * attributes.  This function should make *deep* copies of each
 * of the relevant fields and return a pointer to the newly
 * created Airport structure.
 */
Airport* createAirport(const char* gpsId,
                       const char* type,
                       const char* name,
                       double latitude,
                       double longitude,
                       int elevationFeet,
                       const char* city,
                       const char* countryAbbrv);

/**
 * This function initializes an existing allocated
 * Airport structure with the given attributes.
 */
void initAirport(Airport* airport,
                 const char* gpsId,
                 const char* type,
                 const char* name,
                 double latitude,
                 double longitude,
                 int elevationFeet,
                 const char* city,
                 const char* countryAbbrv);

/**
 * Constructs a new string representation of the given
 * Airport structure.
 */
char* airportToString(const Airport* a);

/**
 * Prints all the airports in the given array of n
 * Airports.
 */
void printAirports(Airport *airports, int n);

/**
 * Converts the given degree value to radians.
 */
double degreesToRadians(double degree);

/**
 * cmputes the air distance, in kilometers, between
 * the two Airports using their latitude/longitude
 */
double getAirDistance(const Airport* origin, const Airport* destination);

/**
 * Frees all the memory used by the given Airport structure.
 */
void freeAirport(Airport *airport);



/**
 * @brief Calculates the estimated travel time for a series of airport stops.
 *
 * This function computes the total estimated travel time for a given series of airport stops,
 * taking into account the average speed of travel and the average layover time at each stop.
 *
 * @param stops An array of Airport structures representing the stops in the travel itinerary.
 * @param size The number of stops in the travel itinerary.
 * @param aveKmsPerHour The average speed of travel in kilometers per hour.
 * @param aveLayoverTimeHrs The average layover time at each stop in hours.
 * @return The estimated total travel time in hours.
 */
double getEstimatedTravelTime(const Airport* stops,
                              int size,
                              double aveKmsPerHour,
                              double aveLayoverTimeHrs);

/**
 * A comparator function that orders the two Airport structures by
 * their GPS IDs in lexicographic order.
 * 
 * @param a a pointer to an Airport structure
 * @param b a pointer to an Airport structure
 */
int cmpByGPSId(const void* a, const void* b);

/**
 * A comparator function that orders the two Airport structures by
 * their type.
 * 
 * @param a a pointer to an Airport structure
 * @param b a pointer to an Airport structure
 */
int cmpByType(const void* a, const void* b);

/**
 * A comparator function that orders the two Airport structures by
 * their name in lexicographic order.
 * 
 * @param a a pointer to an Airport structure
 * @param b a pointer to an Airport structure
 */
int cmpByName(const void* a, const void* b);

/**
 * A comparator function that orders the two Airport structures by
 * their name in reverse lexicographic order.
 * 
 * @param a a pointer to an Airport structure
 * @param b a pointer to an Airport structure
 */
int cmpByNameDesc(const void* a, const void* b);

/**
 * A comparator function that orders the two Airport structures first by
 * country, then by city
 * 
 * @param a a pointer to an Airport structure
 * @param b a pointer to an Airport structure
 */
int cmpByCountryCity(const void* a, const void* b);

/**
 * A comparator function that orders the given Airport structures
 * by their latitudes north to south
 * 
 * @param a a pointer to an Airport structure
 * @param b a pointer to an Airport structure
 */
int cmpByLatitude(const void* a, const void* b);

/**
 * A comparator function that orders the given Airport structures
 * by their longitudes west to east
 * 
 * @param a a pointer to an Airport structure
 * @param b a pointer to an Airport structure
 */
int cmpByLongitude(const void* a, const void* b);

/**
 * A comparator function that orders the two Airport structures by
 * their relative distance from Lincoln Municipal Airport
 * (0R2, 40.846176, -96.75471)
 * in ascending order according (closest to Lincoln would come first)
 * 
 * @param a a pointer to an Airport structure
 * @param b a pointer to an Airport structure
 */
int cmpByLincolnDistance(const void* a, const void* b);

/**
void generateReports(Airport *airports, int n);


 * given array of Airport structures.
 */
void generateReports(Airport *airports, int n);

/**
 * Get Airports that are in city.
 * 
 * @param airports a pointer to an array of Airport structures
 * @param n the number of elements in the array
 * @param city the city to filter by
 * @param output_size int passed by ref, will be output size of resulting array
 */
Airport* filterByCity(Airport *airports, int n, char *city, char* countryAbbr, int *output_size);

/**
 * Filter airports by size.
 * 
 * @param airports a pointer to an array of Airport structures
 * @param n the number of elements in the array
 * @param size the size to filter by
 * @param output_size int passed by ref, will be output size of resulting array
 */
Airport* filterBySize(Airport *airports, int n, char *size, int *output_size);


#endif // AIRPORT_H