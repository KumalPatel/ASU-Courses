/* 
 * Name: Kumal Patel
 * Class ID: 70642
 * Assignment #: 2
 * Description: Test Cases
 */
package cse360assign2;

import org.junit.jupiter.api.Test;

class Testing {

	@Test
	void test1() { // checking positive results
		AddingMachine obj = new AddingMachine();
		obj.add(4);
		obj.subtract(2);
		obj.add(5);
		System.out.println(obj.toString() + " = " + obj.getTotal());
	}
	
	@Test
	void test2() { // checking negative results
		AddingMachine obj = new AddingMachine();
		obj.subtract(2);
		obj.add(18);
		obj.subtract(27);
		System.out.println(obj.toString() + " = " + obj.getTotal());
	}

}
