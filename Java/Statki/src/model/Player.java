package model;

public abstract class Player {
    private String name;
    protected Board ownBoard = new Board();
    public Ship[] ownships = {
        new Ship("Destroyer", 3),
        new Ship("Submarine 1",2),
        new Ship("Submarine 2", 2),
        new Ship("Battleship", 4)
    };
    
    
    public Ship getShip(int index){
        return ownships[index];
    }
   public Ship[] getShips(){
        return ownships;
    }

    public Player(String name) {
        this.name = name;
    }
    public void setBoard(Board ownBoard){
        this.ownBoard = ownBoard;
    }
    public Board getOwnBoard(){
        return ownBoard;
    }
    

    
    public boolean CheckShipPlaced(){
        for(Ship s : ownships){
            if(s.getSize() > 0)
                return true;
        }
        return false;
    }
    
    
    public abstract boolean makeStrike(Board enemyBoard,int col,int row);

}
