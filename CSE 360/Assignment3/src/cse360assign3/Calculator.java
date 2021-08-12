package cse360assign3;

public class Calculator extends AddingMachine{ // inheriting AddingMachine (AddingMachine is the parent class to Calculator)
	
	public void mult(int value) // multiplies value and adds it to total
	{
		total *= value;
		result += " * " + value;
	}
	
	public void div(int value)  // divides by value and adds that to total
	{
		try
		{
			total /= value;
			result += " / " + value;
		}
		catch(Exception e)
		{
			result += " / " + value;
			total = 0;
		}
		
	}
	
	public void power(int value) // raise number to power of value
	{
		if(value < 0)
		{
			result += " ^ " + value;
			total = 0;
		}
		else
		{
			total = (int) Math.pow(total , value);
			result += " ^ " + value;
		}
	}
}
