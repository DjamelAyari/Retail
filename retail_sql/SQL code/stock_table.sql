CREATE TABLE stock
(
	id_stock int not null auto_increment,
    id_edible int,
	id_seed int,
    id_plant int,
    quantity_stock int not null,
    
    primary key (id_stock),
    constraint unique_stock1 unique (id_edible, quantity_stock),
    constraint unique_stock2 unique (id_seed, quantity_stock),
    constraint unique_stock3 unique (id_plant, quantity_stock),
    foreign key (id_edible) references edible (id_edible),
    foreign key (id_seed) references seed (id_seed),
    foreign key (id_plant) references plant (id_plant)
);