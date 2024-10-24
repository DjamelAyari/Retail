CREATE TABLE sun_need
(
	id_sun_need int not null auto_increment,
    id_fruit int,
    id_vegetable int,
    quantity_sun_need varchar(50) not null,
    
    primary key (id_sun_need),
    constraint unique_sun_need1 unique (id_fruit, quantity_sun_need),
    constraint unique_sun_need2 unique (id_vegetable, quantity_sun_need),
    foreign key (id_fruit) references fruit (id_fruit),
    foreign key (id_vegetable) references vegetable (id_vegetable)
);