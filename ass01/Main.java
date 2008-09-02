import java.io.*;
import java.util.*;
public class Main {
	public static void main(String[] args) throws IOException {
		String in = "missing.inp";
		String out = "missing.out";
		Vector<Integer> v = new Vector<Integer>();
		Scanner scnr = new Scanner(new FileReader(in));
		FileWriter fo = new FileWriter(out);
	    scnr.nextInt();scnr.nextInt();
	    while(scnr.hasNext())
	    	v.add(scnr.nextInt());
	    Collections.sort(v);
		for(int i = 0; i<v.size()-1; i++)
		{
			int nw = v.get(i);
			int nxt = v.get(i+1);
			if(nxt-nw>1)
				for(int j = nw+1; j<nxt; j++)
					fo.write(j+"\n");
		}
		fo.close();
	}
}
