package ro.utcn;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Vehicle> list = new ArrayList<Vehicle>();

        list.add(new Bicycle("B 01 ABC", "Trek", "X-Caliber 8", 2019, BicycleType.MOUNTAIN, false));
        list.add(new Bicycle("B 02 ABC", "Trek", "X-Caliber 8", 2019, BicycleType.MOUNTAIN, false));
        list.add(new Car("B 03 ABC", "Dacia", "Logan", 2019, 4, false, false));
        list.add(new Car("B 04 ABC", "Hyundai", "Tucson", 2022, 4, true, true));
        list.add(new Motorcycle("B 05 ABC", "Kawasaki", "Ninja", 2020, 1000, true));
        list.add(new Motorcycle("B 06 ABC", "Harley", "Softail", 2021, 1745, false));


        for (Vehicle vehicle : list) {
            vehicle.printDetails();
            System.out.println();
        }

    }

}