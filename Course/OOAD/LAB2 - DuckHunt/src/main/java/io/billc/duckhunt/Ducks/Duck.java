package io.billc.duckhunt.Ducks;

import io.billc.duckhunt.FlyBehaviour.FlyBehaviourInterface;
import io.billc.duckhunt.FlyBehaviour.FlyWithWings;
import io.billc.duckhunt.QuackBehaviour.Quack;
import io.billc.duckhunt.QuackBehaviour.QuackBehaviourInterface;
import io.billc.duckhunt.Utils.Utils;
/**
 * Duck class.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:28
 **/
public class Duck {

	private static final int DUCK_STATUS_ACTIVE = 1;
	private static final int DUCK_STATUS_SHOOTDOWN = 2;
	private static final int DUCK_STATUS_RUNAWAY = 3;

	private FlyBehaviourInterface flyBehaviour;

	private QuackBehaviourInterface quackBehaviour;

	private String duckType;

	private long duckId;

	private int x;
	private int y;
	private int duckStatus;

	public Duck() {
		duckId = Utils.totalDucks + 1;
		duckType = "Default Duck";
		flyBehaviour = new FlyWithWings(this);
		quackBehaviour = new Quack(this);
		Utils.totalDucks++;
	}

	protected Duck(String duckType) {
		this();
		this.duckType = duckType;
	}

	public void performQuack(){
		quackBehaviour.quack();
	}

	public void performFly(){
		flyBehaviour.fly();
	}

	public void swim() {
		Utils.printFromDuck("I am swimming.", this);
	}

	public long getDuckId() {
		return duckId;
	}

	public String getDuckType() {
		return duckType;
	}

	protected void setFlyBehaviour(FlyBehaviourInterface flyBehaviour) {
		this.flyBehaviour = flyBehaviour;
	}

	protected void setQuackBehaviour(QuackBehaviourInterface quackBehaviour) {
		this.quackBehaviour = quackBehaviour;
	}


}
