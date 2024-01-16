package swp4.ue01.part1.DataCollection;

public class CharacterStat {
    private int totalComparisons;
    private int successfulComparisons;

    public CharacterStat() {
        totalComparisons = 0;
        successfulComparisons = 0;
    }

    public void updateStats(boolean success) {
        totalComparisons++;
        if(success) {
            successfulComparisons++;
        }
    }

    public int getSuccessfulComparisons() {
        return successfulComparisons;
    }

    public int getFailedComparisons() {
        return totalComparisons - successfulComparisons;
    }


}
