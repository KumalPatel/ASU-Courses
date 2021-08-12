/**
 * Team Project CSE360
 * Names: Gabriel Anderson, Kumal Patel, Christopher Campanella, Vincent Li
 * Class ID: 70642
 * Description: Formatter.java is the class that 
 * transforms the inputed text file into a formatted output.
 * GitHub URL (via HTTPS): https://github.com/LowRaps/Group_Project.git
 */

/**
 * Creates Formatter class that reads an input string from a text file,
 * and converts it into a standardized format.
 * 
 */
package formatTextFile;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;

public class Formatter {
	protected int total, textAlign;
	protected boolean doubleSpaced, block, indent, twoColumn, title, flagged, checkTwoColumn, checkDoubleS, checkBlock;
	protected String currentString, spillOver, inputFileName, outputFileName, indentLength, extra, testString;

	public Formatter(String inputFile, String outputFile) {
		indentLength = "     "; // 5 spaces long
		currentString = "";
		spillOver = "";
		extra = "";
		textAlign = 0; // left aligned
		doubleSpaced = false;
		block = false;
		twoColumn = true;
		indent = false;
		title = false;

		inputFileName = inputFile;
		outputFileName = outputFile;
	}

	public void readFile() {
		BufferedReader reader;
		try {
			reader = new BufferedReader(new FileReader(inputFileName));
			PrintStream out = new PrintStream(new FileOutputStream(outputFileName));
			System.setOut(out);
			String line = "";
			while (line != null) {

				// read next line
				line = reader.readLine();
				if (line == null) {
					printRemainder();
				} else if (line.length() == 2) {
					checkFlags(line);
				} else {
					if (title) {
						printTitle(line);
					} else if (twoColumn) {
						printTwoColumn(line);
					} else {
						printSingleLine(line);
					}
					if (doubleSpaced) {
						System.out.print("\n");
					}
				}

				if (doubleSpaced) {
					System.out.print("\n");
				}
			}
			reader.close();

			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void printRemainder() {

		String temp = testString.toLowerCase();
		while (extra.length() > 0) {
			if (checkTwoColumn || twoColumn) {
				printTwoColumn(extra);
				if (doubleSpaced && testString.equals("-1")) {
					System.out.print("\n");
				}
			} else {
				printSingleLine(extra);
				if (doubleSpaced && temp.equals("-b")) {
					System.out.print("\n");
				}
			}
			if (checkDoubleS) {
				System.out.print("\n");
			}
		}
		checkTwoColumn = false;
		checkDoubleS = false;
		checkBlock = false;
		return;
	}

	public void checkFlags(String line) {
		String temp = line.toLowerCase();
		testString = line;
		flagged = true;
		if (temp.equals("-r")) {
			textAlign = 2; // right flag
		} else if (temp.equals("-c")) {
			textAlign = 1; // center flag
		} else if (temp.equals("-l")) {
			textAlign = 0; // left flag
		} else if (temp.equals("-t")) {
			title = true;
		} else if (temp.equals("-n")) {
			indent = false;
			block = false;
		} else if (temp.equals("-d")) {
			doubleSpaced = true;
			checkDoubleS = false;
		} else if (temp.equals("-s")) {
			doubleSpaced = false;
			checkDoubleS = true;
		} else if (temp.equals("-i")) {
			indent = true;
		} else if (temp.equals("-b")) {
			block = true;
			checkBlock = true;
		} else if (temp.equals("-e")) {
			if (twoColumn = false) {
				System.out.print("\n");
			}
		} else if (temp.equals("-2")) {
			twoColumn = true;
			checkTwoColumn = true;
		} else if (temp.equals("-1")) {
			twoColumn = false;
			checkTwoColumn = true;
		} else {
			flagged = false;
			printSingleLine(line);
		}
		if (flagged) {
			flagged = false;
			printRemainder();
		}
	}

	public void printTwoColumn(String line) {
		spillOver = line;
		String extra2 = "";
		if (spillOver != extra) {
			if (extra.length() > 0) {
				spillOver = extra + spillOver;
				extra = "";
			}
		}
		if (spillOver.length() >= 70) {
			currentString = spillOver.substring(0, 71);
			extra = spillOver.substring(71);
		} else {
			currentString = spillOver.substring(0);
		}
		if (currentString.length() < 36) {
			System.out.print(currentString + indentLength + indentLength + "\n");
			if (extra.equals(currentString)) {
				extra = "";
			}
		} else {
			extra2 = currentString.substring(0, 36);
			currentString = currentString.substring(36);
			System.out.print(extra2 + indentLength + indentLength + currentString + "\n");
			if (extra.equals(extra2 + currentString)) {
				extra = "";
			}
		}
		return;
	}

	public void printTitle(String line) {
		title = false;
		String temp = "";
		while (2 * temp.length() + line.length() < 80) {
			temp += " ";
		}
		temp = temp + line + temp;
		System.out.println(temp);
	}

	public void printSingleLine(String line) {
		spillOver = line;
		if (spillOver != extra) {
			if (extra.length() > 0) {
				spillOver = extra + spillOver;
				extra = "";
			}
		}
		if (indent) {
			spillOver = indentLength + spillOver;
			indent = false;
		} else if (block && !checkBlock) {
			spillOver = indentLength + indentLength + spillOver;
			testString = extra;
		}
		if (spillOver.length() >= 80) {
			currentString = spillOver.substring(0, 81);
			extra = spillOver.substring(81);
		} else {
			currentString = spillOver.substring(0);
			if (textAlign == 2) {
				String temp = "";
				while (temp.length() + currentString.length() < 80) {
					temp += " ";
				}
				currentString = temp + currentString;
				if (currentString.equals(temp + extra) || testString.equals(temp + extra)) {
					extra = "";
				}
			} else if (textAlign == 1) {
				String temp = "";
				while (2 * temp.length() + currentString.length() < 80) {
					temp += " ";
				}
				currentString = temp + currentString + temp;
				if (currentString.equals(temp + extra + temp) || testString.equals(temp + extra + temp)) {
					extra = "";
				}
			} else {
				if (currentString.equals(extra) || testString.equals(extra)) {
					extra = "";
				}
			}

		}
		System.out.print(currentString + "\n");
		return;
	}

	public String checkInitialErrors(String inputFileName, String outputFileName) {
		String errorMessage = "<html>";
		File scratch = new File(inputFileName);
		// Check to see if the input file exists
		if (!scratch.exists()) {
			errorMessage += "<font color=red>Error: An input file of this name is not found.</font><br>";
		}
		// Check to see if the input and output file names are the same
		if (outputFileName.equals(inputFileName)) {
			errorMessage += "<font color=red>Error: The input and output file names cannot be the same.</font><br>";
		}
		// Check to see if the output file has the .txt suffix
		if (outputFileName.indexOf(".txt", outputFileName.length() - 4) == -1) {
			outputFileName += ".txt";
			errorMessage += "<font color=red>Error: Output file is not specified as type txt.</font><br>";
		}
		// Check to see if the input file has the .txt suffix
		if (inputFileName.indexOf(".txt", inputFileName.length() - 4) == -1) {
			errorMessage += "<font color=red>Error: Input file is not specified as type txt.</font><br>";
		}
		// None of the conditions above are true. Return "<html></html>", meaning all is
		// clear
		errorMessage += "</html>";
		return errorMessage;
	}
}
