CREATE TABLE floor_type
(
	id_floor_type int not null auto_increment,
    id_fruit int,
    id_vegetable int,
    floor_type varchar(50) not null,
    
    primary key (id_floor_type),
    constraint unique_floor_type1 unique (id_fruit, floor_type),
    constraint unique_floor_type2 unique (id_vegetable, floor_type),
    foreign key (id_fruit) references fruit (id_fruit),
    foreign key (id_vegetable) references vegetable (id_vegetable)
);