if (window.location.pathname.includes('seed_fruit.html')) {
// This script will automatically run when you reach edible.html
window.addEventListener('DOMContentLoaded', function() {
    console.log("Plant Page Loaded");

    // Call function to fetch data from the server when the page loads
    fetchDataFromServer();
});

// Function to fetch data from the server
function fetchDataFromServer() {
    // Send a request to the server to fetch all the data
    fetch('http://localhost:8443/seed_fruit')  // Replace with your actual endpoint
        .then(response => response.json())  // Assuming the server returns JSON data
        .then(data => {
            console.log("Data received from server:", data);
            const resultsDiv = document.getElementById('results');
            resultsDiv.innerHTML = ''; // Clear previous results

            if (data.length === 0) {
                resultsDiv.innerHTML = '<p>No results found.</p>';
            } else {
                // Load HTML template
                fetch('../retail_html/result_seed_fruit_template.html')
                    .then(response => response.text())
                    .then(templateHTML => {
                        data.forEach(item => {
                            const row = document.createElement('div');
                            row.innerHTML = templateHTML; // Inject the template HTML

                            // Populate the data
                            row.querySelector('.name_fruit').textContent = item.name_fruit;
                            row.querySelector('.variety_fruit').textContent = item.variety_fruit;
                            row.querySelector('.latin_name_fruit').textContent = item.latin_name_fruit;
                            row.querySelector('.origine_seed').textContent = item.origine_seed;
                            row.querySelector('.price_seed').textContent = item.price_seed;
                            row.querySelector('.quantity_stock').textContent = item.quantity_stock;
                            row.querySelector('.month_gathering').textContent = item.month_gathering;
                            row.querySelector('.month_cultivation').textContent = item.month_cultivation;
                            row.querySelector('.floor_type').textContent = item.floor_type;
                            row.querySelector('.quantity_sun_need').textContent = item.quantity_sun_need;
                            row.querySelector('.quantity_water_need').textContent = item.quantity_water_need;

                            /*const imageUrl = fruitImages[item.name_fruit.toLowerCase()] || '../retail_html/default.jpg'; // Default image if not found
                            row.querySelector('.fruit_image').src = imageUrl; // Update the image source*/

                            resultsDiv.appendChild(row); // Add the row to the results container
                        });
                    })
                    .catch(error => {
                        console.error('Error loading HTML template:', error);
                    });
            }
        })
        .catch(error => {
            console.error('Error fetching data:', error);
        });
}
}
