package server;

import java.io.*;
import java.net.*;
import java.util.HashSet;
import java.util.Set;

public class Server {
    private static final int PORT = 5555; 

    public static void main(String[] args) {
        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("--- SERWER URUCHOMIONY na porcie " + PORT + " ---");


            while (true) {
                System.out.println("[Serwer] Czekam na Gracza 1...");
                Socket s1 = serverSocket.accept();
                System.out.println("[Serwer] Gracz 1 połączony");
                ClientHandler p1 = new ClientHandler(s1);


                System.out.println("[Serwer] Czekam na Gracza 2");
                Socket s2 = serverSocket.accept();
                System.out.println("[Serwer] Gracz 2 połączony");
                ClientHandler p2 = new ClientHandler(s2);


                p1.setOpponent(p2);
                p2.setOpponent(p1);

                p1.start(); 
                p2.start(); 

                System.out.println(">>> Pomyślnie stworzono pokój dla Gracza 1 i Gracza 2. Oczekiwanie na rozstawienie statków... <<<");
            }
        } catch (IOException e) {
            System.err.println("Błąd krytyczny serwera: " + e.getMessage());
        }
    }
}