package ro.utcn;

public class Motorcycle extends Vehicle{
    private Integer engineDisplacement;
    private Boolean isSportBike;
    public Motorcycle(
            String registrationNumber,
            String make,
            String model,
            Integer year,
            Integer engineDisplacement,
            Boolean isSportBike
    ) {
        super(registrationNumber, make, model, year, 30.0);
        this.engineDisplacement = engineDisplacement;
        this.isSportBike = isSportBike;
    }

    @Override
    public Double calculateRentalCost(Integer days) {
        if (days <= 0)
            throw new RuntimeException("Days must be positive and non-zero");

        Double cost = super.calculateRentalCost(days);

        cost += isSportBike ? 15 : 0;
        cost += engineDisplacement > 1000 ? 20 : 0;

        return cost;
    }

    @Override
    public void printDetails() {
        super.printDetails();
        System.out.println("\tEngine displacement: " + engineDisplacement);
        System.out.println("\tIs sport bike: " + isSportBike);
    }

    public Integer getEngineDisplacement() {
        return engineDisplacement;
    }

    public void setEngineDisplacement(Integer engineDisplacement) {
        this.engineDisplacement = engineDisplacement;
    }

    public Boolean getSportBike() {
        return isSportBike;
    }

    public void setSportBike(Boolean sportBike) {
        isSportBike = sportBike;
    }
}
