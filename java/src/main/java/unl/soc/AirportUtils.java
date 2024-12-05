/**
 * Author Max Schessler
 * Date 2024-11-12
 *
 * This file holds my Airport utils class.
 */

package unl.soc;

import java.util.Comparator;
import java.util.*;
import java.util.stream.Collectors;

public class AirportUtils {

	/**
	 * A comparator function that orders the two Airport structures by their GPS IDs
	 * in lexicographic order.
	 */
	public static final Comparator<Airport> CMP_GPS_ID = new Comparator<Airport>() {
		@Override
		public int compare(Airport a1, Airport a2) {
			return a1.gspId.compareToIgnoreCase(a2.gspId);
		}
	};

	/**
	 * A comparator function that orders the two Airport structures by their type.
	 */
	public static final Comparator<Airport> CMP_TYPE = new Comparator<Airport>() {
		@Override
		public int compare(Airport a1, Airport a2) {
			return a1.type.compareToIgnoreCase(a2.type);
		}
	};

	/**
	 * A comparator function that orders the two Airport structures by their name in
	 * lexicographic order.
	 */
	public static final Comparator<Airport> CMP_NAME = new Comparator<Airport>() {
		@Override
		public int compare(Airport a1, Airport a2) {
		
			return a1.name.compareToIgnoreCase(a2.name);
		}
	};

	/**
	 * A comparator function that orders the two Airport structures by their name in
	 * reverse lexicographic order.
	 */
	public static final Comparator<Airport> CMP_NAME_DESC = new Comparator<Airport>() {
		@Override
		public int compare(Airport a1, Airport a2) {
			return a2.name.compareToIgnoreCase(a1.name);
		}
	};

	

	/**
	 * A comparator function that orders the two Airport structures first by
	 * country, then by city
	 */
	public static final Comparator<Airport> CMP_COUNTRY_CITY = new Comparator<Airport>() {
		@Override public int compare(Airport a1, Airport a2) {
			int compareCountry = a1.country.compareToIgnoreCase(a2.country);
			if (compareCountry != 0) {
				return compareCountry;
			}

			return a1.city.compareToIgnoreCase(a2.city);
		}
	};

	/**
	 * A comparator function that orders the given Airport structures by their
	 * latitudes north to south
	 */
	public static final Comparator<Airport> CMP_LATITUDE = new Comparator<Airport>() {
		@Override public int compare(Airport a1, Airport a2) {
			if (a1.latitude < a2.latitude) return 1;
			else if (a1.latitude > a2.latitude) return -1;
			else return 0;
		}
	};

	/**
	 * A comparator function that orders the given Airport structures by their
	 * longitudes west to east
	 */
	public static final Comparator<Airport> CMP_LONGITUDE = new Comparator<Airport>() {
		@Override public int compare(Airport a1, Airport a2) {
			if (a1.longitude > a2.longitude) return 1;
			else if (a1.longitude < a2.longitude) return -1;
			else return 0;
		}
	}; 

	/**
	 * A comparator function that orders the two Airport structures by their
	 * relative distance from Lincoln Municipal Airport (0R2, 40.846176, -96.75471)
	 * in ascending order according (closest to Lincoln would come first)
	 */
	public static final Comparator<Airport> CMP_LINCOLN_DISTANCE = new Comparator<Airport>() {
		@Override public int compare(Airport a1, Airport a2) {
			double _a1 = getAirDistanceFromLincoln(a1);
			double _a2 = getAirDistanceFromLincoln(a2);

			if (_a1 > _a2) {
				return 1;
			} else if (_a1 < _a2) {
				return -1;
			} else {
				return 0;
			}
		}

		private final Airport LincolnAirport = new Airport("0R2", "Lincoln Municipal Airport",
		40.846176, -96.75471, "small_airport", 4403, "Lincoln", "USA");

		private double getAirDistanceFromLincoln(Airport a1) {
			return Airport.airDistanceBetweenTwoStops(a1, LincolnAirport);
		}

	};

	/**
	 * A function that generates and prints several reports on the given list of
	 * Airports.
	 */
	public static void generateReports(List<Airport> airports) {

		System.out.printf("Airports (original): \n");
		System.out.printf("==============================\n");
		printList(airports);

		System.out.printf("\nAirports By GPS ID: \n");
		System.out.printf("==============================\n");
		airports.sort(CMP_GPS_ID);
		printList(airports);

		System.out.printf("\nAirports By Type: \n");
		System.out.printf("==============================\n");
		airports.sort(CMP_TYPE);
		printList(airports);

		System.out.printf("\nAirports By Name: \n");
		System.out.printf("==============================\n");
		airports.sort(CMP_NAME);
		printList(airports);

		System.out.printf("\nAirports By Name - Reversed: \n");
		System.out.printf("==============================\n");
		airports.sort(CMP_NAME_DESC);
		printList(airports);

		System.out.printf("\nAirports By Country/City: \n");
		System.out.printf("==============================\n");
		airports.sort(CMP_COUNTRY_CITY);
		printList(airports);

		System.out.printf("\nAirports By Latitude: \n");
		System.out.printf("==============================\n");
		airports.sort(CMP_LATITUDE);
		printList(airports);

		System.out.printf("\nAirports By Longitude: \n");
		System.out.printf("==============================\n");
		airports.sort(CMP_LONGITUDE);
		printList(airports);

		System.out.printf("\nAirports By Distance from Lincoln: \n");
		System.out.printf("==============================\n");
		airports.sort(CMP_LINCOLN_DISTANCE);
		printList(airports);

		System.out.printf("\nClosest Airport to Lincoln: \n");
		System.out.printf("==============================\n");
		System.out.println(airports.get(0));

		System.out.printf("\nFurthest Airport from Lincoln: \n");
		System.out.printf("==============================\n");
		System.out.println(airports.get(airports.size()-1));

		System.out.printf("\nEast-West Geographic Center: \n");
		System.out.printf("==============================\n");
		airports.sort(CMP_LONGITUDE);
		System.out.println(airports.get(airports.size()/2));


		System.out.printf("\nNew York, NY airport: \n");
		System.out.printf("==============================\n");
		// 1. Convert to stream
		// 2. Filter based on predicate: city + country\
		// 3. Collect as list
		// 4. print the new list of New York Airports

		List<Airport> newYorkAirports = airports
				.stream()
				.filter(a -> a.city.equals("New York") && a.country.equals("US"))
				.collect(Collectors.toList());
		if (!newYorkAirports.isEmpty())
			printList(newYorkAirports);
		else 
			System.out.println("No New York airport found!");


		System.out.printf("\nLarge airport: \n");
		System.out.printf("==============================\n");
		//if none found, print: "No large airport found!\n"
		List<Airport> largeAirports = airports
				.stream()
				.filter(a -> a.type.equals("large_airport"))
				.collect(Collectors.toList());
		if (!largeAirports.isEmpty())
			printList(largeAirports);
		else {
			System.out.println("No large airport found!");
		}
	}

	/**
	 * Prints the contents of a collection of airports
	 * @param Airports List of airports
	 */
	public static void printList(List<Airport> Airports) {
		for(Airport a : Airports) {
			System.out.println(a.toString());
		}
	}

}


