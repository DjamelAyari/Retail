CREATE TABLE gathering
(
	id_gathering int not null auto_increment,
    id_fruit int,
    id_vegetable int,
    month_gathering varchar(15) not null,
    
    primary key (id_gathering),
    constraint unique_gathering1 unique (id_fruit, month_gathering),
    constraint unique_gathering2 unique (id_vegetable, month_gathering),
    foreign key (id_fruit) references fruit (id_fruit),
    foreign key (id_vegetable) references vegetable (id_vegetable)
);