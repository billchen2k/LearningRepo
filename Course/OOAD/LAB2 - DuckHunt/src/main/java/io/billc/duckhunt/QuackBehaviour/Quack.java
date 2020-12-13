package io.billc.duckhunt.QuackBehaviour;

import io.billc.duckhunt.Ducks.Duck;
import io.billc.duckhunt.Utils.Utils;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:30
 **/
public class Quack extends QuackBehaviour {

	public Quack(Duck d){
		super(d);
		this.quackSound = Utils.getSound("/sound/duckQuack.wav");
	}

	public void quack() {
		Utils.printFromDuck("I can quack. Quack, Quack, Quack.", relatedDuck);
		quackSound.stop();
		quackSound.play();
	}

	@Override
	public boolean isQuacking() {
		return quackSound.isPlaying();
	}
}
