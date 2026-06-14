package pl.sadowski.stockflow.controller;

import org.springframework.web.bind.annotation.*;
import pl.sadowski.stockflow.dto.BuyRequest;
import pl.sadowski.stockflow.dto.SellRequest;
import pl.sadowski.stockflow.service.PortfolioService;

@RestController
@RequestMapping("/portfolio")
public class PortfolioController {

    private final PortfolioService portfolioService;

    public PortfolioController(PortfolioService portfolioService) {
        this.portfolioService = portfolioService;
    }

    @PostMapping("/buy")
    public String buy(@RequestBody BuyRequest request) {

        portfolioService.buyStock(
                Integer.parseInt(request.getSymbol()),
                request.getQuantity()
        );

        System.out.println("Buy request: " + request.getSymbol() + " " + request.getQuantity());

        return "BUY executed";
    }

    @PostMapping("/sell")
    public String sell(@RequestBody SellRequest request) {

        portfolioService.sellStock(
                Integer.parseInt(request.getSymbol()),
                request.getQuantity()
        );

        return "SELL executed";
    }
    @GetMapping("/display")
    public String display() {
        return portfolioService.displayPortfolio();
    }

}