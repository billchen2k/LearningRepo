package io.billc.duckhunt.Ducks;

import io.billc.duckhunt.FlyBehaviour.FlyNoWay;
import io.billc.duckhunt.FlyBehaviour.FlyWithWings;
import io.billc.duckhunt.QuackBehaviour.MuteQuack;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:29
 **/
public class DecoyDuck extends Duck{
	public DecoyDuck() {
		super("Decoy Duck");
		super.setFlyBehaviour(new FlyNoWay(this));
		super.setQuackBehaviour(new MuteQuack(this));
	}
}
