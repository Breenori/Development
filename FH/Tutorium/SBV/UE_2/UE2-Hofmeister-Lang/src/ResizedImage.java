public class ResizedImage {

    private int[][] image;
    private int width;
    private int height;

    public ResizedImage(int width, int height) {
        this.width = width;
        this.height = height;
        this.image = new int[width][height];
    }

    public void setImage(int[][] image) {
        this.image = image;
    }

    public int[][] getImage() {
        return this.image;
    }

    public int getWidth() {
        return this.width;
    }

    public int getHeight() {
        return this.height;
    }
}
