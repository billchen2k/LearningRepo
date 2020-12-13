package io.billc.duckhunt.Game;

import io.billc.duckhunt.Utils.Config;
import io.billc.duckhunt.Utils.Sound;
import io.billc.duckhunt.Utils.Utils;
import lombok.SneakyThrows;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

/**
 * Main class for game.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:28
 **/
public class DuckHunt extends JFrame {



	private WelcomePanel welcomePanel;
	private GamePanel gamePanel;
	private ResultPanel resultPanel;

	private Timer gameTimer;

	public DuckHunt() {
		welcomePanel = new WelcomePanel();
		gameTimer = new Timer(Config.GAME_PLAY_DURATION * 1000, new ActionListener() {
			@SneakyThrows
			@Override
			public void actionPerformed(ActionEvent e) {
				resultPanel = gamePanel.getResultPanel();
				gamePanel.setVisible(false);
				gameTimer.stop();
				Timer listenerTime = new Timer(3000, new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						resultPanel.addMouseListener(new MouseAdapter() {
							@Override
							public void mousePressed(MouseEvent e) {
								resultPanel.setVisible(false);
								gamePanel = new GamePanel();
								add(gamePanel);
								gameTimer.start();
								repaint();
								revalidate();
							}
						});
					}
				});
				listenerTime.start();
				add(resultPanel);
			}
		});
	}



	private void loadFrame(){
		this.setTitle("Duck Hunt || ECNU @ Bill Chen");
		this.setSize(Config.FRAME_SIZE);
		this.setVisible(true);
		this.setResizable(false);

		this.add(new ResultPanel(0,0,0));
		welcomePanel.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				welcomePanel.setVisible(false);
				gamePanel = new GamePanel();
				add(gamePanel);
				gameTimer.start();
				repaint();
				revalidate();
			}
		});

		this.add(welcomePanel);

	}

	public void start() {
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				loadFrame();
			}
		});
	}
}
