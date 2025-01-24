package model;

import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

public class Person {
    private LocalDate birthDate;

    public Person(LocalDate birthDate) {
        this.birthDate = birthDate;
    }

    public LocalDate getBirthDate() {
        return birthDate;
    }

    public void setBirthDate(LocalDate birthDate) {
        this.birthDate = birthDate;
    }

    public int Age() {
        return (int) ChronoUnit.YEARS.between(birthDate, LocalDate.now());
    }
}
