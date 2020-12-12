package io.billc.duckhunt.QuackBehaviour;

import io.billc.duckhunt.Ducks.Duck;
import io.billc.duckhunt.Utils.Utils;

/**
 * Quack behaviour class
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 21:25
 **/
public class QuackBehaviour implements QuackBehaviourInterface{

	protected Duck relatedDuck;

	public void quack() {
		Utils.printFromDuck("Undefined quack behaviour.", relatedDuck);
	}

	QuackBehaviour(Duck d) {
		this.relatedDuck = d;
	}
}
