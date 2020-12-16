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

	private ActionListener resultTimerListener;

	public DuckHunt() {
		welcomePanel = new WelcomePanel();

		gameTimer = new Timer(Config.GAME_PLAY_DURATION * 1000, new ActionListener() {
			@SneakyThrows
			@Override
			public void actionPerformed(ActionEvent e) {
				resultPanel = gamePanel.getResultPanel();
				gamePanel.setVisible(false);
				remove(gamePanel);
				repaint();
				revalidate();
				gameTimer.stop();
				Timer listenerTimer = new Timer(3000, new ActionListener() {
					@Override
					public void actionPerformed(ActionEvent e) {
						resultPanel.addMouseListener(new MouseAdapter() {
							@Override
							public void mousePressed(MouseEvent e) {
								resultPanel.setVisible(false);
								remove(resultPanel);
								gamePanel = new GamePanel();
								add(gamePanel);
								gameTimer.start();
								repaint();
								revalidate();
							}
						});
					}
				});
				listenerTimer.start();
				listenerTimer.setRepeats(false);
				add(resultPanel);
			}
		});
	}



	private void loadFrame(){
		this.setTitle("Duck Hunt || ECNU @ Bill Chen");
		this.setSize(Config.FRAME_SIZE);
		this.setVisible(true);
		this.setResizable(false);

		welcomePanel.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				welcomePanel.setVisible(false);
				remove(welcomePanel);
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
