package io.billc.duckhunt.Ducks;

import io.billc.duckhunt.FlyBehaviour.FlyWithWings;
import io.billc.duckhunt.QuackBehaviour.Quack;
import io.billc.duckhunt.Utils.Utils;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:29
 **/
public class RedHeadDuck extends Duck{
	public RedHeadDuck() {
		super("Read Head Duck");
		super.setFlyBehaviour(new FlyWithWings());
		super.setQuackBehaviour(new Quack(this));
		displayImage = Utils.getImage("/image/duck3.png");
	}
}
