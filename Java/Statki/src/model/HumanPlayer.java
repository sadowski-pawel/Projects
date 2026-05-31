package model;


public class HumanPlayer extends Player{
    
    public HumanPlayer(String name) {
        super(name);
    }

    @Override
    public boolean makeStrike(Board enemyBoard,int col,int row) {
        return enemyBoard.strike(col, row);
    }
    
}
