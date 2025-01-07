package ro.utcn;

public class Bicycle extends Vehicle{
    private BicycleType type;
    private Boolean isElectric;

    public Bicycle(
            String registrationNumber,
            String make,
            String model,
            Integer year,
            BicycleType type,
            Boolean isElectric
    ) {
        super(registrationNumber, make, model, year, 10.0);
        this.type = type;
        this.isElectric = isElectric;
    }

    @Override
    public Double calculateRentalCost(Integer days) {
        if (days <= 0)
            throw new RuntimeException("Days must be positive and non-zero");

        Double cost = super.calculateRentalCost(days);

        cost += isElectric ? 20 : 0;
        switch (type) {
            case MOUNTAIN:
                cost += 5;
                break;
            case RACING:
                cost += 10;
                break;
            case BMX:
                cost += 5;
                break;
            case FOLDING:
                cost += 5;
                break;
        }

        return cost;
    }

    @Override
    public void printDetails() {
        super.printDetails();
        System.out.println("\tType: " + type);
        System.out.println("\tIs electric: " + isElectric);
    }

    public BicycleType getType() {
        return type;
    }

    public void setType(BicycleType type) {
        this.type = type;
    }

    public Boolean getElectric() {
        return isElectric;
    }

    public void setElectric(Boolean electric) {
        isElectric = electric;
    }
}
