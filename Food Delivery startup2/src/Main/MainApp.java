package Main;

import Model.CustOrder;
import java.util.ArrayList;
import java.util.List;

public class MainApp {
    public static void main(String[] args) {
        CustOrder Prince=new CustOrder();
        List<String> foodItem=new ArrayList<>();
        foodItem.add("Burger");
        foodItem.add("Coke");
        Prince.setInfo("prince", foodItem, false, "4th Oct", true);
        Prince.calculatePrice();
        System.out.println(Prince.getPrice());
   }
}
