## Database Homework 2

> 10185101210 陈俊潼

### 2.1

Employee - *person_name*
Works - *person_name*
Company - company_name

### 2.2

- Inserting: If we insert a tuple like (12345, ABC, Software, 10000) into the table *instructor*, since there isn't Software department in the department relation, the foreign key constraint is corrupted.
- Deleting: Deleting (Comp. Sci., Taylor, 100000) from relation *department* will corrupt the foreign key constraint.

### 2.3

To be a primary key, the key should be able to identify a unique instance and the key should have no sub sets. The day and start time is already abundant to represent a time slot for a certain class. Because if the start time and the day is fixed, the end time is also fixed. So it don't have to be a part of the primary key.

### 2.4

No. Because we can't ascertain that the upcoming new teachers won't have the same name as the teachers we have.

### 2.9

a.

| Relation  | Primary key    |
| --------- | -------------- |
| branch    | branch_name    |
| customer  | customer_name  |
| loan      | Loan_number    |
| borrower  | customer_name  |
| account   | account_number |
| depositor | customer_name  |

b.

| Relation  | Foreign Key                |
| --------- | -------------------------- |
| borrower  | Customer_name(at customer) |
| borrower  | Loan_number(at loan)       |
| account   | Branch_name(at branch)     |
| depositor | account_number(at account) |

### 2.10

No. Now the primary key is s_id together with i_id.

### 2.11

**Relation** is relation schema together with relation instances, meaning the data and structure of a database table.

**Relation Schema** is a set of attributes, or table schema.

### 2.14

- Sometimes one attribute of a instance might not applicable or unpredictable, this is inorder to maintain the completion of the database.
- The NULL value help represent a more accurate model information

