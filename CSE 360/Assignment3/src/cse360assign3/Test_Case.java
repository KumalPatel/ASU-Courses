package cse360assign3;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class Test_Case {

	@Test
	void test() {
		Calculator obj1 = new Calculator();
		obj1.add(5);
		obj1.add(2);
		obj1.mult(3);
		//obj1.div(3);
		obj1.div(0);
		obj1.power(2);
		//obj1.power(-1);
		System.out.println(obj1.toString() + " = " + obj1.getTotal());
		
	}

}
