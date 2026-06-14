package pl.sadowski.stockflow.service;

import domain.Portfolio;
import domain.Stock;
import domain.StockHolding;
import org.springframework.stereotype.Service;

@Service
public class PortfolioService {
    private final Portfolio portfolio = new Portfolio();

    public void buyStock(int id, int quantity) {

        for (StockHolding holding : portfolio.getStocks()) {
            if (holding.getStock().getId() == id) {
                holding.setQuantity(holding.getQuantity() + quantity);
                return;
            }
        }

        Stock stock = new Stock(id, "UNKNOWN", 0);
        portfolio.getStocks().add(new StockHolding(stock, quantity));
    }

    public void sellStock(int id, int quantity) {

        for (StockHolding holding : portfolio.getStocks()) {

            if (holding.getStock().getId() == id) {

                int currentQuantity = holding.getQuantity();
                int quantityToSell = currentQuantity - quantity;

                if (quantityToSell < 0)
                    throw new IllegalArgumentException("Not enough stocks to sell");

                if (quantityToSell == 0) {
                    portfolio.getStocks().remove(holding);
                } else {
                    holding.setQuantity(quantityToSell);
                }
                return;
            }
        }
        throw new IllegalArgumentException("Stock not found in portfolio");
    }

    public String displayPortfolio() {
        String output = "";
        for (StockHolding holding : portfolio.getStocks()) {
            output += "Stock: " + holding.getStock() + "\n";
        }
        return output;
    }
}
