package io.billc.duckhunt.FlyBehaviour;

import io.billc.duckhunt.Ducks.Duck;
import io.billc.duckhunt.Utils.Utils;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 21:20
 **/
public class FlyBehaviour implements FlyBehaviourInterface{
	protected Duck duck;

	public Duck fly() {
		Utils.printFromDuck("Undefined fly behaviour.", duck);
		return duck;
	}

	FlyBehaviour(Duck d) {
		duck = d;
	}
}
