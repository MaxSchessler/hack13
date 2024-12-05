/**
 * Author Max Schessler
 * Date 2024-11-12
 *
 * This file holds my Airport class
 */

package unl.soc;

import java.util.List;

/**
 * The Airport class represents an airport with various attributes such as GPS ID, name, location, type, elevation, city, and country.
 * It provides methods to compute the air distance between two airports and to estimate travel time for a flight with multiple stops.
 * Attributes:
 * - gspId: The GPS ID of the airport.
 * - type: The type of the airport.
 * - name: The name of the airport.
 * - latitude: The latitude of the airport.
 * - longitude: The longitude of the airport.
 * - elevationFeet: The elevation of the airport in feet.
 * - city: The city where the airport is located.
 * - country: The country where the airport is located.
 * 
 */


public class Airport {

	public String gspId;
	public String type;
	public String name;
	public double latitude;
	public double longitude;
	public double elevationFeet;
	public String city;
	public String country;

	
	/**
	 * Constructs an Airport object with the specified details.
	 *
	 * @param gpsId the GPS identifier of the airport
	 * @param name the name of the airport
	 * @param latitude the latitude coordinate of the airport
	 * @param longitude the longitude coordinate of the airport
	 * @param type the type of the airport (e.g., small_airport, large_airport)
	 * @param elevationFeet the elevation of the airport in feet
	 * @param city the city where the airport is located
	 * @param country the country where the airport is located
	 */
	public Airport(String gpsId, String name, double latitude, double longitude, String type, int elevationFeet,
				   String city, String country) {
		
		this.gspId = gpsId;
		this.name = name;
		this.latitude = latitude;
		this.longitude = longitude;
		this.type = type;
		this.elevationFeet = elevationFeet;
		this.city = city;
		this.country = country;
	}

	/**
	 * Calculates the air distance between this airport and the destination airport using the Spherical Law of Cosines.
	 *
	 * @param destination The destination airport to which the air distance is calculated.
	 * @return The air distance in kilometers between this airport and the destination airport.
	 *         Returns -1 if any of the latitude or longitude values are out of their valid ranges.
	 *         Valid latitude range: -90 to 90 degrees.
	 *         Valid longitude range: -180 to 180 degrees.
	 */
	public double getAirDistance(Airport destination) {
		double lat1 = this.latitude;
		double lon1 = this.longitude;
		double lat2 = destination.latitude;
		double lon2 = destination.longitude;
		final double RADIUS = 6371; // Earth's radius in kilometers

		if (lat1 < -90 || lat1 > 90) 
        {
            System.out.println("Origin Latitude value must be between -90 and 90 degrees.\n");
            return -1;
        }
        if (lon1 < -180 || lon1 > 180) 
        {
            System.out.println("Origin Longitude value must be between -180 and 180 degrees.\n");
            return -1;
        }
        if (lat2 < -90 || lat2 > 90) 
        {
            System.out.println("Destination Latitude value must be between -90 and 90 degrees.\n");
            return -1;
        }
        if (lon2 < -180 || lon2 > 180) 
        {
            System.out.println("Destination Longitude value must be between -180 and 180 degrees.\n");
            return -1;
		}

		// Convert degrees to radians
		lat1 = Math.toRadians(lat1);
		lon1 = Math.toRadians(lon1);
		lat2 = Math.toRadians(lat2);
		lon2 = Math.toRadians(lon2);
	
        return Math.acos(( Math.sin(lat1) * Math.sin(lat2)) + (Math.cos(lat1) * Math.cos(lat2) * Math.cos(lon2-lon1))) * RADIUS;
	}

	/**
	 * Calculates the estimated travel time for a given list of airport stops.
	 *
	 * @param stops A list of Airport objects representing the stops in the journey.
	 * @param aveKmsPerHour The average speed in kilometers per hour.
	 * @param aveLayoverTimeHrs The average layover time in hours.
	 * @return The estimated travel time in hours, or -1 if there is an error in the input parameters.
	 *         Errors include null or empty stops list, non-positive average speed, or negative layover time.
	 */
	public static double getEstimatedTravelTime(List<Airport> stops, double aveKmsPerHour, double aveLayoverTimeHrs) {
		if (stops == null || stops.isEmpty()) {
			System.err.println("Stops is null or empty");
			return -1;
		}

		if (aveKmsPerHour <= 0) {
			System.err.println("AveKmsPerHour is negative or zero.");
			return -1;
		}

		if (aveLayoverTimeHrs < 0) {
			System.err.println("aveLayoverTimeHrs is negative.");
			return -1;
		}


		double travelTime = 0;
		double airDistance;
		int size = stops.size();


		for (int i = 0; i<size - 1; i++) {
			airDistance = airDistanceBetweenTwoStops(stops.get(i), stops.get(i+1));
			if (airDistance < 0) {
				return -1;
			}

			travelTime += airDistance / aveKmsPerHour; 
			if (i < size - 2) {
				travelTime += aveLayoverTimeHrs;
			}
		}

		return travelTime;

	}


	/**
	 * Calculates the air distance between two airports using the Spherical Law of Cosines.
	 *
	 * @param origin The origin airport.
	 * @param destination The destination airport.
	 * @return The air distance between the two airports in kilometers, or -1 if any of the latitude or longitude values are out of range.
	 *         Latitude values must be between -90 and 90 degrees.
	 *         Longitude values must be between -180 and 180 degrees.
	 */
	public static double airDistanceBetweenTwoStops(Airport origin, Airport destination) {
		final int RADIUS = 6371;
		double lat1 = origin.latitude, lon1 = origin.longitude, lat2 = destination.latitude, lon2 = destination.longitude;
		if (lat1 < -90 || lat1 > 90) 
        {
            System.out.println("Origin Latitude value must be between -90 and 90 degrees.\n");
            return -1;
        }
        if (lon1 < -180 || lon1 > 180) 
        {
            System.out.println("Origin Longitude value must be between -180 and 180 degrees.\n");
            return -1;
        }
        if (lat2 < -90 || lat2 > 90) 
        {
            System.out.println("Destination Latitude value must be between -90 and 90 degrees.\n");
            return -1;
        }
        if (lon2 < -180 || lon2 > 180) 
        {
            System.out.println("Destination Longitude value must be between -180 and 180 degrees.\n");
            return -1;
        }
 
        lat1 = degreesToRadians(lat1);
        lon1 = degreesToRadians(lon1);
        lat2 = degreesToRadians(lat2);
        lon2 = degreesToRadians(lon2);

        return Math.acos(( Math.sin(lat1) * Math.sin(lat2)) + (Math.cos(lat1) * Math.cos(lat2) * Math.cos(lon2-lon1))) * RADIUS;
        
	}

	 /**
     * This function converts an angle from degrees to radians.
     * 
     * @param degrees The angle in degrees.
     * @return The angle in radians.
     */
    public static double degreesToRadians(double degrees) {

        return degrees * Math.PI / 180;
    }

	/**
	 * Returns a string representation of the object whenever necassary.
	 */
	@Override
	public String toString() {
		return String.format("%s %s %s %.2f %.2f %.0f %s %s",
				gspId, type, name, latitude, longitude, elevationFeet, city, country);
	}

}
