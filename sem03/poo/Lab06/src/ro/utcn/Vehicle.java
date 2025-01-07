package ro.utcn;

public class Vehicle {
    private String registrationNumber;
    private String make;
    private String model;
    private Integer year;
    private Double rentalRate;
    private Boolean isRented;

    public Vehicle(
            String registrationNumber,
            String make,
            String model,
            Integer year,
            Double rentalRate
    ) {
        this.registrationNumber = registrationNumber;
        this.make = make;
        this.model = model;
        this.year = year;
        this.rentalRate = rentalRate;
        this.isRented = false;
    }

    public void rent() {
        if (this.isRented)
            throw new RuntimeException("Vehicle is already rented");

        this.isRented = true;
    }

    public void returnVehicle() {
        if (!this.isRented)
            throw new RuntimeException("Vehicle is not rented");

        this.isRented = false;
    }

    public Double calculateRentalCost(Integer days) {
        if (days <= 0)
            throw new RuntimeException("Days must be positive and non-zero");

        return rentalRate * days;
    }

    public String getRegistrationNumber() {
        return registrationNumber;
    }

    public void setRegistrationNumber(String registrationNumber) {
        this.registrationNumber = registrationNumber;
    }

    public String getMake() {
        return make;
    }

    public void setMake(String make) {
        this.make = make;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public Integer getYear() {
        return year;
    }

    public void setYear(Integer year) {
        this.year = year;
    }

    public Double getRentalRate() {
        return rentalRate;
    }

    public void setRentalRate(Double rentalRate) {
        this.rentalRate = rentalRate;
    }

    public Boolean getRented() {
        return isRented;
    }

    public void setRented(Boolean rented) {
        isRented = rented;
    }

    public void printDetails() {
        System.out.println("Registration number: " + this.registrationNumber);
        System.out.println("\tMake: " + this.make);
        System.out.println("\tModel: " + this.model);
        System.out.println("\tYear: " + this.year);
        System.out.println("\tRental rate: " + this.rentalRate);
        System.out.println("\tIs rented: " + this.isRented);
    }
}
