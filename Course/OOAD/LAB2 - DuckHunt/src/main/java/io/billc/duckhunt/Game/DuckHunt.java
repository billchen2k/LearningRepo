package io.billc.duckhunt.Game;

import javax.swing.*;
import java.awt.*;

/**
 * Main class for game.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:28
 **/
public class DuckHunt extends JFrame {

	private static final Dimension FRAME_SIZE = new Dimension(800, 500);


	private int score;
	private int successCount;
	private int missedCount;
	private int timer;

	private void loadFrame(){

		this.setTitle("Duck Hunt By Bill Chen");
		this.setSize(FRAME_SIZE);
		this.setVisible(true);
		this.setResizable(false);


	}

	public void start() {
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				loadFrame();
			}
		});
	}
}
