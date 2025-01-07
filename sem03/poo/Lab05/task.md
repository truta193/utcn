## Banking System - UML Class Diagram

**Description:**
You are tasked with designing a UML class diagram for a basic banking system. The system should allow customers to have accounts, make transactions, and the bank to manage its customers' data.

### Class Diagram Requirements:

1. **Customer Class:**
    - Create a `Customer` class to represent bank customers. Include attributes such as a customer ID, name, contact information, and a list of bank accounts.

2. **Bank Account Class:**
    - Design a `BankAccount` class to represent individual bank accounts. Include attributes like an account number, account type (e.g., savings, checking), balance, and a list of transactions.

3. **Transaction Class:**
    - Create a `Transaction` class to represent financial transactions. Include attributes such as a transaction ID, the source account, the destination account (if applicable), transaction type (e.g., deposit, withdrawal, transfer), and amount.

4. **Bank Staff Class:**
    - Design a `BankStaff` class to represent bank staff members responsible for managing customer accounts. Include attributes for staff ID, name, and position.

### Relationships:

- Establish an association relationship between the `Customer` and `BankAccount` classes to show that a customer can have multiple bank accounts.

- Establish an association relationship between the `Customer` and `Transaction` classes to indicate that a customer can be associated with multiple transactions.

- Establish an aggregation relationship between the `BankStaff` class and the `Transaction` class, indicating that a staff member can be part of multiple transactions.

- Establish a dependency relationship from the `Transaction` class to the `Bank Account` class to indicate that transactions depend on account information.

### ro.utcn.Main Class:
- In the main class, demonstrate how customers can create accounts, make transactions (deposits, withdrawals, transfers), and view their account balances.
