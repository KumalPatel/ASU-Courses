/* 
 * Name: Kumal Patel
 * Class ID: 70642
 * Assignment #: 1
 * Description: Checks if a string is a palindrome ignoring formating
 */
package assign1;

public class Palindrome {
	// local variables
	private String testString;
	
	public Palindrome(String str) // initializing string to str upon object creation
	{
		testString = str;
	}
	
	public boolean isPalindrome() {
		// instance variables
		testString = testString.replaceAll("[^A-Za-z0-9]+", "").toLowerCase(); // ignores everything thats not a letter or number
		int middle = testString.length() / 2; 
		int i = 0; 
		int j = testString.length() - 1;
		int temp = 1; 
		boolean flag = true;
		
		do
		{
			if(testString.equals("")) // return true for empty string
			{
				flag = true;
				temp = 0;
			}
			
			else if(i == 0 && j == 0) // for string of size one, will go below zero otherwise
			{
				flag = true;
				temp = 0;
			}
			
			else if(testString.charAt(i) != testString.charAt(j)) // when characters on both ends don't match its not a palindrome
			{
				flag = false;
				temp = 0; // to break out of loop
			}
			
			else // increment otherwise
			{
				i++;
				j--;
			}
			
		}
		while(i != middle && j != middle && temp != 0); // stop when both indexes reach the middle or if temp = 0
		
		if(flag == true)
			return true;
		else
			return false;
}
}
	
