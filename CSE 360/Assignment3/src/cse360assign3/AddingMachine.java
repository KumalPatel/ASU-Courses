/*
 * Name: Kumal Patel
 * Class ID: 70642
 * Assignment #: 3
 * Description: A machine that returns the process of using add/sub operators
 */

package cse360assign3;

public class AddingMachine {
	// local variables
	protected int total;
	protected String result;
	
	public AddingMachine () { // Initializes local variables
		total = 0;  // not needed - included for clarity
		result = Integer.toString(0); // Initializes to "0"
	}
	
	public int getTotal () { // returns total
		return total;
	}
	
	public void add (int value) { // adds value to total
		total += value; 
		result += " + " + value;
	}
	
	public void subtract (int value) { // subtracts value from total
		total -= value;
		result += " - " + value;
	}
		
	public String toString () { // returns the process of using operators 
		return result;
	}

	public void clear() { // clears total value
		total = 0;
		result = "";
	}
}
