package io.billc.duckhunt.Ducks;

import io.billc.duckhunt.FlyBehaviour.FlyWithWings;
import io.billc.duckhunt.QuackBehaviour.Quack;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:29
 **/
public class RedHeadDuck extends Duck{
	public RedHeadDuck() {
		super("Read Head Duck");
		super.setFlyBehaviour(new FlyWithWings(this));
		super.setQuackBehaviour(new Quack(this));
	}
}
