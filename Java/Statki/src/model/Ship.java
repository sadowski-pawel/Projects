package model;

public class Ship {
    private String name;
    private int size;
    boolean isplaced = false;
    
    public Ship(String name,int size){
        this.name = name;
        this.size = size;
    }
    
    public String getName(){
        return name;
    }
    public int getSize(){
        return size;
    }
    public void setPlaced(){
        this.isplaced = true;
    }
    public boolean getPlaced(){
        return isplaced;
    }
}
