CREATE TABLE cultivation
(
	id_cultivation int not null auto_increment,
    id_fruit int,
    id_vegetable int,
    month_cultivation varchar(15) not null,
    
    primary key (id_cultivation),
    constraint unique_cultivation1 unique (id_fruit, month_cultivation),
    constraint unique_cultivation2 unique (id_vegetable, month_cultivation),
    foreign key (id_fruit) references fruit (id_fruit),
    foreign key (id_vegetable) references vegetable (id_vegetable)
);