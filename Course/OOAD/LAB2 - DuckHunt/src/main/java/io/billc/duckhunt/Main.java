package io.billc.duckhunt;


import io.billc.duckhunt.Ducks.*;
import io.billc.duckhunt.Game.DuckHunt;

import javax.swing.*;
import java.awt.*;

/**
 * Create four kinds of ducks and one default duck.
 * Their behavior will be printed in the STDOUT and a GUI in then shown and playable.
 */
public class Main {

    public static void main(String[] args) {
        Duck[] ducks = {new Duck(), new DecoyDuck(), new MallardDuck(), new RedHeadDuck(), new RubberDuck()};
        for(Duck one : ducks) {
            one.performFly();
//            one.performQuack();
            one.swim();
        }

        /** Game Start **/
        DuckHunt duckHunt = new DuckHunt();
        duckHunt.start();
    }
}
