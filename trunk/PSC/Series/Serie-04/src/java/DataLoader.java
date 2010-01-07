import java.io.*;

public abstract class DataLoader<ItemType> {

	protected abstract ItemType[] newArray(int numEntries);
	protected abstract ItemType newInstance(String[] elems);

	private BufferedReader input;
	
	public ItemType[] loadFrom(String filename) throws IOException {
		input = new BufferedReader(new FileReader(filename));
		ItemType[] res = build(0);
		input.close();
		return res;
	}

	private ItemType[] build(int n) throws IOException {
		ItemType item = null;
		String line = input.readLine();
		if (line == null) return newArray(n);
		String [] elems = line.split("\\|");
		if (elems.length>0 && elems[0].length()>0) {
			for(int i=0 ; i<elems.length ; ++i)
				elems[i] = elems[i].trim();
			item = newInstance(elems);
		}
		if (item != null) {
			ItemType[] items = build(n + 1);
			items[n] = item;
			return items;
		}
		return build(n);
	}
}
