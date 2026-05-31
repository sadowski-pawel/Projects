package ui;


import config.GameAssets.BoardType;
import config.GameAssets.cell;
import java.awt.*;
import javax.swing.JPanel;
import model.Board;

public class BoardPanel extends JPanel{
    private Board board;
    public int cellSize = 40;
    public BoardType typ;
    boolean showShips = true;

    public BoardPanel(){
        setPreferredSize(new Dimension(450, 450));
        setBackground(Color.WHITE);
    }
    
    public void setBoard(Board board) {
        this.board = board;
    }

    public Board getBoard() {
        return board;
    }
    
    
    public void setBoardType(BoardType typ){
        this.typ = typ;
    }
    public BoardType getBoardType(){
        return typ;
    }

    public void setShowShips(boolean showShips) {
        this.showShips = showShips;
    }
    
    
    
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        
        if (board == null) return;
        cell[][] cells = board.getCells();
        
        for(int i=0; i < 10; i++){
            for(int j=0; j < 10; j++){
                g.setColor(Color.BLACK);
                g.drawRect(i * cellSize, j * cellSize, cellSize, cellSize);
                
                switch(cells[i][j]){

                    case SHIP ->{
                        if(showShips){
                            g.setColor(Color.BLUE);
                            g.fillRect(i * cellSize, j * cellSize, cellSize, cellSize);
                        }
                    }
                    
                    case HIT ->{
                        g.setColor(Color.RED);
                        g.fillRect(i * cellSize, j * cellSize, cellSize, cellSize);
                    }
                    case MISS ->{
                        g.setColor(Color.GRAY);
                        g.fillRect(i * cellSize, j * cellSize, cellSize, cellSize);
                    }
                }
            }
        }
    }
    
}
