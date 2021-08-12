/* 
 * Name: Kumal Patel
 * Class ID: 70642
 * Assignment #: 1
 * Description: Test cases for the isPalindrome method
 */
package assign1;

import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

public class PalindromeTest {
	
	@Test
	public void test1() {
		Palindrome test = new Palindrome("RaceCa-,r"); // test punctuation
		assertTrue(test.isPalindrome());
	}
	
	@Test
	public void test2() {
		Palindrome test = new Palindrome("AB66BA"); // test normal
		assertTrue(test.isPalindrome());
	}
	
	@Test
	public void test3() {
		Palindrome test = new Palindrome(""); // test empty string
		assertTrue(test.isPalindrome());
	}
	
	@Test
	public void test4() {
		Palindrome test = new Palindrome("hAn()#$_%@__-()naH"); // test punctuation and case
		assertTrue(test.isPalindrome());
	}
	
	@Test
	public void test5() {
		Palindrome test = new Palindrome("AB674BA"); // test false condition
		assertFalse(test.isPalindrome());
	}
	
	@Test
	public void test6() {
		Palindrome test = new Palindrome("A"); // test one letter
		assertTrue(test.isPalindrome());
	}
}