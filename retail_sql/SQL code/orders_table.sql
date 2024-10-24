CREATE TABLE orders
(
id_orders int not null auto_increment,
id_customer int not null,
date_orders date not null, /*Cette colonne doit se remplir automatiquement à la date du jour de la commande*/
status_orders varchar(20) not null, /*Cette colonne doit se remplir automatiquement*/
total_items_orders int not null, /*Cette colonne doit se remplir automatiquement*/
total_price_orders decimal(8,2) not null,

primary key (id_orders),
constraint unique_orders unique (id_customer, date_orders, status_orders, total_items_orders, total_price_orders),
foreign key (id_customer) references customer (id_customer)
);