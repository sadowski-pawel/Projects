package model;

import config.GameAssets;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;
import javax.swing.JOptionPane;
import start.Game;



class Point {
    private int col;
    private int row;

    public Point(int col, int row) {
        this.col = col;
        this.row = row;
    }

    public int getCol() {
        return col;
    }

    public int getRow() {
        return row;
    }
}

public class ComputerPlayer extends Player {
    private Game game;
    private BotThread LogicBot;
    private Set<Point> shots = new HashSet<>();
    
    public ComputerPlayer(Game game,String name) {
        this.game = game;
        super(name);
    }

    public Game getGame() {
        return game;
    }
    
    public void  placeShipsRandomly(){
        Random rand = new java.util.Random();
        for (Ship i : this.getShips()) {
            boolean success = false;
            
            while (!success) {
                int col = rand.nextInt(10);
                int row = rand.nextInt(10);
                int rotation = rand.nextInt(2); 
                
                if (getOwnBoard().canPlace(col, row, i.getSize(), rotation) && 
                    getOwnBoard().canPlaceNoCollision(col, row, i.getSize(), rotation)) {

                    getOwnBoard().placeShip(col, row, i.getSize(), rotation);
                    i.setPlaced(); 
                    success = true;
                }
            }
        }
    }
    
    public void startGame(){
        new BotThread(this,"AI").start();
    }
    
    
    @Override
    public boolean makeStrike(Board enemyBoard, int col, int row) {

        int x, y;
        Point p;
        Random rand = new Random();

        do {
            x = rand.nextInt(10);
            y = rand.nextInt(10);
            p = new Point(x, y);
        } while (shots.contains(p));

        shots.add(p);

        return enemyBoard.strike(x, y);
    }
}

class BotThread extends Thread{
    ComputerPlayer computerData;

    public BotThread(ComputerPlayer computerData, String name) {
        super(name);
        this.computerData = computerData;
    }
    
    @Override
    public void run(){
        Random rand = new Random();
        while(true){
            if(computerData.getGame().getGamePhase() == GameAssets.GamePhase.ENEMY_TURN){
                try {
                    Thread.sleep(1000);
                    if(computerData.makeStrike(computerData.getGame().getLocalPlayer().getOwnBoard(), rand.nextInt(10), rand.nextInt(10)))
                        computerData.getGame().setGamePhase(GameAssets.GamePhase.ENEMY_TURN);
                    else
                        computerData.getGame().setGamePhase(GameAssets.GamePhase.PLAYER_TURN);
                    computerData.getGame().repaint();
                    if(computerData.getGame().isGameOver(computerData.getOwnBoard())){
                        computerData.getGame().Victory("Zwyciężyłeś zniszczyłeś wszystkei statki!");
                        computerData.getGame().dispose();
                    }else if(computerData.getGame().isGameOver(computerData.getGame().getLocalPlayer().getOwnBoard())){
                        computerData.getGame().Victory("Przegrałeś komputer cię pokonał");
                        computerData.getGame().dispose();
                    }
                } catch (InterruptedException ex) {
                    System.out.print(ex);
                }

            }
        }
    }
}