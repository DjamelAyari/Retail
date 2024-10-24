SELECT
	name_vegetable,
    variety_vegetable,
    latin_name_vegetable,
    origine_seed,
    price_seed,
    quantity_stock,
    month_clutivation,
    month_gathering,
    floor_type,
    sun_need,
    water_need
FROM
	vegetable
JOIN
	seed
ON
	vegetable.id_vegetable = seed.id_vegetable
JOIN
	gathering
ON
	vegetable.id_vegetable = gathering.id_vegetable
JOIN
	cultivation
ON
	vegetable.id_vegetable = cultivation.id_vegetable
JOIN
	floor_type
ON
	vegetable.id_vegetable = floor_type.id_vegetable
JOIN
	sun_need
ON
	vegetable.id_vegetable = sun_need.id_vegetable
JOIN
	water_need
ON
	vegetable.id_vegetable = water_need.id_vegetable
LEFT JOIN
	stock
ON
	seed.id_seed = stock.id_seed
WHERE 1=1
    AND name_vegetable = ?
    AND variety_vegetable = ?
    AND latin_name_vegetable = ?
    AND origine_seed = ?
    AND price_seed BETWEEN ? AND ?
    AND quantity_stock = ?
    AND month_cultivation = ?
    AND month_gathering = ?
    AND floor_type = ?
    AND sun_need = ?
    AND water_need = ?;