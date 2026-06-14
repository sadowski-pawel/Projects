StockFlow

Prototype Spring Boot application simulating a simple stock trading system.

Features
Buy stocks
Sell stocks
Manage portfolio in memory (no database yet)


📡 API Endpoints

🟢 Buy stock
POST /portfolio/buy

Request body:

{

  "symbol": "AAPL",
  
  "quantity": 10
  
}

🔴 Sell stock
POST /portfolio/sell

Request body:

{

  "symbol": "AAPL",
  
  "quantity": 5
  
}


📊 Get portfolio
GET /portfolio/display

Returns current stock holdings.



Notes

This project is for learning purposes and focuses on:

Spring Boot basics
REST API design
Service layer architecture
In-memory data handling
