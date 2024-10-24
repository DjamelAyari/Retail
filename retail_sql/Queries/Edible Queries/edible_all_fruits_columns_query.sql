SELECT
    name_fruit,
    variety_fruit,
    latin_name_fruit,
    origine_edible,
    price_edible,
    quantity_stock,
    month_gathering
FROM
    fruit
JOIN
    edible
ON
    fruit.id_fruit = edible.id_fruit
JOIN
    gathering
ON
    fruit.id_fruit = gathering.id_fruit
LEFT JOIN
    stock
ON
    edible.id_edible = stock.id_edible
WHERE 1=1
    AND (name_fruit = ? OR ? = '')
    AND (variety_fruit = ? OR ? = '')
    AND (latin_name_fruit = ? OR ? = '')
    AND (origine_edible = ? OR ? = '')
    AND (price_edible = ? OR ? < 0)
    AND (quantity_stock = ? OR ? < 0)
    AND (month_gathering = ? OR ? = '');

