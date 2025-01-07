package ro.utcn;

import ro.utcn.BankAccount;
import ro.utcn.Customer;

public class Main {
    public static void main(String[] args) {
        Customer c1 = new Customer("John Doe", "Cluj-Napoca", "test@gmail.com", "0740123456");

        c1.openAccount(AccountType.CURRENT);
        c1.depositCurrency(0, 100.0);
        c1.withdrawCurrency(0, 50.0);
        System.out.println(c1.getBalance(0));

        c1.openAccount(AccountType.SAVINGS);
        c1.depositCurrency(1, 75.0);
        System.out.println(c1.getBalance(1));

        BankTransferService.transferInternalCurrency (c1, 0, 1, 25.0);
        System.out.println(c1.getBalance(0));
        System.out.println(c1.getBalance(1));

        Customer c2 = new Customer("Jane Dee", "Cluj-Napoca", "hi@yahoo.com", "0740123456");
        c2.openAccount(AccountType.CURRENT);

        BankTransferService.transferExternalCurrency(c1, 0, c2, 2, 25.0);
        System.out.println(c1.getName() + " has " + c1.getBalance(0) + " in account 0");
        System.out.println(c2.getName() + " has " + c2.getBalance(2) + " in account 2");


    }
}