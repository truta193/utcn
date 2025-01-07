package ro.utcn;

public class BankTransferService {
    //Moves currency between own accounts
    public static void transferInternalCurrency(
            Customer customer,
            Integer sourceAccountNumber,
            Integer destinationAccountNumber,
            Double amount
    ) {

        BankAccount sourceAccount = customer.getAccount(sourceAccountNumber);
        BankAccount destinationAccount = customer.getAccount(destinationAccountNumber);

        if (sourceAccount == null || destinationAccount == null) {
            throw new IllegalArgumentException("Invalid account number");
        }

        Transaction transaction = new Transaction(
                sourceAccount,
                destinationAccount,
                TransactionType.TRANSFER_OUT,
                amount,
                null);
        sourceAccount.addTransaction(transaction);

        transaction = new Transaction(
                sourceAccount,
                destinationAccount,
                TransactionType.TRANSFER_IN,
                amount,
                null);
        destinationAccount.addTransaction(transaction);
    }

    //Transfer between accounts of different customers
    public static void transferExternalCurrency(
            Customer sourceCustomer,
            Integer sourceAccountNumber,
            Customer destinationCustomer,
            Integer destinationAccountNumber,
            Double amount
    ) {

        if (sourceCustomer == null || destinationCustomer == null) {
            throw new IllegalArgumentException("Invalid customer");
        }

        BankAccount sourceAccount = sourceCustomer.getAccount(sourceAccountNumber);
        BankAccount destinationAccount = destinationCustomer.getAccount(destinationAccountNumber);

        if (sourceAccount == null || destinationAccount == null) {
            throw new IllegalArgumentException("Invalid account number");
        }

        if (amount > sourceAccount.getBalance()) {
            throw new IllegalArgumentException("Amount cannot be greater than balance");
        }

        Transaction transaction = new Transaction(
                sourceAccount,
                destinationAccount,
                TransactionType.TRANSFER_OUT,
                amount,
                null);
        sourceAccount.addTransaction(transaction);

        transaction = new Transaction(
                sourceAccount,
                destinationAccount,
                TransactionType.TRANSFER_IN,
                amount,
                null);
        destinationAccount.addTransaction(transaction);
    }
}
