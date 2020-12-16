package io.billc.duckhunt.Ducks;

import io.billc.duckhunt.FlyBehaviour.FlyNoWay;
import io.billc.duckhunt.FlyBehaviour.FlyWithWings;
import io.billc.duckhunt.QuackBehaviour.MuteQuack;
import io.billc.duckhunt.Utils.Utils;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:29
 **/
public class DecoyDuck extends Duck{
	public DecoyDuck() {
		super("Decoy Duck");
		super.setFlyBehaviour(new FlyNoWay());
		super.setQuackBehaviour(new MuteQuack(this));
		displayImage = Utils.getImage("/image/duck1.png");
	}
}
