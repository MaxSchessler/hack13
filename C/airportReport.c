/**
 * Author: Max Schessler
 * Date: 2024-12-2
 * 
 * This file contains tests for airport functions.
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "airport.h"

int main() {
    // testing createAirport
    // Airport* a1 = createAirport("OMA1", "normal", "Eppley Airfield", 41.30, -95.89, 150, "Omaha", "US");
    // Airport* a2 = createAirport("CHI0", "huge", "O'Hare", 41.97, -87.91, 125, "Chicago", "US");
    // Airport* a3 = createAirport("YYZA", "medium", "Pearson", 43.60, -79.60, 25, "Toronto", "CN");
    // Airport* a4 = createAirport("NYNY", "intl", "LaGuardia", 40.78, -73.87, 50, "New York", "US");
    // Airport* a5 = createAirport("YACS", "small_airport", "Acacia Downs", -31.42, 141.90, 0, "None", "AU");
    // Airport* a6 = createAirport("9TX0", "heliport", "Houston Police", 29.66, -95.32, 40, "Houston", "US");
    // Airport* a7 = createAirport("EDDH", "large_airport", "Hamburg Airport", 53.63, 9.99, 53, "Hamburg", "DE");
    // Airport* a8 = createAirport("99KS", "tiny", "Elm Creek", 37.41, -98.65, 1600, "Medicine Lodge", "US");
    // Airport* a9 = createAirport("26MA", "tiny_airport", "Pepperell Airport", 42.70, -71.55, 176, "Pepperell", "US");
    // Airport* a10 = createAirport("KIXA", "one_strip", "Halifax-Northampton", 36.33, -77.64, 145, "Roanoke Rapids", "US");

    Airport* a1 = createAirport("SLIY", "small_airport", "Intiraymi Airport", -17.81, -67.44, 1246, "La Joya", "BO");
    Airport* a2 = createAirport("CYOH", "medium", "Oxford House Airport", 54.93, -95.28, 663, "Oxford House", "CA");
    Airport* a3 = createAirport("UHK1", "smallest", "Blagodatnoye Base", 48.41, 135.41, 0, "Blagodatnoye", "RU");
    Airport* a4 = createAirport("NYNY", "intl", "JFK", 40.78, -73.87, 50, "New York", "US");
    Airport* a5 = createAirport("RK6M", "heliport", "H 173 Heliport", 37.91, 126.88, 1552, "Camp Ethan", "KR");
    Airport* a6 = createAirport("LGSR", "smaller", "Santorini Airport", 36.40, 25.48, 127, "Santorini", "GR");
    Airport* a7 = createAirport("KGGW", "mediumish", "Wokal Field", 48.21, -106.61, 2296, "Glasgow", "US");
    Airport* a8 = createAirport("FR-0045", "helipad", "Le Port Heliport", 47.98, 3.39, 254, "Joigny", "FR");
    Airport* a9 = createAirport("NGAB", "tiny", "Abaiang Airport", 1.80, 173.04, 0, "Abaiang", "KI");
    Airport* a10 = createAirport("KR-0515", "heli", "Cheonmi-ri South", 38.25, 127.87, 0, "Cheonmi-ri", "KR");

    int n = 10;
    Airport* airports = (Airport*) malloc(sizeof(Airport) * 10);
    airports[0] = *a1;
    airports[1] = *a2;
    airports[2] = *a3;
    airports[3] = *a4;
    airports[4] = *a5;
    airports[5] = *a6;
    airports[6] = *a7;
    airports[7] = *a8;
    airports[8] = *a9;
    airports[9] = *a10;;

    generateReports(airports, n);

    freeAirport(a1);
    freeAirport(a2);
    freeAirport(a3);
    freeAirport(a4);
    freeAirport(a5);
    freeAirport(a6);
    freeAirport(a7);
    freeAirport(a8);
    freeAirport(a9);
    freeAirport(a10);
    free(airports);


    

    //generateReports(airports, n);
}