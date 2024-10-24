CREATE TABLE orders_detail
(
id_orders_detail int not null auto_increment,
id_orders int not null,
id_edible int,
id_seed int,
id_plant int,
quantity_orders_detail int not null, /*Cette colonne doit se remplir automatiquement*/
price_orders_detail decimal(8,2) not null,

primary key (id_orders_detail),
constraint unique_orders_detail1 unique (id_orders, id_edible),
constraint unique_orders_detail2 unique (id_orders, id_seed),
constraint unique_orders_detail3 unique (id_orders, id_plant),
foreign key (id_orders) references orders (id_orders),
foreign key (id_edible) references edible (id_edible),
foreign key (id_seed) references seed (id_seed),
foreign key (id_plant) references plant (id_plant)
);