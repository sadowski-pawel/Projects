package domain;

import java.util.ArrayList;
import java.util.List;

public class Portfolio {
    private List<StockHolding> stocks;

    public Portfolio() {
        stocks = new ArrayList<StockHolding>();
    }

    public List<StockHolding> getStocks() {
        return stocks;
    }
}