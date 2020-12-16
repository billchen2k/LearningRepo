package io.billc.duckhunt.Ducks;

import io.billc.duckhunt.FlyBehaviour.FlyNoWay;
import io.billc.duckhunt.FlyBehaviour.FlyWithWings;
import io.billc.duckhunt.QuackBehaviour.Squick;
import io.billc.duckhunt.Utils.Utils;

/**
 * Mallard Duck.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:28
 **/
public class MallardDuck extends Duck{
	public MallardDuck() {
		super("Mallard Duck");
		super.setFlyBehaviour(new FlyWithWings());
		super.setQuackBehaviour(new Squick(this));
		displayImage = Utils.getImage("/image/duck2.png");
	}
}
