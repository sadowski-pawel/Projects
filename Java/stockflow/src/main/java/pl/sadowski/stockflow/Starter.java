package pl.sadowski.stockflow;

import domain.Portfolio;
import domain.Stock;
import domain.Transaction;
import domain.TransactionType;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;
import pl.sadowski.stockflow.service.PortfolioService;
import pl.sadowski.stockflow.service.TransactionService;

import java.time.LocalDate;

@Component
public class Starter implements CommandLineRunner {

    @Autowired
    private PortfolioService portfolioService;

    @Autowired
    private TransactionService transactionService;

    @Override
    public void run(String... args) {
        /*
            Portfolio portfolio = new Portfolio();
            Stock stock = new Stock(1,"AAPL", 20);

            portfolioService.buyStock(portfolio, stock, 10);
            portfolioService.displayPortfolio(portfolio);

            transactionService.save(
                    new Transaction(1,stock, TransactionType.BUY)
            );
            transactionService.DisplayTransactions();
        */
    }
}
