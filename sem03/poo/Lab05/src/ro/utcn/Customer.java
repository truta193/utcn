package ro.utcn;

import jdk.jfr.Unsigned;

import java.util.ArrayList;
import java.util.List;

public class Customer {
    private static Integer nextId = -1;
    private Integer id;
    private String name;
    private String address;
    private String email;
    private String phone;
    private List<BankAccount> accounts = new ArrayList<BankAccount>();

    public Customer(String name, String address, String email, String phone) {
        this.id = ++nextId;
        this.name = name;
        this.address = address;
        this.email = email;
        this.phone = phone;
    }

    public void openAccount(AccountType type) {
        BankAccount account = new BankAccount(type);
        accounts.add(account);
    }

    public BankAccount getAccount(Integer accountNumber) {
        for (BankAccount account : accounts) {
            if (account.getAccountNumber().equals(accountNumber)) {
                return account;
            }
        }
        return null;
    }

    public void depositCurrency(Integer accountNumber, Double amount) {
        BankAccount account = getAccount(accountNumber);

        if (account == null) {
            throw new IllegalArgumentException("Invalid account number");
        }

        account.depositCurrency(amount);
    }

    public void withdrawCurrency(Integer accountNumber, Double amount) {
        BankAccount account = getAccount(accountNumber);

        if (account == null) {
            throw new IllegalArgumentException("Invalid account number");
        }

        account.withdrawCurrency(amount);
    }



    public Double getBalance(Integer accountNumber) {
        BankAccount account = getAccount(accountNumber);

        if (account == null) {
            throw new IllegalArgumentException("Invalid account number");
        }

        return account.getBalance();
    }

    public String getName() {
        return this.name;
    }

    public Integer getAccountNumber(Integer accountNumber) {
        BankAccount account = getAccount(accountNumber);

        if (account == null) {
            throw new IllegalArgumentException("Invalid account number");
        }

        return account.getAccountNumber();
    }

}
