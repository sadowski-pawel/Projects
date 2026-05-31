package start;

import client.GameClient;
import config.GameAssets;
import java.awt.BorderLayout;
import java.awt.Dimension;
import javax.swing.JFrame;
import javax.swing.JPanel;
import model.*;
import config.GameAssets.*;
import javax.swing.JOptionPane;
import model.HumanPlayer;
import ui.*;

public class Game extends JFrame {
    
    private Player localPlayer;
    private Player enemyPlayer;
    
    public GameClient client;
    private BoardPanel ownPanel;
    private BoardPanel enemyPanel;
    private GameControlPanel gameControlPanel;
    private HandlingEvent handlingEvent;
    private GamePhase gamePhase;
    private mode mode;
    
    

    public Game(GameAssets.mode m) {
        
        this.mode = m;
        gamePhase = GamePhase.PLACING_SHIPS;
        
        ownPanel = new BoardPanel();
        enemyPanel = new BoardPanel();
        gameControlPanel = new GameControlPanel();
        handlingEvent = new HandlingEvent(this);
        
        this.localPlayer = new HumanPlayer("Ja");
        if(m == mode.VS_HUMAN){
            this.enemyPlayer = new HumanPlayer("Przeciwnik");
            System.out.println("Uruchamianie trybu sieciowego...");
            this.client = new GameClient(this);
            this.client.startListening();
        }
        else{
            ComputerPlayer botDate = new ComputerPlayer(this,"Komputer");
            botDate.placeShipsRandomly();
            enemyPlayer = botDate;
            enemyPanel.setShowShips(false);
        }
        
        ownPanel.setBoard(localPlayer.getOwnBoard());
        ownPanel.setBoardType(GameAssets.BoardType.PLAYER);
        enemyPanel.setBoard(enemyPlayer.getOwnBoard());
        enemyPanel.setBoardType(GameAssets.BoardType.ENEMY);
        
        
        init();

    }
    
    
    public BoardPanel getOwnPanel(){
        return ownPanel;
    }
    public BoardPanel getEnemyPanel(){
        return enemyPanel;
    }
    
    public GameControlPanel getchoosenShipPanel(){
        return gameControlPanel;
    }
    public Player getLocalPlayer(){
        return localPlayer;
    }
    public Player getEnemyPlayer(){
        return enemyPlayer;
    }
    
    public  synchronized  GamePhase getGamePhase() {
        return gamePhase;
    }
    
    public mode getMode(){
        return mode;
    }
    
    public synchronized  void setGamePhase(GamePhase gamePhase) {
        this.gamePhase = gamePhase;
    }
    
    
    private void init() {
        setTitle("Battleship");
        setSize(900, 500);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        setResizable(false);
        
        ownPanel.setPreferredSize(new Dimension(400, 400));
        enemyPanel.setPreferredSize(new Dimension(400, 400));
        
        add(ownPanel, BorderLayout.CENTER);
        
        JPanel right = new JPanel(new BorderLayout());
        right.add(gameControlPanel, BorderLayout.NORTH);
        right.add(enemyPanel, BorderLayout.CENTER);
        
        add(right, BorderLayout.EAST);
        
        setLocationRelativeTo(null);
        
        gameControlPanel.battleship.addActionListener(handlingEvent);
        gameControlPanel.destroyer.addActionListener(handlingEvent);
        gameControlPanel.submarine.addActionListener(handlingEvent);
        gameControlPanel.submarine2.addActionListener(handlingEvent);
        enemyPanel.addMouseListener(handlingEvent);
        ownPanel.addMouseListener(handlingEvent);
        gameControlPanel.start.addActionListener(handlingEvent);
        gameControlPanel.importBoard.addActionListener(handlingEvent);
        gameControlPanel.exportBoard.addActionListener(handlingEvent);
        
        
        setVisible(true);
    }
    
    
    public boolean  isPlacedOver(){
        for(Ship i : localPlayer.getShips()){
            if(!i.getPlaced())
                return false;
        }
        return true;
    }
    
    
    public boolean isGameOver(Board ownBoard) {
        for (cell[] row : ownBoard.getCells()) {
            for (cell c : row) {
                if (c == cell.SHIP) {
                    return false;
                }
            }
        }
        gamePhase = GamePhase.GAME_OVER;
        return true;
    }
    
    public void Victory(String name){
        JOptionPane.showMessageDialog(this, name);
    }

}