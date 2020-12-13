package io.billc.duckhunt.Game;

import io.billc.duckhunt.Ducks.DecoyDuck;
import io.billc.duckhunt.Utils.Config;
import io.billc.duckhunt.Utils.Utils;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;

/**
 * Main JFrame Panel
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 21:52
 **/
public class WelcomePanel extends JPanel{

	private BufferedImage backgroundImage;

	@Override
	protected void paintComponent(Graphics g) {
		g.setColor(Color.WHITE);
		Graphics2D g2d = (Graphics2D) g;
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2d.drawImage(backgroundImage, 0, 0, Config.FRAME_SIZE.width, Config.FRAME_SIZE.height, getParent());
		g2d.setFont(new Font("superhelio", Font.PLAIN, 48));
		g2d.drawString("DUCK HUNT", (int) (Config.FRAME_SIZE.width * 0.35), (int) (Config.FRAME_SIZE.height * 0.3));
		g2d.setFont(new Font("superhelio", Font.PLAIN, 24));
		g2d.drawString("CLICK TO START", (int) (Config.FRAME_SIZE.width * 0.38), (int) (Config.FRAME_SIZE.height * 0.6));
	}

	public WelcomePanel() {
		this.backgroundImage = Utils.getImage("/image/bg.png");
	}

	public void mouseDragged(MouseEvent e) {

	}

	public void mouseMoved(MouseEvent e) {

	}
}
