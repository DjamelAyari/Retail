CREATE TABLE edible
(
	id_edible int not null auto_increment,
    id_fruit int,
    id_vegetable int,
    origine_edible varchar(50) not null,
    price_edible decimal(8,2) not null,
    
    primary key (id_edible),
    constraint unique_edible1 unique (id_fruit, origine_edible, price_edible),
    constraint unique_edible2 unique (id_vegetable, origine_edible, price_edible),
    foreign key (id_fruit) references fruit (id_fruit),
    foreign key (id_vegetable) references vegetable (id_vegetable)
);