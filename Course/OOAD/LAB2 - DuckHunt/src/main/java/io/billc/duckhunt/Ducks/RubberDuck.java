package io.billc.duckhunt.Ducks;

import io.billc.duckhunt.FlyBehaviour.FlyNoWay;
import io.billc.duckhunt.QuackBehaviour.Squick;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:29
 **/
public class RubberDuck extends Duck{
	public RubberDuck() {
		super("Rubber Duck");
		super.setFlyBehaviour(new FlyNoWay(this));
		super.setQuackBehaviour(new Squick(this));
	}
}
