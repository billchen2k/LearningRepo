package io.billc.duckhunt;


import javax.swing.*;
import java.awt.*;

public class Main {

    public static void createRun(){
        JFrame frame = new JFrame("Duck Hunt");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JLabel label = new JLabel("Hello World");

        frame.getContentPane().add(label);
        frame.setPreferredSize(new Dimension(512, 512));
        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args) {
	// write your code here

        System.out.printf("Hello, I'm a duck.\n\n\n");
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createRun();
            }
        });
    }
}
