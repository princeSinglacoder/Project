package Model;

import java.util.HashMap;
import java.util.Map;

public class SpecialDayOrNot {
    private static final Map<String, String> specialDay = new HashMap<>();
    static {
        specialDay.put("4th Nov","Diwali");
        specialDay.put("25 Dec","Christmas");
    }
    public static boolean checkDate(String date) {
        if(specialDay.containsKey(date)){
            return true;
        }
        return false;
    }
}
