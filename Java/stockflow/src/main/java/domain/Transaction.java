package domain;


import java.time.LocalDate;



public class Transaction {
    private int id;
    private Stock stock;
    private TransactionType type;
    private LocalDate date;

    public Transaction(int id, Stock stock, TransactionType type) {
        this.id = id;
        this.stock = stock;
        this.type = type;
        this.date = LocalDate.now();
    }

    public StringBuilder display() {
        return new StringBuilder("ID: " + this.id + " | Stock: " + this.stock + " | Type: " + this.type);
    }
}
