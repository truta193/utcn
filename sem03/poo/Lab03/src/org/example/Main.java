package org.example;

public class Main {
    public static void main(String[] args) {
        Phone firstPhone = new Phone("Samsung", "123");
        Phone secondPhone = new Phone("iPhone", "456");

        firstPhone.powerOn();
        firstPhone.powerOff();

        System.out.println(firstPhone.brandName);
        System.out.println(firstPhone.imeiNumber);
        System.out.println(secondPhone.imeiNumber);

        Phone thirdPhone = new Phone("Nokia", "789");

    }


    public static void doSomething(Phone phone) {
        System.out.printf("The phone's brand name is %s\n", phone.brandName);
    }

}
