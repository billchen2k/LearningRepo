package io.billc.duckhunt.Game;

import io.billc.duckhunt.Ducks.*;
import io.billc.duckhunt.Utils.Config;
import io.billc.duckhunt.Utils.Sound;
import io.billc.duckhunt.Utils.Utils;

import javax.swing.*;
import javax.xml.transform.Result;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Main game panel
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 23:47
 **/
public class GamePanel extends JPanel implements MouseMotionListener {

	private int shotCount;
	private int missedCount;
	private int duckUpperBound;
	private long startTimeMillis;

	private Timer tickTimer;
	private Random rd = new Random();

	DecoyDuck duck = new DecoyDuck();
	ArrayList<Duck> ducks = new ArrayList<>();

	private BufferedImage backgroundImage;
	private Rectangle cursorRectangle = new Rectangle(0, 0, 0, 0);

	private Sound shotSuccessSound = Utils.getSound("/sound/shootDown.wav");
	private Sound shotMissSound = Utils.getSound("/sound/shootMiss.wav");
	private Sound flyawaySound = Utils.getSound("/sound/duckFly.wav");
	private Sound bgmSound = Utils.getSound("/sound/BGM.wav");

	private void startGame() {
		bgmSound.loop();
		startTimeMillis = System.currentTimeMillis();
		shotCount = missedCount = 0;
		ActionListener listener = (ActionEvent e) -> {
			tick();
		};
		tickTimer = new Timer(40, listener);
		tickTimer.start();
	}

	public GamePanel() {
		this.duckUpperBound = 10;
		this.backgroundImage = Utils.getImage("/image/bg.png");
		this.addMouseMotionListener(this);
		this.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent e) {
				Point hitPoint = e.getPoint();
				shoot(hitPoint.x, hitPoint.y);
			}
		});
		startGame();
	}

	private Integer getPlaySeconds() {
		return (int) (System.currentTimeMillis() - startTimeMillis) / 1000;
	}

	/**
	 * This method is used to handle duck generation and duck runaway.
	 */
	private void generateDuck() {
		if ((System.currentTimeMillis() - startTimeMillis) / 500 < ducks.size() || ducks.size() - missedCount - shotCount >= duckUpperBound) {
			// Don't need to generate
			return;
		}
		int type = rd.nextInt(4);
		switch (type) {
			case 0:
				ducks.add(new DecoyDuck());
				break;
			case 1:
				ducks.add(new MallardDuck());
				break;
			case 2:
				ducks.add(new RedHeadDuck());
			case 3:
				ducks.add(new RubberDuck());
		}
	}

	/**
	 * Main tick, activates every frame.
	 */
	private void tick() {
		if (System.currentTimeMillis() - startTimeMillis > Config.GAME_PLAY_DURATION * 1000) {
			stopGame();
		}

		int rounds = (int) (System.currentTimeMillis() - startTimeMillis) / (1000 * Config.WAVE_INTERVAL_SECS);
		duckUpperBound = (rounds + 1) * Config.DUCK_PER_WAVE;

		generateDuck();

		ducks.forEach(one -> {
			/** Update Duck Position **/
			if(one.getDuckStatus() == Duck.DUCK_STATUS_ACTIVE) {
				one.performFly();
				one.swim();
			}

			/** Flyway duck **/
			if (one.getAgeMills() > Config.DUCK_LIFESPAN_MILLS && one.getDuckStatus() == Duck.DUCK_STATUS_ACTIVE) {
				one.flyAway();
				if (!flyawaySound.isPlaying()) {
					flyawaySound.play();
				}
			}

			/** Perform Quack **/
			if (one.getAgeMills() % 10000 < 500 && !one.isQuacking() && one.getDuckStatus() == Duck.DUCK_STATUS_ACTIVE) {
				one.performQuack();
			}

		});
		repaint();
	}

	private void shoot(int x, int y) {
		AtomicBoolean ifHitAny = new AtomicBoolean(false);

		ducks.forEach(one -> {
			if (one.getDuckStatus() == Duck.DUCK_STATUS_ACTIVE
				&&x >= one.getX() && x <= one.getX() + Config.DUCK_SIZE
				&& y >= one.getY() && y <= one.getY() + Config.DUCK_SIZE) {
				// Success
				ifHitAny.set(true);
				one.shotDown();
			}
		});
		if (ifHitAny.get()) {
			shotSuccessSound.play();
		}
		else{
			shotMissSound.play();
		}
	}

	private void stopGame() {
		bgmSound.stop();
		tickTimer.stop();
	}

	public ResultPanel getResultPanel() {
		ResultPanel resultPanel = new ResultPanel(ducks.size(), missedCount, shotCount);
		return resultPanel;
	}

	@Override
	protected void paintComponent(Graphics g) {
//		g.setFont(Utils.getFont("superhelio.ttf"));
		g.setFont(Utils.getFontSuperhelio(24));
		g.setColor(Color.WHITE);
		Graphics2D g2d = (Graphics2D) g;
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2d.drawImage(backgroundImage, 0, 0, Config.FRAME_SIZE.width, Config.FRAME_SIZE.height, getParent());

		shotCount = missedCount = 0;
		ducks.forEach(oneDuck -> {

			if(oneDuck.isQuacking()) {
				g2d.drawImage(Utils.getImage("/image/Quack.png"), oneDuck.getX() - 20, oneDuck.getY() - 10, 25, 25, getParent());
			}
			switch (oneDuck.getDuckStatus()) {
				case (Duck.DUCK_STATUS_SHOOTDOWN):
					shotCount++;
					if (System.currentTimeMillis() - oneDuck.getShotTimeMills() < 500) {
						g2d.drawImage(oneDuck.getDisplayImage(), oneDuck.getX(), oneDuck.getY(), Config.DUCK_SIZE, Config.DUCK_SIZE, getParent());
						g2d.drawImage(Utils.getImage("/image/Cross.png"), oneDuck.getX() + 10, oneDuck.getY() + 10, 30, 30, getParent());
					}
					break;
				case (Duck.DUCK_STATUS_RUNAWAY):
					missedCount++;
					break;
				case (Duck.DUCK_STATUS_ACTIVE):
					if (oneDuck.getAgeMills() > Config.DUCK_LIFESPAN_MILLS - 5000) {
						/** Blink **/
						if (oneDuck.getAgeMills() % 300 < 200){
							g2d.drawImage(oneDuck.getDisplayImage(), oneDuck.getX(), oneDuck.getY(), Config.DUCK_SIZE, Config.DUCK_SIZE, getParent());
						}
					}
					else{
						g2d.drawImage(oneDuck.getDisplayImage(), oneDuck.getX(), oneDuck.getY(), Config.DUCK_SIZE, Config.DUCK_SIZE, getParent());
					}
					break;
			}
		});
		g2d.drawString("TIME: " + String.valueOf(Config.GAME_PLAY_DURATION - getPlaySeconds()), 20, 450);
		g2d.drawString("HIT: " + String.valueOf(shotCount), 700, 450);
		g2d.drawString("MISSED: " + String.valueOf(missedCount), 550, 450);
	}

	public void mouseDragged(MouseEvent e) {

	}

	public void mouseMoved(MouseEvent e) {
		cursorRectangle.x = e.getPoint().x;
		cursorRectangle.y = e.getPoint().y;
//		repaint();
	}
}
