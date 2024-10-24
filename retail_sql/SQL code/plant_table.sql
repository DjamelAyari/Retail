CREATE TABLE plant
(
	id_plant int not null auto_increment,
    id_fruit int,
    id_vegetable int,
    brand_plant varchar(50) not null,
    origine_plant varchar(50) not null,
    price_plant decimal(8,2) not null,
           
    primary key (id_plant),
    constraint unique_plant1 unique (id_fruit, brand_plant, origine_plant, price_plant),
    constraint unique_plant2 unique (id_vegetable, brand_plant, origine_plant, price_plant),
    foreign key (id_fruit) references fruit (id_fruit),
    foreign key (id_vegetable) references vegetable (id_vegetable)
);