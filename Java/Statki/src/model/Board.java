package model;

import config.GameAssets.cell;

public class Board {
    public cell[][] cells = new cell[10][10];
    
    public Board(){
        init();
    }
    
    public void init(){
        for(int i=0; i < 10; i++){
            for(int j=0; j < 10; j++){
                markEmpty(i,j);
            }
        }
    }
    
    public cell[][] getCells() {
        return cells;
    }
    
    
    public boolean canPlace(int col, int row, int size, int rotation){

        switch(rotation){

            case 0: 
                return col + size <= 10;

            case 1: 
                return row + size <= 10;

            case 2: 
                return col - (size - 1) >= 0;

            case 3: 
                return row - (size - 1) >= 0;
        }

        return false;
    }
    
    public boolean  canPlaceNoCollision(int col, int row,int size,int rotation){
        
        switch(rotation){

            case 0: 
                for(int i = 0; i < size; i++){
                    if(cells[col + i][row] == cell.SHIP) {
                        return false;
                    }
                }
                break;

            case 1: 
                for(int i = 0; i < size; i++){
                    if(cells[col][row + i] == cell.SHIP) {
                        return false;
                    }
                }
                break;

            case 2:
                for(int i = 0; i < size; i++){
                    if(cells[col - i][row] == cell.SHIP) {
                        return false;
                    }
                }
                break;

            case 3: 
                for(int i = 0; i < size; i++){
                    if(cells[col][row - i] == cell.SHIP) {
                        return false;
                    }
                }
                break;
        }

        return true;
    }
    
    public void placeShip(int col, int row,int size,int rotation){

        switch(rotation){

            case 0: // →
                for(int i = 0; i < size; i++){
                    markShip(col + i, row);
                }
                break;

            case 1: // ↓
                for(int i = 0; i < size; i++){
                    markShip(col, row + i);
                }
                break;

            case 2: // ←
                for(int i = 0; i <size; i++){
                    markShip(col - i, row);
                }
                break;

            case 3: // ↑
                for(int i = 0; i < size; i++){
                    markShip(col, row - i);
                }
                break;
        }

    }
    public boolean strike(int col, int row) {
        if (cells[col][row] == cell.SHIP) {
            cells[col][row] = cell.HIT;
            return true;
        } 
        else if (cells[col][row] == cell.HIT || cells[col][row] == cell.MISS) {
            return true;
        }

        cells[col][row] = cell.MISS; 
        return false;
    }
    
    public void markHit(int col, int row) {
        if (cells[col][row] == cell.EMPTY) {
            cells[col][row] = cell.HIT;
        }
    }

    public void markMiss(int col, int row) {
        if (cells[col][row] == cell.EMPTY) {
            cells[col][row] = cell.MISS;
        }
    }
    public void markShip(int col,int row){
        cells[col][row] = cell.SHIP;
    }
   public void markEmpty(int col,int row){
        cells[col][row] = cell.EMPTY;
    }
    
    public String toFile() {
        StringBuilder file = new StringBuilder();

        for (cell[] row : getCells() ) {
            for (cell col : row) {
                switch(col){
                    case SHIP->file.append("S");
                    case EMPTY->file.append(".");
                    default -> file.append(".");
                }
            }
            file.append("\n");
        }

        return file.toString();
    }
}
