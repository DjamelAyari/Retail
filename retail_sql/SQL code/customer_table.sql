CREATE TABLE customer
(
id_customer int not null auto_increment,
familly_name_customer varchar(50) not null,
name_customer varchar(50) not null,
birth_date_customer date not null,
email_customer varchar(50) not null,
phone_customer int not null,
alley_number_customer int not null,
repetition_index_customer varchar(5),
alley_type_customer varchar(20) not null,
alley varchar(50) not null,
zip_code_customer int not null,
city_customer varchar(50) not null,
country varchar(50) not null,

primary key (id_customer),
constraint unique_cutomer unique (familly_name_customer, name_customer, birth_date_customer)
);