# Live-Rate AI CLI Currency Converter

A lightweight, secure, and fast Command-Line Interface (CLI) currency converter written in C++. It communicates directly with the ExchangeRate-API via native Windows PowerShell telemetry to fetch real-time conversion matrices and generates automated AI-driven macroeconomic risk and volatility summaries for your transactions.

## 🚀 Features
- **Real-Time API Telemetry:** Fetches precise, live mid-market conversion data.
- **Automated AI Financial Insights:** Evaluates conversion directions and yields an instant volatility risk report.
- **Continuous Execution Loop:** Allows processing multiple currency conversions consecutively without restarting the application or re-entering the API key.
- **Hardened Security:** Built-in validation algorithms check currency formats and sanitize inputs to eliminate shell injection vulnerabilities.
- **Zero Heavy Dependencies:** Avoids massive external HTTP or JSON parsing frameworks by utilizing native Windows tools and resilient string parsing.

## 🛠️ Requirements & Prerequisites
- **Operating System:** Windows 10 / 11
- **Compiler:** `g++` (MinGW / GCC) 
- **Network:** Active internet connection (for PowerShell `Invoke-WebRequest` streams)
- **API Key:** A valid free or premium API key from [ExchangeRate-API](https://www.exchangerate-api.com/)

## 📂 Project Structure
```text
convert/
├── api.cpp             # Cleaned C++ source code containing core operational logic
├── CMakeLists.txt      # Project build metadata configuration (for IDE environments)
└── README.md           # Documentation file
```

⚙️ Compilation & Execution
Follow these precise terminal steps to compile and run the utility natively via Windows PowerShell:

1. Open Terminal and Navigate to Project Location
2. 
Open PowerShell and point your terminal context to your project folder:
```BASH
cd "C:\Users\YOUR_USERNAME\OneDrive\Desktop\convert"
```
2. Compile the Binary
   ```VG
    Compile the source using g++. Ensure you pass the file path precisely (accounting for potential hidden file extensions):
    ```
PowerShell

g++ api.cpp -o currency_app.exe

3. Run the Application
```
Launch the standalone executable binary:

PowerShell

.\currency_app.exe
```
📊 Sample Walkthrough
API Authentication: Provide your ExchangeRate-API token string at startup.

Transaction Mapping: Provide 3-letter standard ISO currency denominations (e.g., Base: USD -> Target: INR).

Quantum Input: Provide a numeric valuation total to calculate.

Interactive Prompt: Once output is printed, respond with Y to evaluate another pair or N to terminate.

🔒 Security Context
The software isolates raw inputs through an alphanumeric 3-character format gate (isValidCurrencyCode) and screens the API Key stream via token filter masks (find_first_of) before shipping strings to system command matrices, defending your workstation execution parameters against malicious shell manipulations.

