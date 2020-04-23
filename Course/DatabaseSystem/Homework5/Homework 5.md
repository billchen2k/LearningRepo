## Database Homework 5

> 10185101210 陈俊潼


###7.1

![Work7-Page-3](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-23-Work7-Page-3.png)

### 7.15

![Work7](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-22-Work7%20%281%29.png)



### 7.16

**Relation schema for 7.1:**

customer(<u>customer_id</u>, name, address, licence_id, gender, birthday, phone)

owns(<u>customer_id</u>, <u>car_id</u>)

car(<u>car_id</u>, model, manufatured_date)

accident(<u>accident_id</u>, location, date)

cover(<u>policy_id</u>, ca<u>r</u>_id)

insurance_policy(<u>policy_id</u>, name, amout)

payment(<u>payment_id</u>, <u>policy_id</u>, begin_date, end_date, amount)

**Relation schema for 7.2:**

*Ternary Relationship:*

exams(<u>exam_id</u>, date, time)

course(<u>course_id</u>, name, credit)

section(<u>course_id</u>, <u>section_id</u>, semester, year)

student(<u>student_id</u>, department, gender)

grades(<u>exam_id</u>, <u>student_id</u>, <u>course_id</u>, <u>section_id</u>, grade)

*Binary Relationship:*

course(<u>course_id</u>, name, credit)

section(<u>course_id</u>, <u>section_id</u>, semester, year)

student(<u>student_id</u>, department, gender)

grades(<u>exam_id</u>, <u>student_id</u>, <u>course_id</u>, <u>section_id</u>, grade)

**Relation schema for 7.3**

match(<u>match_id</u>, date, location)

score(<u>match_id</u>, <u>player_id</u>, score)

player(<u>player_id</u>, name, gender, birthday)

### 7.20

a.

author(<u>name</u>, address, URL)

publisher(<u>name</u>, address, phone, URL)

book(<u>ISBN</u>, title, year, price)

customer(<u>email</u>, name, address, phone)

shopping basket(<u>baske_id</u>)

warehouse(<u>code</u>, address, phone)

(The primary key is denoted unerline.)

b.

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-23-Work7-Page-5.png" alt="Work7-Page-5" style="zoom: 50%;" />

c.

![Work7-Page-5](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-23-Work7-Page-5%20%281%29.png)

### 7.21

E-R Diagram:

![Work7-7.21](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-23-Work7-7.21%20%281%29.png)

Relational schemas:

company(<u>**company_id**</u>, name, address)

brand_manufactures(<u>company_id</u>, <u>brand_id</u>)

brand(<u>**brand_id**</u>, name)

model(<u>**model_id**</u>, model_name, <u>brand_id</u>)

options(<u>**option_id**</u>, option_type, option_value, <u>model_id</u>)

vehicle(<u>**VIN**</u>, <u>model_id</u>, <u>customer_id</u>)

vehicle_options(<u>VIN</u>, <u>option_id</u>)

customer(<u>**customer_id**</u>, name, address, registration_date)

dealers(<u>**dealer_id**</u>, dealer_name, location)

sales(<u>dealer_id</u>, <u>VIN</u>)

>  The primary key of each relation is denoted ==underline and bold==.
>
>  The foreign key of each relation is denoted underline.

### 7.22

![Work7-7.22](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-23-Work7-7.22%20%283%29.png)

package(<u>**package_id**</u>, content, weight, category, <u>sender</u>, <u>receiver</u>, send_time, receive_time)

customer(<u>**customer_id**</u>, name, address, phone)

history(<u>**log_id**</u>, datetime, truck, plane, airport, warehouse, <u>package_id</u>)

> The primary key of each relation is denoted ==underline and bold==.
> 
> The foreign key of each relation is denoted underline.

### 7.23

![Work7-7.23](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-04-23-Work7-7.23%20%281%29.png)

customer(<u>**customer_id**</u>, name, address, phone, gender)

reservation(<u>**customer_id**</u>, <u>section_id</u>)

airline_section(<u>**section_id**</u>, status, delay_duration, <u>schedule_id</u>, <u>flight_no</u>)

airline(<u>**flight_no**</u>, from, to, company)

schedule(**<u>schedule_id</u>**, departure_time, arrival_time, lane)

> The primary key of each relation is denoted ==underline and bold==.
>
> The foreign key of each relation is denoted underline.

