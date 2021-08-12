/**
 * Team Project CSE360
 * Names: Gabriel Anderson, Kumal Patel, Christopher Campanella, Vincent Li
 * Class ID: 70642
 * Description: Sets up a JPanel with two GUIPanels for the applet.
 * GitHub URL (via HTTPS): https://github.com/LowRaps/Group_Project.git
 */

package formatTextFile;

import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.JPanel;

public class ControlPanel extends JPanel {
	private int width, height;
	private int panelNum;

	// The constructor creates 2 panels and
	// control panels that control their movement, and organize them using a layout
	public ControlPanel(int width, int height) {
		this.width = width;
		this.height = height;
		panelNum = 2; // the number of panels is 2

		// create 2 panels to control the movements
		GUIPanel guiPanels = new GUIPanel(width / panelNum, height);

		// add two panels into this control panel using GridLayout
		setLayout(new GridLayout(panelNum, 1));
		add(guiPanels);

		setPreferredSize(new Dimension(width, height));
	}
}
