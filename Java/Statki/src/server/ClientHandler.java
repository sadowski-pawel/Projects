package server;

import java.io.*;
import java.net.*;
import java.util.Random;

public class ClientHandler extends Thread {
    private Socket socket;
    private PrintWriter out;
    private BufferedReader in;
    private ClientHandler opponent;
    private boolean isFirstPlayer;
    private  boolean isReady = false;

    public void setIsReady(boolean isReady) {
        this.isReady = isReady;
    }
    
    
    public ClientHandler() {
        this.socket = null;
    }

    public ClientHandler(Socket socket) {
        this.socket = socket;
    }

    public void setOpponent(ClientHandler opponent) {
        this.opponent = opponent;
    }

    public void setFirstPlayer(boolean isFirstPlayer) {
        this.isFirstPlayer = isFirstPlayer;
    }

    public void send(String message) {
        if (out != null) {
            out.println(message);
        }
    }

@Override
public void run() {
    try {
        
        out = new PrintWriter(socket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(socket.getInputStream()));



        String message;
        
        while ((message = in.readLine()) != null) {
            System.out.println("[Serwer] Odebrano: " + message);
            
            if (opponent == null) continue;

            String[] tokens = message.split(";");
            String command = tokens[0];

            switch (command) {
                case "READY":
                    this.isReady = true;

                    if (opponent != null && opponent.isReady == true) {
                        System.out.println("[Serwer] OBAJ GOTOWI! Odpalam losowanie tury...");

                        boolean p1Starts = new Random().nextBoolean();
                        if (p1Starts) {
                            this.send("START;YOUR_TURN");
                            opponent.send("START;WAIT_TURN");
                        } else {
                            this.send("START;WAIT_TURN");
                            opponent.send("START;YOUR_TURN");
                        }
                    } else {
                        System.out.println("[Serwer] Drugi gracz jeszcze układa statki. Czekam...");
                    }
                    break;
                    

                case "STRIKE":
                    int col = Integer.parseInt(tokens[1]);
                    int row = Integer.parseInt(tokens[2]);
                    opponent.send("ENEMY_STRIKE;" + col + ";" + row);
                    break;

                case "STRIKE_RESULT":
                    int resCol = Integer.parseInt(tokens[1]);
                    int resRow = Integer.parseInt(tokens[2]);
                    String result = tokens[3]; 
                    opponent.send("YOUR_STRIKE_RESULT;" + resCol + ";" + resRow + ";" + result);
                    break;
                case "I_AM_LOSER":
                    if (opponent != null) {
                        opponent.send("VICTORY");
                    }
                default:
                    opponent.send(message);
                    break;
            }
        }

    } catch (IOException e) {
        System.out.println("Jeden z graczy się rozłączył.");
    } finally {
        if (opponent != null && opponent.socket.isConnected()) {
            opponent.send("OPPONENT_DISCONNECTED");
        }
        try { socket.close(); } catch (IOException ignored) {}

    }
}
    }
