ALTER TABLE orders
MODIFY COLUMN date_orders TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP;

ALTER TABLE orders
MODIFY COLUMN status_orders ENUM('Pending', 'Processing', 'Shipped', 'Delivered', 'Completed', 'Cancelled', 'Returned', 'Refunded', 'On Hold', 'Failed') NOT NULL DEFAULT 'Pending';

ALTER TABLE orders
MODIFY total_items_orders INT NOT NULL DEFAULT 0;

ALTER TABLE orders
MODIFY total_price_orders INT NOT NULL DEFAULT 0.00;

