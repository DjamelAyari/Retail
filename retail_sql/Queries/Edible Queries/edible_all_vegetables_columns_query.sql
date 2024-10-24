SELECT
	name_vegetable,
    variety_vegetable,
    latin_name_vegetable,
    origine_edible,
    price_edible,
    quantity_stock,
    month_gathering
FROM
	vegetable
JOIN
	edible
ON
	vegetable.id_vegetable = edible.id_vegetable
JOIN
	gathering
ON
	vegetable.id_vegetable = gathering.id_vegetable
LEFT JOIN
	stock
ON
	edible.id_edible = stock.id_edible
WHERE 1=1
    AND name_vegetable = ?
    AND variety_vegetable = ?
    AND latin_name_vegetable = ?
    AND origine_edible = ?
    AND price_edible BETWEEN ? AND ?
    AND quantity_stock = ?
    AND month_gathering = ?;