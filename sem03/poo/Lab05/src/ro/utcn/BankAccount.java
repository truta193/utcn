package ro.utcn;

import java.util.ArrayList;
import java.util.List;

public class BankAccount {
    private static Integer nextId = -1;
    private Integer accountNumber;
    private AccountType accountType;
    private Double balance;
    private List<Transaction> transactions = new ArrayList<Transaction>();

    private Integer getNextId() {
        return ++nextId;
    }

    public BankAccount(AccountType accountType) {
        this.accountType = accountType;
        this.balance = 0.0;
        this.accountNumber = getNextId();
    }

    public Integer getAccountNumber() {
        return this.accountNumber;
    }

    public void depositCurrency(Double amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("Amount cannot be negative");
        }
        this.balance += amount;
    }

    public void withdrawCurrency(Double amount) {
        if (amount < 0) {
            throw new IllegalArgumentException("Amount cannot be negative");
        }
        if (amount > this.balance) {
            throw new IllegalArgumentException("Amount cannot be greater than balance");
        }
        this.balance -= amount;
    }

    public void addTransaction(Transaction transaction) {

        switch (transaction.getTransactionType()) {
            case TRANSFER_IN:
            case DEPOSIT:
                this.balance += transaction.getAmount();
                break;
            case TRANSFER_OUT:
            case WITHDRAWAL:
                this.balance -= transaction.getAmount();
                break;
        }

        transactions.add(transaction);
    }

    public Double getBalance() {
        return this.balance;
    }
}
