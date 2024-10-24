document.getElementById("search_form").addEventListener("submit", 
    function(event)
    {
            var name_vegetable = document.getElementById("name_vegetable");
            var variety_vegetable = document.getElementById("variety_vegetable");
            var latin_name_vegetable = document.getElementById("latin_name_vegetable");
            var origine_plant = document.getElementById("origine_plant");
            var price_plant = document.getElementById("price_plant");
            var quantity_stock = document.getElementById("quantity_stock");
            var month_gathering = document.getElementById("month_gathering");
            var month_cultivation = document.getElementById("month_cultivation");
            var floor_type = document.getElementById("floor_type");
            var quantity_sun_need = document.getElementById("quantity_sun_need");
            var quantity_water_need = document.getElementById("quantity_water_need");

            if (name_vegetable.value === "")
            {
                    name_vegetable.value = "NULL";
            }
            if (variety_vegetable.value === "")
            {
                    variety_vegetable.value = "NULL";
            }
            if (latin_name_vegetable.value === "")
            {
                    latin_name_vegetable.value = "NULL";
            }
            if (origine_plant.value === "")
            {
                    origine_plant.value = "NULL";
            }
            if (price_plant.value === "")
            {
                    price_plant.value = "NULL";
            }
            if (quantity_stock.value === "")
            {
                    quantity_stock.value = "NULL";
            }
            if (month_gathering.value === "NULL")
            {
                    month_gathering.value = "NULL";
            }
            if (month_cultivation.value === "NULL")
            {
                month_cultivation.value = "NULL";
            }
            if (floor_type.value === "NULL")
            {
                floor_type.value = "NULL";
            }
            if (quantity_sun_need.value === "NULL")
            {
                quantity_sun_need.value = "NULL";
            }
            if (quantity_water_need.value === "NULL")
            {
                quantity_water_need.value = "NULL";
            }
    });

    // Mappage des images des fruits
    /*const fruitImages = {
    "apple": "../retail_html/apple.jpg",
    "banana": "../retail_html/banana.jpg",
    "orange": "../retail_html/orange.jpg",
    // Ajoute d'autres fruits ici
    };*/

    document.getElementById("search_form").addEventListener("submit", function(event) {
        event.preventDefault(); // Empêche le rechargement de la page
        console.log("Form submitted");
  
        const queryParams = new URLSearchParams(new FormData(event.target)).toString();
        console.log("Query Params:", queryParams);
    
        fetch(`http://localhost:8443/plant_vegetable?${queryParams}`)
            .then(response => response.json())
            .then(data => {
                console.log("Data received from server:", data);
                const resultsDiv = document.getElementById('results');
                resultsDiv.innerHTML = ''; // Effacer les anciens résultats
    
                if (data.length === 0) {
                    resultsDiv.innerHTML = '<p>No results found.</p>';
                } else {
                    // Charger le modèle HTML
                    fetch('../retail_html/result_plant_vegetable_template.html')
                        .then(response => response.text())
                        .then(templateHTML => {
                            data.forEach(item => {
                                const row = document.createElement('div');
                                row.innerHTML = templateHTML; // Injecte le modèle dans le div
                                
                                // Remplir les données
                                row.querySelector('.name_vegetable').textContent = item.name_vegetable;
                                row.querySelector('.variety_vegetable').textContent = item.variety_vegetable;
                                row.querySelector('.latin_name_vegetable').textContent = item.latin_name_vegetable;
                                row.querySelector('.origine_plant').textContent = item.origine_plant;
                                row.querySelector('.price_plant').textContent = item.price_plant;
                                row.querySelector('.quantity_stock').textContent = item.quantity_stock;
                                row.querySelector('.month_gathering').textContent = item.month_gathering;
                                row.querySelector('.month_cultivation').textContent = item.month_cultivation;
                                row.querySelector('.floor_type').textContent = item.floor_type;
                                row.querySelector('.quantity_sun_need').textContent = item.quantity_sun_need;
                                row.querySelector('.quantity_water_need').textContent = item.quantity_water_need;
                                
                                /*const imageUrl = fruitImages[item.name_fruit.toLowerCase()] || '../retail_html/default.jpg'; // Image par défaut si fruit non trouvé
                                row.querySelector('.fruit_image').src = imageUrl; // Met à jour la source de l'image*/

                                resultsDiv.appendChild(row); // Ajoute le div au conteneur des résultats
                            });
                        })
                        .catch(error => {
                            console.error('Error loading HTML template:', error);
                        });
                }
            })
            .catch(error => {
                console.error("Error fetching data:", error);
            });
    });
    

    