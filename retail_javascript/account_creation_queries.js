window.onload = function() {
    console.log("Window loaded, adding event listener to the form...");

    document.getElementById("creation_form").addEventListener("submit", function(event) {
        event.preventDefault(); // Prevent the default form submission

        const emailInput = document.getElementById("email_customer");
        const passwordInput = document.getElementById("password_customer");

        // Get the values
        const email = emailInput.value.trim(); // Trim leading/trailing spaces
        const password = passwordInput.value;
        let errorMessages = [];

        // Logging the values to debug
        console.log("Email entered (trimmed):", email);
        console.log("Password entered (raw):", password);

        // Validate email format
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        if (!emailRegex.test(email)) {
            console.log("Email validation failed for:", email);
            errorMessages.push('Invalid email format.');
        } else {
            console.log("Email validation passed for:", email);
        }

        // Validate password format
        const passwordRegex = /^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&,;:/!§])[A-Za-z\d@$!%*?&,;:/!§]{8,}$/;
        if (!passwordRegex.test(password)) {
            console.log("Password validation failed for:", password);
            errorMessages.push("Invalid password format. It must contain at least 8 characters, including uppercase, lowercase, a number, and a special character.");
        } else {
            console.log("Password validation passed for:", password);
        }

        // Display error messages if any validation failed
        if (errorMessages.length > 0) {
            alert(errorMessages.join("\n"));
            return; // Exit early if there are validation errors
        }

        // Form submission logic here...
        console.log("No validation errors. Proceeding with form submission.");

        // Create a URL-encoded string from the form data
        const formData = new URLSearchParams(new FormData(event.target)).toString();
        console.log("URL-encoded form data ready to be sent:", formData);

        // Sending the URL-encoded data
        fetch('http://localhost:8443/account_creation', {
            method: 'POST',
            body: formData,
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
            },
        })
        .then(response => {
            console.log("Response status:", response.status);
            return response.text(); // Return raw text to check for errors
        })
        .then(rawText => {
            console.log("Raw response text:", rawText);

            let responseData;
            let duplicateEntryMessage = null;

            // Vérifiez si la réponse contient un JSON valide suivi d'un message d'erreur
            try {
                // Si le JSON est bien formé, essayez de le parser
                const jsonPart = rawText.split("\n")[0]; // Sépare la première ligne, qui devrait être le JSON
                responseData = JSON.parse(jsonPart);
                console.log("Parsed JSON:", responseData);
                
                // Vérifiez s'il y a une ligne supplémentaire contenant un message d'erreur
                const errorPart = rawText.split("\n")[1];
                if (errorPart && errorPart.includes("Duplicate entry")) {
                    duplicateEntryMessage = errorPart;
                }
            } catch (parseError) {
                console.error("Error parsing JSON:", parseError);
                document.getElementById('results').innerHTML = '<p>Error parsing response data.</p>';
                return; // Sortir si le parsing échoue
            }

            // Gestion des messages de réponse serveur
            if (duplicateEntryMessage) {
                alert("Error: This account already exists.");
            } else if (responseData.message === "Success") {
                alert("Account creation OK! You can now connect to your account.");
            } else {
                document.getElementById('results').innerHTML = `<p>Server message: ${responseData.message}</p>`;
            }
        })
        .catch(error => {
            console.error("Error during fetch:", error);
            document.getElementById('results').innerHTML = `<p>An error occurred: ${error.message}</p>`;
        });
    });
};

