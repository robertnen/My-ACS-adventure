public class Problema5 {

    private String addStars(String word) {
        int len = word.length();
        for(int i = 2; i < len; i++) word = word.substring(0, i - 1) + '*' + word.substring(i);
        return word;
    }

    public String cenzurare(String text, String words[]) {
        int index;
        boolean isSus = false;
        for(String word : words) {
            index = text.indexOf(word);
            if(index != -1) {
                System.out.println("Text suspect");
                isSus = true;
                break;
            }
        }
        if(!isSus) System.out.println("Nimic suspect");

        String[] textWords = text.split(" ");

        String result = "";

        for(String textWord : textWords) {
            isSus = false;
            for(String word : words) if(textWord.equals(word)) {isSus = true; break;}
            result += (isSus ? addStars(textWord) : textWord) + " ";
            }

        return result;
    }
}
