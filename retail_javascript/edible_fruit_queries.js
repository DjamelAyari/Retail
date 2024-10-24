document.getElementById("search_form").addEventListener("submit", 
    function(event)
    {
            var name_fruit = document.getElementById("name_fruit");
            var variety_fruit = document.getElementById("variety_fruit");
            var latin_name_fruit = document.getElementById("latin_name_fruit");
            var origine_edible = document.getElementById("origine_edible");
            var price_edible = document.getElementById("price_edible");
            var quantity_stock = document.getElementById("quantity_stock");
            var month_gathering = document.getElementById("month_gathering");

            if (name_fruit.value === "")
            {
                    name_fruit.value = "NULL";
            }
            if (variety_fruit.value === "")
            {
                    variety_fruit.value = "NULL";
            }
            if (latin_name_fruit.value === "")
            {
                    latin_name_fruit.value = "NULL";
            }
            if (origine_edible.value === "")
            {
                    origine_edible.value = "NULL";
            }
            if (price_edible.value === "")
            {
                    price_edible.value = "NULL";
            }
            if (quantity_stock.value === "")
            {
                    quantity_stock.value = "NULL";
            }
            if (month_gathering.value === "NULL")
            {
                    month_gathering.value = "NULL";
            }
    });

    // Mappage des images des fruits
    const fruitImages = {
    "apple": "../retail_html/apple.jpg",
    "banana": "../retail_html/banana.jpg",
    "orange": "../retail_html/orange.jpg",
    // Ajoute d'autres fruits ici
    };

    document.getElementById("search_form").addEventListener("submit", function(event) {
        event.preventDefault(); // Empêche le rechargement de la page
        console.log("Form submitted");
  
        const queryParams = new URLSearchParams(new FormData(event.target)).toString();
        console.log("Query Params:", queryParams);
    
        fetch(`http://localhost:8443/edible_fruit?${queryParams}`)
            .then(response => response.json())
            .then(data => {
                console.log("Data received from server:", data);
                const resultsDiv = document.getElementById('results');
                resultsDiv.innerHTML = ''; // Effacer les anciens résultats
    
                if (data.length === 0) {
                    resultsDiv.innerHTML = '<p>No results found.</p>';
                } else {
                    // Charger le modèle HTML
                    fetch('../retail_html/result_edible_fruit_template.html')
                        .then(response => response.text())
                        .then(templateHTML => {
                            data.forEach(item => {
                                const row = document.createElement('div');
                                row.innerHTML = templateHTML; // Injecte le modèle dans le div
                                
                                // Remplir les données
                                row.querySelector('.name_fruit').textContent = item.name_fruit;
                                row.querySelector('.variety_fruit').textContent = item.variety_fruit;
                                row.querySelector('.latin_name_fruit').textContent = item.latin_name_fruit;
                                row.querySelector('.origine_edible').textContent = item.origine_edible;
                                row.querySelector('.price_edible').textContent = item.price_edible;
                                row.querySelector('.quantity_stock').textContent = item.quantity_stock;
                                row.querySelector('.month_gathering').textContent = item.month_gathering;
                                
                                const imageUrl = fruitImages[item.name_fruit.toLowerCase()] || '../retail_html/default.jpg'; // Image par défaut si fruit non trouvé
                                row.querySelector('.fruit_image').src = imageUrl; // Met à jour la source de l'image

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
    

    