package Model;

import java.util.ArrayList;
import java.util.List;

public class CustOrder {
    private String name;
    private List<String> items = new ArrayList();
    private Boolean peakHour;
//    private Boolean specialDay;
    private String specialDay;
    private Boolean nightOrder;
    private Boolean normalDel;
    private float totalBill;
    public void setInfo(String name,List<String> foodItem,Boolean peakHour,String specialDay,Boolean nightOrder){
        this.name=name;
        this.items=foodItem;
        this.peakHour=peakHour;
        this.specialDay=specialDay;
        this.nightOrder=nightOrder;
        if(peakHour || SpecialDayOrNot.checkDate(specialDay) || nightOrder){
            this.normalDel=false;
        }
        else{
            this.normalDel=true;
        }
    }
    public void calculatePrice(){
        int price=0;
        for(String item: items){
            price+=FoodItem.getPrice(item);
        }
        float gst=(price*5)/100;
        int normalDelPrice=0,peakHourPrice=0,specialPrice=0,nightOrderPrice=0;
        if(price<500) {
            normalDelPrice = 20;
        }
        if(this.peakHour){
            peakHourPrice=30;
        }
        if(SpecialDayOrNot.checkDate(specialDay)){
            specialPrice=50;
        }
        if(this.nightOrder){
            nightOrderPrice=20;
        }
        price+=Math.max(Math.max(Math.max(normalDelPrice,peakHourPrice),specialPrice),nightOrderPrice);
        price+=gst;
        this.totalBill=price;
    }
    public float getPrice(){
        return this.totalBill;
    }
}
