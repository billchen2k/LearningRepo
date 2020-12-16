package io.billc.duckhunt.Game;

import io.billc.duckhunt.Utils.Config;
import io.billc.duckhunt.Utils.Utils;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;

/**
 * Panel to show results of the game.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 23:42
 **/
public class ResultPanel extends JPanel {

	private BufferedImage backgroundImage;
	private int totalDucks;
	private int missedDucks;
	private int shotDownDucks;

	@Override
	protected void paintComponent(Graphics g) {
		g.setColor(Color.WHITE);
		Graphics2D g2d = (Graphics2D) g;
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2d.drawImage(backgroundImage, 0, 0, Config.FRAME_SIZE.width, Config.FRAME_SIZE.height, getParent());
		g2d.setFont(Utils.getFontSuperhelio(48));
		g2d.drawString("TIME'S UP", (int) (Config.FRAME_SIZE.width * 0.37), (int) (Config.FRAME_SIZE.height * 0.3));
		g2d.setFont(Utils.getFontSuperhelio(24));
		g2d.drawString("HIT: " + String.valueOf(shotDownDucks), 300, 250);
		g2d.drawString("MISS: " + String.valueOf(missedDucks), 300, 290);
		g2d.drawString("TOTAL DUCKS:  " + String.valueOf(totalDucks), 300, 330);
		g2d.drawString("CLICK TO RESTART.", 300, 400);
	}

	public ResultPanel() {
		this.backgroundImage = Utils.getImage("/image/bg.png");
	}

	public ResultPanel(int totalDucks, int missedDucks, int shotDownDucks) {
		this();
		this.totalDucks = totalDucks;
		this.missedDucks = missedDucks;
		this.shotDownDucks = shotDownDucks;
	}

	public void mouseDragged(MouseEvent e) {

	}

	public void mouseMoved(MouseEvent e) {

	}

}
