import java.util.ArrayList;

public class GenericListMethods implements GenericInterface {

    @Override
    public <E extends Comparable<E>> ArrayList<E> removeDuplicates(ArrayList<E> list) {
        ArrayList<E> uList = new ArrayList<>();
        for(E element : list)
            if(!uList.contains(element)) uList.add(element);

        return uList;
    }

    @Override
    public <E extends Comparable<E>> E max(ArrayList<E> list) {
        if(list.isEmpty()) return null;

        E maxim = list.get(0);
        for(E element : list)
            if(element.compareTo(maxim) > 0) maxim = element;

        return maxim;
    }

    @Override
    public <E extends Comparable<E>> int binarySearch(ArrayList<E> list, E x, int left, int right) {
        if(left > right) return -1;

        int mid = (left + right) / 2;
        if (list.get(mid).equals(x)) return mid;
        else if (list.get(mid).compareTo(x) > 0) return binarySearch(list, x, left, mid - 1);
        else return binarySearch(list, x, mid + 1, right);
    }

    public static void main(String[] args) {
        ArrayList<Integer> iList = new ArrayList<>();

        iList.add(1);
        iList.add(2);
        iList.add(3);
        iList.add(2);
        iList.add(4);
        iList.add(3);

        System.out.println("iList (before): " + iList);

        GenericListMethods genericListMethods = new GenericListMethods();
        iList = genericListMethods.removeDuplicates(iList);
        System.out.println("iList (after - unique): " + iList);

        ArrayList<Double> dList = new ArrayList<>();

        dList.add(0.1);
        dList.add(0.2);
        dList.add(0.3);
        dList.add(0.14);
        dList.add(0.23);

        System.out.println("dList: " + dList);
        Double dMaxim = genericListMethods.max(dList);
        System.out.println("Maxim in dList: " + dMaxim);

        ArrayList<String> sList = new ArrayList<>();

        sList.add("mar");
        sList.add("banana");
        sList.add("portocala");
        sList.add("pruna");
        sList.add("capsuna");
        sList.add("strugure");

        System.out.println("sList: " + sList);

        int i = genericListMethods.binarySearch(sList, "portocala", 0, sList.size() - 1);

        if (i != -1) System.out.println("Pozitie portocala: " + i);
        else System.out.println("Nu mai sunt portocale");

        i = genericListMethods.binarySearch(sList, "kiwi", 0, sList.size() - 1);

        if (i != -1) System.out.println("Pozitie kiwi: " + i);
        else System.out.println("Nu exista kiwi");
    }
}