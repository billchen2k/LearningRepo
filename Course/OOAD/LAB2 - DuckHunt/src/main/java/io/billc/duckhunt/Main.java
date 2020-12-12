package io.billc.duckhunt;


import io.billc.duckhunt.Ducks.*;
import io.billc.duckhunt.Game.DuckHunt;

import javax.swing.*;
import java.awt.*;

public class Main {

    public static void main(String[] args) {
        Duck[] ducks = {new Duck(), new DecoyDuck(), new MallardDuck(), new RedHeadDuck(), new RubberDuck()};
        for(Duck one : ducks) {
            one.performFly();
            one.performQuack();
            one.swim();
        }
        DuckHunt duckHunt = new DuckHunt();
        duckHunt.start();
    }
}
