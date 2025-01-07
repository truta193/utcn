package org.example;

public class Phone {
    String brandName;
    String imeiNumber;
    String contactPersonPhoneNumber;
    Integer volume = 0;
    boolean isRepaired = false;

    public Phone() {

    }

    public Phone(String brandName, String imeiNumber) {
        this.brandName = brandName;
        this.imeiNumber = imeiNumber;
    }

    public Phone(String brandName) {
        this(); // calls the default constructor
        this.brandName = brandName;
    }

    public void setAsRepaired() {
        isRepaired = true;
    }

    public void powerOn() {
        System.out.println("Powering on...");
    }

    public void powerOff() {
        System.out.println("Powering off...");
    }

    public void tweakVolume(int amount) {
        if (volume + amount < 0)
            volume = 0;
        else if (volume + amount > 100)
            volume = 100;
        else
            volume += amount;

    }


}
