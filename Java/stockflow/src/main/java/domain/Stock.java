package domain;

public class Stock {
    private int id;
    private String symbol;
    private double price;

    public Stock(int id, String symbol, double price) {
        this.id = id;
        this.symbol = symbol;
        this.price = price;
    }

    public int getId() {
        return id;
    }
    public String getSymbol() {
        return symbol;
    }
    public double getPrice() {
        return price;
    }

    @Override
    public String toString() {
        return "Stock{" + "id=" + id + ", symbol=" + symbol + ", price=" + price + '}';
    }

}