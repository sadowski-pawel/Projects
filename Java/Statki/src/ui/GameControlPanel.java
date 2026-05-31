package ui;

import java.awt.Dimension;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class GameControlPanel extends JPanel {
    public JButton destroyer;
    public JButton submarine;
    public JButton submarine2;
    public JButton battleship;
    public JButton start;
    public JButton importBoard;
    public JButton exportBoard;

    public JLabel text;
    public JLabel shipType;
    public JLabel shipRotation;
    

    
    
    public GameControlPanel() {

        setPreferredSize(new Dimension(220, 500));

        setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));

        setBorder(
                BorderFactory.createEmptyBorder(
                        20,
                        20,
                        20,
                        20
                )
        );

        destroyer = new JButton("Destroyer");
        submarine = new JButton("Submarine");
        submarine2 = new JButton("Submarine");
        battleship = new JButton("Battleship");
        importBoard = new JButton("Import");
        exportBoard = new JButton("Export");
        
        
        text = new JLabel("Choosen type ship : ???");
        shipType = new JLabel("");
        shipRotation = new JLabel();
        
        start = new JButton("Let's go");
        

        add(destroyer);
        add(submarine);
        add(submarine2);
        add(battleship);
        
        
        
        
        add(text);
        add(shipType);
        add(shipRotation);
        add(start);
        add(importBoard);
        add(exportBoard);
    }
}
