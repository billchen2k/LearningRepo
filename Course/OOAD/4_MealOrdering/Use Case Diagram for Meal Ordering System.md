# Use Case Diagram for Meal Ordering System

> 1018510120 陈俊潼

![UseCaseDiagram1](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-10-19-CGpAiF.png)

## 用例描述

### Order Meal

| Section       | Content                                                      |
| ------------- | ------------------------------------------------------------ |
| Summary       | Customer submit a meal order.                                |
| Actor List    | Customer, System Database.                                   |
| Precondition  | Customer has logged in; Vendor is open; The order should be valid. |
| Description   | The customer first chose from a variety of dishes from the vendor, then choose a deliver address and enter personal information like e-mail and telephone. Then submit a valid meal order to the vendor. |
| Postcondition | The customer will wait until the vendor accepts the order, and then be assigned with a deliverer. |
| Exception     | User not logged in: Acquire user to log in; The shop is not open: Notify user to change to another shop. |

### Manage Dishes

| Section       | Content                                                      |
| ------------- | ------------------------------------------------------------ |
| Summary       | Vendors can manage dishes in the store.                      |
| Actor List    | Vendor, System Database.                                     |
| Precondition  | Vendor has logged in; user has the permission to edit dishes and censoring the comments. |
| Description   | Vendor can add, remove, or edit stock count for each dishes in the store and set the dish status for different users. |
| Postcondition | Dish information is updated.                                 |
| Exception     | Vendor not logged in: Acquire vendor to log in; The content of the dishes contains invalid characters: Ask the vendor to change text to avoid error. |