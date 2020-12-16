package io.billc.duckhunt.FlyBehaviour;

import io.billc.duckhunt.Ducks.Duck;
import io.billc.duckhunt.Utils.Config;
import io.billc.duckhunt.Utils.Utils;

/**
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:29
 **/
public class FlyWithWings extends FlyBehaviour {

	@Override
	public Duck fly(Duck duck) {
		Utils.printFromDuck(String.format("I can fly with my wings. Current postion: X: %d, Y: %d", duck.getX(), duck.getY()), duck);

		/** Move to next cordinate **/
		int attempNextX = (int) (duck.getX() + duck.getFlyXDirection() * Config.DUCK_FLY_SPEED_FACTOR * 5);
		int attempNextY = (int) (duck.getY() + duck.getFlyYDirection() * duck.getFlySlopeK() * Config.DUCK_FLY_SPEED_FACTOR * 5);

		if (attempNextY > Config.FRAME_SIZE.height - Config.DUCK_SIZE ) {
			duck.setFlyYDirection(-1);
		}
		if(attempNextY < 0) {
			attempNextY = 2;
			duck.setFlyYDirection(1);
		}
		if (attempNextX > Config.FRAME_SIZE.width - Config.DUCK_SIZE ) {
			duck.setFlyXDirection( -1);
		}
		if(attempNextX < 0) {
			attempNextX = 2;
			duck.setFlyXDirection(1);
		}
		duck.setX((attempNextX + Config.FRAME_SIZE.width) % Config.FRAME_SIZE.width);
		duck.setY((attempNextY + Config.FRAME_SIZE.height) % Config.FRAME_SIZE.height);
		return duck;
	}
}
