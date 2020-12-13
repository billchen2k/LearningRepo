package io.billc.duckhunt.QuackBehaviour;

import io.billc.duckhunt.Ducks.Duck;
import io.billc.duckhunt.Utils.Utils;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:30
 **/
public class Squick extends QuackBehaviour {
	public Squick(Duck d) {
		super(d);
		this.quackSound = Utils.getSound("/sound/duckSquick.wav");
	}

	public void quack() {
		Utils.printFromDuck("I can quack. Squick, Squick, Squick.", relatedDuck);
		quackSound.stop();
		quackSound.play();
	}

	@Override
	public boolean isQuacking() {
		return quackSound.isPlaying();
	}
}
