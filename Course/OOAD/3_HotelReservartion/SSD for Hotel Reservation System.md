# SSD for Hotel Reservation System

> 10185101210 陈俊潼

### Room Reservation

![Collaboration1!Interaction1!Room Reservation_1](https://billc.oss-cn-shanghai.aliyuncs.com/file/2020-11-13-Collaboration1!Interaction1!Room%20Reservation_1.png)

Operation: roomReservation(roomType: RoomType)

Cross References: Use Cases: Room Reservation

Preconditions: none

Postconditions:

- A new Room `newRoom` instance is created and store in database, indicating the user’s just reserved room
- `newRoom` is associated with a RoomDescriptor class
- A new Bill instance is created and need to be paid by the customer. Bill.amount is the price of the room

### Change Reservation

![changeReservation](https://billc.oss-cn-shanghai.aliyuncs.com/file/2020-11-13-changeReservation.png)

Operation: changeReservation(: This)

Cross References: Use Case: Change Reservation

Preconditions: The customer had an available room before.

Postconditions:

- The room instance that the customer reserved before is updated.
- A new Bill instance is created, indicating the compensation fee for the customer. If the new room costs less than before, customer will be refunded and vice versa.
