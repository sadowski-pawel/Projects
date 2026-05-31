package config;

public class GameAssets {
    public enum mode{
        VS_COMPUTER,
        VS_HUMAN
    }
    
    
    public enum BoardType {
        PLAYER,
        ENEMY
    }
    
    public enum cell{
        SHIP,
        HIT,
        MISS,
        EMPTY,
    }
    
    public static String[] rotationStr = {
      "Rotation: RIGHT",
      "Rotation: DOWN",
      "Rotation: LEFT",
      "Rotation: TOP",
    };
    
    
    public enum GamePhase {
        PLACING_SHIPS,
        WAIT_TURN,
        PLAYER_TURN,
        ENEMY_TURN,
        GAME_OVER
    }
}
