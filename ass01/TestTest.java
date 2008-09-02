package test;

import org.junit.*;
import static org.junit.Assert.*;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Collections;
import java.util.Scanner;
import java.util.Vector;

public class TestTest {
	private String src = "test.dat";
	private String dst = "test.out";
	@Test
	public void fileExist() {
		File file = new File(src);
		assertTrue(file.exists());
	}
	
	@Test
	public void readFile() throws IOException
	{
		FileReader fin = new FileReader(src);
	    Scanner scanner = new Scanner(fin);
	    assertEquals(2, scanner.nextInt());
	    scanner.close();
	    fin.close();
	}
	
	@Test
	public void writeFile() throws IOException
	{
		FileWriter fout = new FileWriter(dst);
	    fout.write("1");
	    fout.close();
	    
	    FileReader fin = new FileReader(dst);
	    Scanner scanner = new Scanner(fin);
	    assertEquals(1, scanner.nextInt());
	    scanner.close();
	    fin.close();
	}
	
	@Test
	public void sortArray()
	{
		Vector<Integer> v = new Vector<Integer>();
		v.add(4);
		v.add(6);
		v.add(3);
		v.add(2);
		v.add(8);
		v.add(5);
		assertEquals(6, v.size());
		
		Collections.sort(v);
		
		int indx = 0;
		assertEquals(2, v.get(indx++));
		assertEquals(3, v.get(indx++));
		assertEquals(4, v.get(indx++));
		assertEquals(5, v.get(indx++));
		assertEquals(6, v.get(indx++));
		assertEquals(8, v.get(indx++));
	}
	
	@Test
	public void algorithm()
	{
		Vector<Integer> v = new Vector<Integer>();
		v.add(2);
		v.add(3);
		v.add(4);
		v.add(5);
		v.add(6);
		v.add(8);
		
		Vector<Integer> result = algorithm(v);
		assertEquals(1, result.size());
		assertEquals(7, result.get(0));
	}
	
	@Test
	public void testData() throws IOException
	{
		suite("1");
		suite("2");
		suite("3");
		suite("4");
	}

	private void suite(String test) throws IOException {
		Vector<Integer> input = readInput(test+".inp");
		Vector<Integer> output = readOutput(test+".out");
	    Collections.sort(input);
	    Vector<Integer> result = algorithm(input);
	    assertArrayEquals(output.toArray(), result.toArray());
	}

	private Vector<Integer> readOutput(String file) throws IOException {
		Vector<Integer> v = new Vector<Integer>();
		FileReader fin = new FileReader(file);
	    Scanner scanner = new Scanner(fin);
	    while(scanner.hasNext())
	    	v.add(scanner.nextInt());
	    scanner.close();
	    fin.close();
	    return v;
	}

	private Vector<Integer> readInput(String file) throws IOException {
		int min, max;
		Vector<Integer> v = new Vector<Integer>();
		FileReader fin = new FileReader(file);
	    Scanner scanner = new Scanner(fin);
	    min = scanner.nextInt();
	    max = scanner.nextInt();
	    while(scanner.hasNext())
	    	v.add(scanner.nextInt());
	    assertTrue(min<v.get(0));
	    assertTrue(max>v.get(v.size()-1));
	    scanner.close();
	    fin.close();
	    return v;
	}
	private Vector<Integer> algorithm(Vector<Integer> v) {
		Vector<Integer> result = new Vector<Integer>();
		for(int i = 0; i<v.size()-1; i++)
		{
			int now = v.get(i);
			int next = v.get(i+1);
			if(next-now>1)
			{
				for(int j = now+1; j<next; j++)
				{
					result.add(j);
				}
			}
		}
		return result;
	}
}
