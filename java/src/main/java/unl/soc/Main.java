package unl.soc;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
    

        List<Airport> airports = new ArrayList<>();
        airports.add(new Airport("SLIY", "Intiraymi Airport", -17.81, -67.44, "small_airport", 1246, "La Joya", "BO"));
        airports.add(new Airport("CYOH", "Oxford House Airport", 54.93, -95.28, "medium", 663, "Oxford House", "CA"));
        airports.add(new Airport("UHK1", "Blagodatnoye Base", 48.41, 135.41, "smallest", 0, "Blagodatnoye", "RU"));
        airports.add(new Airport("NYNY", "JFK", 40.78, -73.87, "intl", 50, "New York", "US"));
        airports.add(new Airport("RK6M", "H 173 Heliport", 37.91, 126.88, "heliport", 1552, "Camp Ethan", "KR"));
        airports.add(new Airport("LGSR", "Santorini Airport", 36.40, 25.48, "smaller", 127, "Santorini", "GR"));
        airports.add(new Airport("KGGW", "Wokal Field", 48.21, -106.61, "mediumish", 2296, "Glasgow", "US"));
        airports.add(new Airport("FR-0045", "Le Port Heliport", 47.98, 3.39, "helipad", 254, "Joigny", "FR"));
        airports.add(new Airport("NGAB", "Abaiang Airport", 1.80, 173.04, "tiny", 0, "Abaiang", "KI"));
        airports.add(new Airport("KR-0515", "Cheonmi-ri South", 38.25, 127.87, "heli", 0, "Cheonmi-ri", "KR"));
        AirportUtils.generateReports(airports);

    }
}