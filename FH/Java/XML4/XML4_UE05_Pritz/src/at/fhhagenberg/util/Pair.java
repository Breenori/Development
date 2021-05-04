package at.fhhagenberg.util;

public class Pair<V1, V2> {

	private V1 first;
	private V2 second;

	public Pair() {
	}

	public Pair(V1 first, V2 second) {
		super();
		this.first = first;
		this.second = second;
	}

	public V1 getFirst() {
		return first;
	}

	public void setFirst(V1 first) {
		this.first = first;
	}

	public V2 getSecond() {
		return second;
	}

	public void setSecond(V2 second) {
		this.second = second;
	}

}
