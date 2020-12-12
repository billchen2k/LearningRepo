package io.billc.duckhunt.FlyBehaviour;

import io.billc.duckhunt.Ducks.Duck;
import io.billc.duckhunt.Utils.Utils;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:29
 **/
public class FlyWithWings extends FlyBehaviour {

	public FlyWithWings(Duck d) {
		super(d);
	}

	@Override
	public void fly() {
		Utils.printFromDuck("I can fly with my wings.", relatedDuck);
	}
}
