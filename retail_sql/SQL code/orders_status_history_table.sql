CREATE TABLE orders_status_history
(
	id_status_history int not null auto_increment,
    id_orders int not null,
    status_orders ENUM('Pending', 'Processing', 'Shipped', 'Delivered', 'Completed', 'Cancelled', 'Returned', 'Refunded', 'On Hold', 'Failed') NOT NULL,
    status_change_date TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    
    primary key (id_status_history),
    constraint unique_status unique (id_orders, status_orders, status_change_date),
    foreign key (id_orders) references orders (id_orders)
);