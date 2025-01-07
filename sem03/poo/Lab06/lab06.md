## Vehicle Rental System

### Problem Description

You are tasked with designing a class hierarchy for a vehicle rental system. The system should allow for the rental of different types of vehicles, such as cars, bicycles, and motorcycles. Each vehicle type has specific attributes and methods related to rentals.

### Class Hierarchy

1. **Vehicle (Base Class):**
    - Attributes:
        - `registrationNumber` (string)
        - `make` (string)
        - `model` (string)
        - `year` (int)
        - `rentalRate` (double)
    - Methods:
        - `rent()`: Mark the vehicle as rented.
        - `returnVehicle()`: Mark the vehicle as returned.
        - `calculateRentalCost(days)`: Calculate the rental cost based on the number of days rented.

2. **Car (Subclass of Vehicle):**
    - Attributes:
        - `numberOfDoors` (int)
        - `hasAC` (boolean)
        - `hasAutomaticTransmission` (boolean)
    - Methods:
        - `calculateRentalCost(days)`: Override the base method to consider car-specific rental pricing.

3. **Bicycle (Subclass of Vehicle):**
    - Attributes:
        - `type` (string) - e.g., mountain, road, city
        - `isElectric` (boolean)
    - Methods:
        - `calculateRentalCost(hours)`: Override the base method to calculate rental cost for bicycles.

4. **Motorcycle (Subclass of Vehicle):**
    - Attributes:
        - `engineDisplacement` (int)
        - `isSportBike` (boolean)
    - Methods:
        - `calculateRentalCost(days)`: Override the base method to determine motorcycle-specific rental rates.
