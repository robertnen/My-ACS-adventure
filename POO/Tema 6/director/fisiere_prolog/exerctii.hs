produs_cartezian::[Int] -> [Int] -> [(Int, Int)]
produs_cartezian l1 l2 = [(x, y) | x <- l1, y <- l2]

f x = [(y, y) | (y, z, t) <- x, y == z]

functie_exemplu:: Int -> Int -> Int
functie_exemplu a b
	| a > 0 && b > 0 = a + b
	| a < 0 && b < 0 = a * b
	| a > 0 && b < 0 = a - b
	| otherwise = 0

replicate2::(Integral i) => i -> a -> [a]
replicate2 n x
	| n <= 0 = []
	| otherwise = x:replicate2 (n - 1) x

reverse1 [] = [];
reverse1 (x:xs) = reverse1(xs) ++ [x];

repeat1 n x 
	| n <= 0 = []
	| otherwise = x:repeat1 (n-1) x

add_three = \x -> \y -> \z -> x + y + z

f_examen x y = (x y) y

ultimul_element [x] = x
ultimul_element (x:xs) = ultimul_element(xs)

element_at list poz = list !! poz

my_length list
	| list == [] = 0
	| otherwise = my_length (tail list) + 1

my_length1 list = foldl (\x y -> x + 1) 0 list

my_reverse list = foldr (\x y -> y ++ [x]) [] list

intersectie list1 list2 = [x | x <- list1, x `elem` list2]


palindrome list = list == list1
	where
		list1 = my_reverse list


duplicare_elemente list = foldr (\x acc -> x:x:acc) [] list

lista_pare list = [ x | x <- list, x `mod` 2 == 0]
lista_impare list = [x | x <- list, x `mod` 2 == 1]
eliminare_duplicate list = foldr (\x acc -> if x `elem` acc then acc else x:acc) [] list
split1 list = [eliminare_duplicate $ lista_pare list, eliminare_duplicate $ lista_impare list]
split list = [eliminare_duplicate (filter (\x -> x `mod` 2 == 0) list), eliminare_duplicate (filter (\x -> x `mod` 2 == 1) list)]

not_special x = if x == 2 then 1 else 2
negare_secventa list = map not_special list
