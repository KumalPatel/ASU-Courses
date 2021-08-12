/**
 * Team Project CSE360
 * Names: Gabriel Anderson, Kumal Patel, Christopher Campanella, Vincent Li
 * Class ID: 70642
 * Description: Initializes the applet.
 * GitHub URL (via HTTPS): https://github.com/LowRaps/Group_Project.git
 */

package formatTextFile;

import javax.swing.JApplet;

public class StartGUI extends JApplet {
	private final int WIDTH = 800;
	private final int HEIGHT = 340;

	public void init() {
		ControlPanel panel = new ControlPanel(WIDTH, HEIGHT);
		getContentPane().add(panel);
		setSize(WIDTH, HEIGHT);
	}
}
