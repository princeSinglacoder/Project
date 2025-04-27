package Model;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class FoodItem {
    private static final Map<String, Integer> priceMap = new HashMap<>();
    static {
        priceMap.put("Pizza", 150);
        priceMap.put("Burger", 100);
        priceMap.put("Coke", 50);
        priceMap.put("Brownies", 60);
    }
    public static int getPrice(String item) {
        return priceMap.get(item);
    }
}
