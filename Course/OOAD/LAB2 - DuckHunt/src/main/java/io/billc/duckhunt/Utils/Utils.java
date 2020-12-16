package io.billc.duckhunt.Utils;

import io.billc.duckhunt.Ducks.Duck;


import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.net.URL;
import java.net.URLDecoder;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Util class.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 20:47
 **/
public class Utils {
	public static int totalDucks = 0;

	public static void printFromDuck(String msg, Duck d) {
		SimpleDateFormat formatter= new SimpleDateFormat("HH:mm:ss.SS");
		Date date = new Date(System.currentTimeMillis());
		if (d != null) {
			System.out.printf("<%s DUCK %03d - %14s>: %s\n", formatter.format(date), d.getDuckId(), d.getDuckType(), msg);
		}
		else {
			System.out.printf("<%s DUCK %03d - %14s>: %s\n", formatter.format(date), 0, "Unknown Duck", msg);
		}
	}

	public static URL getResource(String p) {
		final URL resource = Utils.class.getResource(p);
		return resource;
	}

	public static Sound getSound(String path) {
		Sound sound = null;
		try {
			sound = new Sound(getResource(path));
		} catch (Exception ex) {
			ex.printStackTrace(System.err);
		}
		return sound;
	}

	public static BufferedImage getImage(String path) {
		BufferedImage image = null;
		try {
			image = ImageIO.read(getResource(path));
		} catch (IOException ex) {
			ex.printStackTrace(System.err);
			System.exit(-1);
		}
		return image;
	}

	public static Font getFont(String name, int size) {
		Font font = null;
		if (name == null) {
			font = new Font("sans", Font.PLAIN, 24);
		}
		try {
			URL fontResource = getResource("/font/" + name);
			font = Font.createFont(Font.TRUETYPE_FONT, Utils.class.getResourceAsStream("/font/" + name));
			GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
			ge.registerFont(font);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return font.deriveFont((float) size);
	}

	public static Font getFontSuperhelio(int size) {
		return getFont("superhelio.ttf", size);
	}
}
