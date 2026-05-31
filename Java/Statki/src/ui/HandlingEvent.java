package ui;

import java.awt.event.*;
import javax.swing.SwingUtilities;
import model.*;
import start.Game;
import config.GameAssets;
import config.GameAssets.*;
import java.io.*;
import java.util.Random;
import javax.swing.JOptionPane;

public class HandlingEvent implements MouseListener, ActionListener,WindowListener {

    int currentShip = -1;
    private int rolation = 0;
    Game game;

    public HandlingEvent(Game game) {
        this.game = game;
    }

    @Override
    public void mouseClicked(MouseEvent e) {
    }

    @Override
    public void mousePressed(MouseEvent e) {

        BoardPanel clickedPanel = null;

        if (e.getSource() == game.getOwnPanel()) {
            clickedPanel = game.getOwnPanel();
        } else if (e.getSource() == game.getEnemyPanel()) {
            clickedPanel = game.getEnemyPanel();
        } else {
            return;
        }

        int col = e.getX() / clickedPanel.cellSize;
        int row = e.getY() / clickedPanel.cellSize;

        if (clickedPanel.getBoardType() == GameAssets.BoardType.PLAYER && game.getGamePhase() == GameAssets.GamePhase.PLACING_SHIPS) {
            handleShipPlacement(clickedPanel, col, row, e);
        } else if (clickedPanel.getBoardType() == GameAssets.BoardType.ENEMY && game.getGamePhase() == GameAssets.GamePhase.PLAYER_TURN) {
            handleShipStrike(col, row);
        }
    }

    private void handleShipPlacement(BoardPanel panel, int col, int row, MouseEvent e) {

        if (panel.getBoardType() != GameAssets.BoardType.PLAYER) {
            return;
        }
        if (game.getLocalPlayer().getShip(currentShip).getPlaced()) {
            return;
        }

        if (currentShip == -1) {
            return;
        }

        if (SwingUtilities.isRightMouseButton(e)) {
            rolation = (rolation + 1) % 4;
            game.getchoosenShipPanel().shipRotation.setText(GameAssets.rotationStr[rolation]);
            System.out.println("-> Zmieniono rotację na: " + rolation);
            return;
        }

        if (SwingUtilities.isLeftMouseButton(e)) {

            Board board = panel.getBoard();
            Ship ship = game.getLocalPlayer().getShip(currentShip);

            if (ship == null) {
                return;
            }

            if (!board.canPlace(col, row, ship.getSize(), rolation)) {
                return;
            }

            if (!board.canPlaceNoCollision(col, row, ship.getSize(), rolation)) {
                return;
            }

            board.placeShip(col, row, ship.getSize(), rolation);

      
            game.getLocalPlayer().getShip(currentShip).setPlaced();
            game.repaint();
        }
    }

    private void handleShipStrike(int col, int row) {
        game.setGamePhase(config.GameAssets.GamePhase.ENEMY_TURN);
        if (game.getMode()== mode.VS_HUMAN) {
            game.client.send("STRIKE;" + col + ";" + row);
        }else{
            game.getLocalPlayer().makeStrike(game.getEnemyPlayer().getOwnBoard(), col, row);
            game.repaint();
        }

    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == game.getchoosenShipPanel().destroyer) {
            currentShip = 0;
            game.getchoosenShipPanel().shipType.setText(game.getLocalPlayer().getShip(0).getName());
            return;
        }
        if (e.getSource() == game.getchoosenShipPanel().submarine) {
            currentShip = 1;
            game.getchoosenShipPanel().shipType.setText(game.getLocalPlayer().getShip(1).getName());
            return;
        }
        if (e.getSource() == game.getchoosenShipPanel().submarine2) {
            currentShip = 2;
            game.getchoosenShipPanel().shipType.setText(game.getLocalPlayer().getShip(2).getName());
            return;
        }
        if (e.getSource() == game.getchoosenShipPanel().battleship) {
            currentShip = 3;
            game.getchoosenShipPanel().shipType.setText(game.getLocalPlayer().getShip(3).getName());
            return;
        }

        if (e.getSource() == game.getchoosenShipPanel().start) {
            if (game.isPlacedOver()) {
                game.setGamePhase(GameAssets.GamePhase.WAIT_TURN);
                if (game.getMode() == mode.VS_HUMAN) {
                    game.client.send("READY");
                } else {
                    if (game.getEnemyPlayer() instanceof ComputerPlayer) {
                        ComputerPlayer bot = (ComputerPlayer) game.getEnemyPlayer();

                        
                        if(new Random().nextBoolean()){
                            game.setGamePhase(GamePhase.PLAYER_TURN);
                            JOptionPane.showMessageDialog(game, "Gra wystartowała! Twój ruch.");
                        }
                        else{
                            game.setGamePhase(GamePhase.ENEMY_TURN);
                            JOptionPane.showMessageDialog(game,"Gra wystartowała! Ruch Komputera");
                        }
                        
                        bot.startGame();
                    }
                }
                game.getchoosenShipPanel().setVisible(false);
            } else {
                return;
            }
        }
        
        if (e.getSource() == game.getchoosenShipPanel().exportBoard) {
            ExportFile();
        }
        
        if(e.getSource() == game.getchoosenShipPanel().importBoard){
            try {
                BufferedReader in = new BufferedReader(
                        new InputStreamReader(
                                new FileInputStream("Plansza.csv")
                        ));
                String line ;
                int row = 0;
                while ((line = in.readLine()) != null){
                    for(int col=0; col < line.length(); col++){
                        switch(line.charAt(col)){
                            case 'S' -> game.getLocalPlayer().getOwnBoard().markShip(col, row);
                            case '.' -> game.getLocalPlayer().getOwnBoard().markEmpty(col, row);
                        }
                    }
                    row++;
                }
                in.close();
                game.repaint();
            } catch (FileNotFoundException ex) {
                System.out.println(ex);
            } catch (IOException ex) {
                System.getLogger(HandlingEvent.class.getName()).log(System.Logger.Level.ERROR, (String) null, ex);
            }
        }
    }
    
    private void ExportFile(){
        try {
                BufferedWriter out = new BufferedWriter(
                        new OutputStreamWriter(
                                new FileOutputStream("Plansza.csv")
                        )
                );

                out.write(game.getLocalPlayer().getOwnBoard().toFile());

                out.close();
                return;
                

            } catch (IOException ex) {
                System.out.println("ex");
        }
    }
    
    @Override
    public void windowClosing(WindowEvent e) {
        ExportFile();
    }
    
    @Override
    public void windowOpened(WindowEvent e) {}
    @Override
    public void windowClosed(WindowEvent e) {}
    @Override
    public void windowIconified(WindowEvent e) {}
    @Override
    public void windowDeiconified(WindowEvent e) {}
    @Override
    public void windowActivated(WindowEvent e) {}
    @Override
    public void windowDeactivated(WindowEvent e) {}
    @Override
    public void mouseReleased(MouseEvent e) {}
    @Override
    public void mouseEntered(MouseEvent e) {}
    @Override
    public void mouseExited(MouseEvent e) {}
}
