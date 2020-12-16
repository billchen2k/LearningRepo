package io.billc.duckhunt.FlyBehaviour;

import io.billc.duckhunt.Ducks.Duck;
import io.billc.duckhunt.Utils.Utils;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 21:20
 **/
public class FlyBehaviour implements FlyBehaviourInterface{

	public Duck fly(Duck duck) {
		Utils.printFromDuck("Undefined fly behaviour.", duck);
		return duck;
	}

}
