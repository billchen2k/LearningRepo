# SSD for Meal Ordering System

> 10185101210 陈俊潼

![ManageDishes](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-10-25-cnFYnZ.png)

### Operation Contrast:

**Operation:** manageDishes(dishID: dishID, newDetails: Dish)

**Cross References:** Manage Dishes, User Login

**Preconditions:** The user has logged in and has the privilege to edit dishes.

**Postconditions:** 

1. Dish information is updated.
2. The user’s previous order before system maintaining is then recovered.



![OrderMeal](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-10-25-1jnzvG.png)

**Operation:** orderMeal(mealList: mealList, deliverAddress: Address, contactInfo: ContactInfo)

**Cross References:** Order Meal, Accept Order

**Preconditions:** The user has logged in, shop is currently open and the dishes are all still in stock.

**Postconditions:** 

1. A new order instance `createdOrder` is sent to the vender, together with the address and contact information.
2. Vender can decide whether to accept this order or not, based on the locations and the dishes.