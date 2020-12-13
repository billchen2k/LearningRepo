import io.billc.duckhunt.Utils.Sound;
import io.billc.duckhunt.Utils.Utils;
import org.junit.jupiter.api.Test;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Sound Test
 *
 * @author billchen
 * @version 1.0
 * @create 2020-12-12 22:40
 **/
public class SoundTest {

	@Test
	public void soundTest() throws InterruptedException {
		try {
			Sound sound = Utils.getSound("/sound/BGM.wav");
			Sound s1 = Utils.getSound("/sound/shootDown.wav");

			sound.play();
			s1.play();

			Timer timer = new Timer(1000, new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					Sound s1 = Utils.getSound("/sound/shootDown.wav");

				}
			});
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		Thread.sleep(10000);
	}
}
