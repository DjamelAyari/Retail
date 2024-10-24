SELECT
	name_fruit,
    variety_fruit,
    latin_name_fruit,
    origine_seed,
    price_seed,
    quantity_stock,
    month_clutivation,
    month_gathering,
    floor_type,
    sun_need,
    water_need
FROM
	fruit
JOIN
	seed
ON
	fruit.id_fruit = seed.id_fruit
JOIN
	gathering
ON
	fruit.id_fruit = gathering.id_fruit
JOIN
	cultivation
ON
	fruit.id_fruit = cultivation.id_fruit
JOIN
	floor_type
ON
	fruit.id_fruit = floor_type.id_fruit
JOIN
	sun_need
ON
	fruit.id_fruit = sun_need.id_fruit
JOIN
	water_need
ON
	fruit.id_fruit = water_need.id_fruit
LEFT JOIN
	stock
ON
	seed.id_seed = stock.id_seed
WHERE 1=1
    AND name_fruit = ?
    AND variety_fruit = ?
    AND latin_name_fruit = ?
    AND origine_seed = ?
    AND price_seed BETWEEN ? AND ?
    AND quantity_stock = ?
    AND month_cultivation = ?
    AND month_gathering = ?
    AND floor_type = ?
    AND sun_need = ?
    AND water_need = ?;