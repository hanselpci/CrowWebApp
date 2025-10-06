document.addEventListener("DOMContentLoaded", () => {
  const num1Input = document.getElementById("num1");
  const num2Input = document.getElementById("num2");
  const calculateBtn = document.getElementById("calculate-btn");
  const resultElement = document.getElementById("result");
  const errorElement = document.getElementById("error-message");

  // Calculate sum when button is clicked
  calculateBtn.addEventListener("click", calculateSum);

  // Calculate sum when Enter key is pressed in either input
  num1Input.addEventListener("keypress", (e) => {
    if (e.key === "Enter") calculateSum();
  });

  num2Input.addEventListener("keypress", (e) => {
    if (e.key === "Enter") calculateSum();
  });

  // Function to calculate sum using API
  function calculateSum() {
    // Clear previous error
    errorElement.classList.remove("show");

    // Get input values
    const num1 = num1Input.value.trim();
    const num2 = num2Input.value.trim();

    // Validate inputs
    if (!num1 || !num2) {
      showError("Please enter both numbers");
      return;
    }

    if (isNaN(num1) || isNaN(num2)) {
      showError("Please enter valid numbers");
      return;
    }

    // Send request to API
    fetch("/api/add", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({ num1, num2 }),
    })
      .then((response) => {
        if (!response.ok) {
          return response.json().then((data) => {
            throw new Error(data.error || "Calculation failed");
          });
        }
        return response.json();
      })
      .then((data) => {
        // Display result
        resultElement.textContent = data.result;
      })
      .catch((error) => {
        // Show error message
        showError(error.message);
      });
  }

  // Helper function to show error messages
  function showError(message) {
    errorElement.textContent = message;
    errorElement.classList.add("show");

    // Hide error after 5 seconds
    setTimeout(() => {
      errorElement.classList.remove("show");
    }, 5000);
  }
});
