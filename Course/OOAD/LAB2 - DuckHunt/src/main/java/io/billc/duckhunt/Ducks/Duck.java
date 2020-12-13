package io.billc.duckhunt.Ducks;

import io.billc.duckhunt.FlyBehaviour.FlyBehaviourInterface;
import io.billc.duckhunt.FlyBehaviour.FlyWithWings;
import io.billc.duckhunt.QuackBehaviour.Quack;
import io.billc.duckhunt.QuackBehaviour.QuackBehaviourInterface;
import io.billc.duckhunt.Utils.Config;
import io.billc.duckhunt.Utils.Utils;
import lombok.Getter;
import lombok.Setter;

import java.awt.image.BufferedImage;
import java.util.Random;

/**
 * Duck class.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:28
 **/
public class Duck {

	private FlyBehaviourInterface flyBehaviour;

	private QuackBehaviourInterface quackBehaviour;

	@Getter private String duckType;

	@Getter private long duckId;

	/** Real Games **/

	public static final int DUCK_STATUS_ACTIVE = 1;
	public static final int DUCK_STATUS_SHOOTDOWN = 2;
	public static final int DUCK_STATUS_RUNAWAY = 3;

	@Getter @Setter protected int x;
	@Getter @Setter protected int y;
	@Getter @Setter protected int duckStatus;
	@Getter protected long birthTimeMills;

	@Getter @Setter protected long shotTimeMills;
	@Getter @Setter protected float flySlopeK;
	@Getter @Setter protected int flyXDirection;
	@Getter @Setter protected int flyYDirection;

	protected BufferedImage displayImage;

	public BufferedImage getDisplayImage() {
		return displayImage;
	}

	public Duck() {
		duckId = Utils.totalDucks + 1;
		duckType = "Default Duck";
		flyBehaviour = new FlyWithWings(this);
		quackBehaviour = new Quack(this);

		/** Real Games **/
		Utils.totalDucks++;
		x = new Random().nextInt(Config.FRAME_SIZE.width);
		y = 350;
		duckStatus = DUCK_STATUS_ACTIVE;
		birthTimeMills = System.currentTimeMillis();
		flySlopeK = new Random().nextFloat() % 2;
		flyYDirection = -1;
		flyXDirection = new Random().nextInt(2) == 1 ? 1 : -1;
	}

	protected Duck(String duckType) {
		this();
		this.duckType = duckType;
	}

	public void performQuack(){
		quackBehaviour.quack();
	}

	public void performFly(){
		Duck newd = flyBehaviour.fly();
		setX(newd.getX());
		setY(newd.getY());
		setFlyYDirection(newd.getFlyYDirection());
		setFlyXDirection(newd.getFlyXDirection());
	}

	public void swim() {
		Utils.printFromDuck("I am swimming.", this);
		setX((x + (int) Config.DUCK_FLY_SPEED_FACTOR * 2 * flyXDirection + Config.FRAME_SIZE.width) % Config.FRAME_SIZE.width);
	}

	protected void setFlyBehaviour(FlyBehaviourInterface flyBehaviour) {
		this.flyBehaviour = flyBehaviour;
	}

	protected void setQuackBehaviour(QuackBehaviourInterface quackBehaviour) {
		this.quackBehaviour = quackBehaviour;
	}

	public long getAgeMills() {
		return System.currentTimeMillis() - birthTimeMills;
	}

	public boolean isQuacking() {
		return quackBehaviour.isQuacking();
	}

	public void shotDown() {
		shotTimeMills = System.currentTimeMillis();
		duckStatus = DUCK_STATUS_SHOOTDOWN;
	}


}
