package io.billc.duckhunt.Utils;

import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.Line;
import java.net.URL;

/**
 * Sound class, used for playing SFXs.
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 22:39
 **/
public class Sound {

	private static final Line.Info INFO = new Line.Info(Clip.class);
	private URL soundUrl;
	private Clip readyClip;

	public Sound(URL url) throws Exception {
		if (url == null) {
			throw new Exception("Cannot read null url path");
		}
		this.soundUrl = url;
		this.readyClip = this.getNewClip(this.soundUrl);
	}

	public Clip play() {
		try {
			readyClip = getNewClip(soundUrl);
			readyClip.loop(0);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return readyClip;
	}

	public Clip loop() {
		readyClip.loop(-1);
		return readyClip;
	}

	public Clip stop() {
		if (readyClip != null) {
			readyClip.stop();
		}
		return readyClip;
	}

	public boolean isPlaying() {
		if(readyClip == null) {
			return false;
		}
		return readyClip.isRunning();
	}

	public static Clip getNewClip(URL clipURL) throws Exception {
		Clip clip = null;
		try {
			clip = (Clip) AudioSystem.getLine(INFO);
			clip.open(AudioSystem.getAudioInputStream(clipURL));
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		return clip;
	}
}
