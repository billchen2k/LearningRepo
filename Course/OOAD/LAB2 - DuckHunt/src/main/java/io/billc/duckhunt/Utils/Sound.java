package io.billc.duckhunt.Utils;

import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.Line;
import java.net.URL;
import java.util.HashMap;

/**
 * Sound class, used for playing SFXs.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 22:39
 **/
public class Sound {

	private static final Line.Info INFO = new Line.Info(Clip.class);
	private static HashMap<String, Sound> map;
	private URL soundUrl;
	private Clip readyClip;

	public Sound(URL url) throws Exception {
		if (url == null) {
			throw new Exception("Cannot read null url path");
		}
		this.soundUrl = url;
		this.readyClip = this.getNewClip(this.soundUrl);
	}



	public static Clip getNewClip(URL clipURL) throws Exception {
		Clip clip = null;
		try {
			AudioSystem.getLine(INFO);
			clip.open(AudioSystem.getAudioInputStream(clipURL));
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		return clip;
	}
}
