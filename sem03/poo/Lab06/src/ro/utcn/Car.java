package ro.utcn;

public class Car extends Vehicle{
    private Integer numberOfDoors;
    private Boolean hasAC;
    private Boolean hasAutomaticTransmission;

    public Car(
            String registrationNumber,
            String make,
            String model,
            int year,
            int numberOfDoors,
            boolean hasAC,
            boolean hasAutomaticTransmission
    ) {
        super(registrationNumber, make, model, year, 50.0);
        this.numberOfDoors = numberOfDoors;
        this.hasAC = hasAC;
        this.hasAutomaticTransmission = hasAutomaticTransmission;
    }

    @Override
    public Double calculateRentalCost(Integer days) {
        if (days <= 0)
            throw new RuntimeException("Days must be positive and non-zero");

        Double cost = super.calculateRentalCost(days);

        cost += hasAC ? 10 : 0;
        cost += hasAutomaticTransmission ? 20 : 0;
        cost += numberOfDoors > 3 ? 15 : 0;


        return cost;

    }

    @Override
    public void printDetails() {
        super.printDetails();
        System.out.println("\tNumber of doors: " + numberOfDoors);
        System.out.println("\tHas AC: " + hasAC);
        System.out.println("\tHas automatic transmission: " + hasAutomaticTransmission);
    }

    public Integer getNumberOfDoors() {
        return numberOfDoors;
    }

    public void setNumberOfDoors(Integer numberOfDoors) {
        this.numberOfDoors = numberOfDoors;
    }

    public Boolean getHasAC() {
        return hasAC;
    }

    public void setHasAC(Boolean hasAC) {
        this.hasAC = hasAC;
    }

    public Boolean getHasAutomaticTransmission() {
        return hasAutomaticTransmission;
    }

    public void setHasAutomaticTransmission(Boolean hasAutomaticTransmission) {
        this.hasAutomaticTransmission = hasAutomaticTransmission;
    }
}
