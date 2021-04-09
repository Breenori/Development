package swp4.ue01.part2.collections;

public class MovieNode {
    private String value;
    private boolean movie;

    // create a movienode
    public MovieNode(String value, boolean movie) {
        this.value = value;
        this.movie = movie;
    }

    // return the nodes value
    public String getValue() {
        return value;
    }
    // return whether the node is a movie or not
    public boolean isMovie() {
        return movie;
    }
}
