public class IntegerMatrix extends AMatrix<Integer> {

    private Integer[][] mat;

    public IntegerMatrix(Integer[][] mat) {
        this.mat = mat;
    }

    @Override
    public AMatrix<Integer> addition(AMatrix<Integer> m1) {
        IntegerMatrix mat1 = (IntegerMatrix) m1;

        if(mat.length != mat1.mat.length || mat[0].length != mat1.mat[0].length) {
            System.out.println("Invalid matrix size");
            return null;
        }

        IntegerMatrix result = new IntegerMatrix(new Integer[this.mat.length][this.mat[0].length]);

        for(int i = 0; i < mat.length; i++)
            for(int j = 0; j < mat[0].length; j++)
                result.mat[i][j] = this.mat[i][j] + mat1.mat[i][j];

        return result;
    }

    @Override
    public String toString() {
        String result = "";

        for(Integer[] row : mat) {
            for(Integer value : row) result += value + " ";
            result += '\n';
        }

        return result;
    }

    @Override
    public Integer sum(Integer obj1, Integer obj2) {
        return obj1 + obj2;
    }

    public static void main(String[] args) {
        Integer[][] matrix1 = {{7, 23, 1}, {-23, 4, 6}, {23, 121, 12}};
        Integer[][] matrix2 = {{91, 765, 247}, {26, -215, 24}, {43, 223, 111}};

        IntegerMatrix integerMatrix1 = new IntegerMatrix(matrix1);
        IntegerMatrix integerMatrix2 = new IntegerMatrix(matrix2);

        System.out.println("A:\n" + integerMatrix1 + "==========================");
        System.out.println("B:\n" + integerMatrix2 + "==========================");

        AMatrix<Integer> result = integerMatrix1.addition(integerMatrix2);
        System.out.println("A + B:\n" + result + "==========================");

        Integer sum = integerMatrix1.sum(5, 10);
        System.out.println("Sum: " + sum);
    }
}
