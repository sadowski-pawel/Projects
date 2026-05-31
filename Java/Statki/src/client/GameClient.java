package client;

import java.io.*;
import java.net.*;
import start.Game;
import config.GameAssets.GamePhase;
import javax.swing.JOptionPane;

class GameCielntThread extends Thread{
    public GameClient gameClient;
    
    
    public GameCielntThread(GameClient gameClient){
        this.gameClient = gameClient;
    }
    
    @Override
    public void run() {
        try {
            String msg;
            while ((msg = gameClient.getIn().readLine()) != null) {
                System.out.println("[Sieć] Odebrano: " + msg);

                String[] tokens = msg.split(";");
                String command = tokens[0];

                switch (command) {
                    case "START":
                        String turnInfo = tokens[1];
                            if (turnInfo.equals("YOUR_TURN")) {
                                gameClient.getGame().setGamePhase(GamePhase.PLAYER_TURN);
                                ShowMessage( "Gra wystartowała! Twój ruch.");
                            } else {
                                gameClient.getGame().setGamePhase(GamePhase.ENEMY_TURN);
                                ShowMessage("Gra wystartowała. Czekaj na ruch przeciwnika.");
                            }
                            gameClient.getGame().repaint();
                        break;

                    case "ENEMY_STRIKE":
                        int enemyCol = Integer.parseInt(tokens[1]);
                        int enemyRow = Integer.parseInt(tokens[2]);

                            boolean hit = gameClient.getGame().getLocalPlayer().makeStrike(
                                    gameClient.getGame().getLocalPlayer().getOwnBoard(), enemyCol, enemyRow);
                            gameClient.getGame().repaint();

                            String result = hit ? "HIT" : "MISS";
                            if (hit) {
                                gameClient.getGame().getLocalPlayer().getOwnBoard().markHit(enemyCol, enemyRow);
                            }
                            gameClient.send("STRIKE_RESULT;" + enemyCol + ";" + enemyRow + ";" + result);

                            if (gameClient.getGame().isGameOver(gameClient.getGame().getLocalPlayer().getOwnBoard())) {
                                gameClient.send("I_AM_LOSER");
                                ShowMessage( "Przegrałeś wszystkie twoje statki zostały zniszczone");
                                gameClient.getGame().dispose();
                            }

                            if (!hit) {
                                gameClient.getGame().setGamePhase(GamePhase.PLAYER_TURN);
                            }
                        break;

                    case "YOUR_STRIKE_RESULT":
                        int myCol = Integer.parseInt(tokens[1]);
                        int myRow = Integer.parseInt(tokens[2]);
                        String outcome = tokens[3]; 

                        javax.swing.SwingUtilities.invokeLater(() -> {
                            if (outcome.equals("HIT")) {
                                gameClient.getGame().getEnemyPlayer().getOwnBoard().markHit(myCol, myRow);
                                gameClient.getGame().setGamePhase(GamePhase.PLAYER_TURN);
                            } else {
                                gameClient.getGame().getEnemyPlayer().getOwnBoard().markMiss(myCol, myRow);
                                gameClient.getGame().setGamePhase(GamePhase.ENEMY_TURN);
                            }
                            gameClient.getGame().repaint();
                        });
                        break;

                    case "OPPONENT_DISCONNECTED":
                        if (gameClient.getGame().getGamePhase() != GamePhase.GAME_OVER) {
                            javax.swing.SwingUtilities.invokeLater(() -> {
                                ShowMessage( "Przeciwnik uciekł! Wygrywasz walkowerem.");
                                gameClient.getGame().dispose();
                            });
                        }
                        return;

                    case "VICTORY":
                        javax.swing.SwingUtilities.invokeLater(() -> {
                            ShowMessage("Zwyciężyłeś zniszczyłeś wszystkei statki!");
                            gameClient.getGame().dispose();
                        });
                        return;
                }
            }
        } catch (IOException e) {
            System.out.println("Połączenie sieciowe przerwane: " + e.getMessage());
        } finally {
            gameClient.closeConnection();
        }
    }
    
    
    private void ShowMessage(String message){
        JOptionPane.showMessageDialog(gameClient.getGame(), message);
    }
    
    
}


public class GameClient {
    private Game game;
    private static final String SERVER_IP = "localhost";
    private static final int PORT = 5555;

    private Socket socket;
    private PrintWriter out;
    private BufferedReader in;

    public Game getGame() {
        return game;
    }

    public static String getSERVER_IP() {
        return SERVER_IP;
    }

    public static int getPORT() {
        return PORT;
    }

    public Socket getSocket() {
        return socket;
    }

    public PrintWriter getOut() {
        return out;
    }

    public BufferedReader getIn() {
        return in;
    }

    public GameClient(Game game) {
        this.game = game;
        try {
            this.socket = new Socket(SERVER_IP, PORT);
            this.out = new PrintWriter(socket.getOutputStream(), true);
            this.in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            System.out.println("Połączono z serwerem gry!");
        } catch (IOException e) {
            System.err.println("Błąd podczas łączenia z serwerem: " + e.getMessage());
        }
    }

    public void send(String message) {
        if (out != null) {
            out.println(message);
            System.out.println("[Sieć] Wysłano: " + message);
        }
    }

    public void startListening() {
        if (in == null) {
            return;
        }
        new GameCielntThread(this).start();
    }

    public void closeConnection() {
        try {
            if (socket != null) {
                socket.close();
            }
        } catch (IOException ignored) {}
    }
}