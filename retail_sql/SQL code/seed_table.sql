CREATE TABLE seed
(
	id_seed int not null auto_increment,
    id_fruit int,
    id_vegetable int,
    brand_seed varchar(50) not null,
    origine_seed varchar(50) not null,
    price_seed decimal(8,2) not null,
    
    primary key (id_seed),
    constraint unique_seed1 unique (id_fruit, brand_seed, origine_seed, price_seed),
    constraint unique_seed2 unique (id_vegetable, brand_seed, origine_seed, price_seed),
    foreign key (id_fruit) references fruit (id_fruit),
    foreign key (id_vegetable) references vegetable (id_vegetable)
);