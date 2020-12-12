package io.billc.duckhunt.FlyBehaviour;

import io.billc.duckhunt.Ducks.Duck;
import io.billc.duckhunt.Utils.Utils;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:29
 **/
public class FlyNoWay extends FlyBehaviour {

	public FlyNoWay(Duck d) {
		super(d);
	}

	@Override
	public void fly() {
		Utils.printFromDuck("I am unable to fly.", relatedDuck);
	}

}
