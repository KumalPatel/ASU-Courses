/**
 * Team Project CSE360
 * Names: Gabriel Anderson, Kumal Patel, Christopher Campanella, Vincent Li
 * Class ID: 70642
 * Description: Sets up the arrangement of the applet's components 
 * and includes the buttonlisteners for Start, Clear, and Quit.
 * GitHub URL (via HTTPS): https://github.com/LowRaps/Group_Project.git
 */

package formatTextFile;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class GUIPanel extends JPanel {
	// components of the panel
	private JButton start, clear, quit;
	private JLabel label1, label2, label3, label4;
	private JPanel buttons1, panel7;
	private JTextField field1, field2;
	private JTextArea area1;
	private JScrollPane scroll1;
	

	// Constructor to create all components, add their listener to them,
	// and arrange them using a layout.
	public GUIPanel(int width, int height) {

		// create 3 buttons, start, clear, and color chooser for waves.
		start = new JButton("Start");
		clear = new JButton("Clear");
		quit = new JButton("Quit");

		// initialize JTexfields
		field1 = new JTextField(10);
		field2 = new JTextField(10);

		// add a listener to each button
		start.addActionListener(new ButtonListener());
		clear.addActionListener(new ButtonListener());
		quit.addActionListener(new ButtonListener());

		buttons1 = new JPanel();
		buttons1.setLayout(new GridLayout(1, 3));

		buttons1.add(start);
		buttons1.add(clear);
		buttons1.add(quit);

		// create a label for the delay
		label1 = new JLabel("Input File Name: ");

		JPanel panel3 = new JPanel();
		panel3.setLayout(new BorderLayout());
		panel3.add(label1, BorderLayout.NORTH);
		panel3.add(field1, BorderLayout.SOUTH);

		// create a label for the wave width
		label2 = new JLabel("Output File Name: ");
		label3 = new JLabel("Cleared fields");

		JPanel panel4 = new JPanel();
		panel4.setLayout(new BorderLayout());
		panel4.add(label2, BorderLayout.NORTH);
		panel4.add(field2, BorderLayout.SOUTH);

		label3 = new JLabel();

		JPanel panel6 = new JPanel();
		panel6.setLayout(new GridLayout(3, 1));
		panel6.add(panel3);
		panel6.add(panel4);
		panel6.add(label3);
		panel6.add(label3);

		JPanel panel5 = new JPanel();
		panel5.setLayout(new BorderLayout());
		panel5.add(buttons1, BorderLayout.SOUTH);
		panel5.add(panel6, BorderLayout.CENTER);
		
		area1 = new JTextArea("Text to be Displayed: ");
		
		area1.setForeground(Color.GRAY);
		area1.setFont(new Font("Sanserif", Font.ITALIC, 12));
		area1.setEditable(false);
		
		scroll1 = new JScrollPane(area1); // formatted output
		label4 = new JLabel("Formatted Output: ");
		
		JPanel panel7 = new JPanel();
		panel7.setLayout(new BorderLayout());
		panel7.add(label4, BorderLayout.NORTH);
		panel7.add(scroll1, BorderLayout.CENTER);
	
		
		setLayout(new BorderLayout());
		add(panel5, BorderLayout.WEST);
		add(panel7, BorderLayout.CENTER);

	}

	// ButtonListener defines actions to be performed when each button
	// is pushed.
	private class ButtonListener implements ActionListener {
		public void actionPerformed(ActionEvent event) {
			Object action = event.getSource();

			if (action == start) {
				String inputFileName = field1.getText();
				String outputFileName = field2.getText();
				// setup Formatter class
				Formatter doc = new Formatter(inputFileName, outputFileName);
				// check for initial errors
				label3.setText(doc.checkInitialErrors(inputFileName, outputFileName));
				// if there are no initial errors, begin formatting output
				if(label3.getText().equals("<html></html>")) {
					doc.readFile();	
					// show output in the text area
					area1.setForeground(Color.BLACK);
					area1.setFont(new Font("Sansetif", Font.PLAIN, 12));
					String preview = "";
					File temp = new File(outputFileName);				
					try {
						Scanner scanner = new Scanner(temp);
						while(scanner.hasNextLine()) {
							preview += scanner.nextLine() + "\n";
						}
						scanner.close();
					} catch (FileNotFoundException e) {
						area1.setForeground(Color.RED);
						preview = "Unable to preview " + outputFileName;
					}
					area1.setText(preview);
				}
			} else if (action == clear) {
				field1.setText("");
				field2.setText("");
				area1.setText("");
			} else if (action == quit) {
				System.exit(0);
				label3.setText("");
			}
		}
	} // end of ButtonListener
}
