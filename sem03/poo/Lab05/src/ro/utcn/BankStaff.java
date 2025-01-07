package ro.utcn;

public class BankStaff {
    public static Integer nextId = -1;
    private Integer id;
    private String name;
    private String position;

    public BankStaff(String name, String position) {
        this.name = name;
        this.position = position;
        this.id = ++nextId;
    }

}
