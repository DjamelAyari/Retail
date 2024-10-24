CREATE TABLE fruit
(
	id_fruit int not null auto_increment,
    name_fruit varchar(50) not null,
    latin_name_fruit varchar(50),
    variety_fruit varchar(50) not null,
    
    primary key (id_fruit),
    constraint unique_fruit unique (name_fruit, variety_fruit)
);