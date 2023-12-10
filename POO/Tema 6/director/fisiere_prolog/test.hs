import GHC.Float

f = \x y -> x + y
g x y = x + y
factorial_1 x = 
	if x < 1 then
		1
	else
		x * factorial_1(x - 1)

factorial_guards x
	| x < 1 = 1
	| otherwise = x * factorial_guards (x - 1)

factorial_mihai x
	| x < 1 = 1
	| otherwise = x * factorial_mihai(x - 1)

diff x y = l - s
	where
		l = if x > y then x else y
		s = if x < y then x else y

divizibil:: Int -> Int -> Bool
divizibil d n = rem n d == 0

prim_auxiliar x nr 
	| nr == 1 = True
	| nr == 2 = True
	| otherwise = not(divizibil x nr) && prim_auxiliar x (nr - 1)

prim x
	| x == 1 = True
	| otherwise = prim_auxiliar x (x - 1)

prim_functionale x = elem x (filter prim [x | x <- [1..100]])

minimLista:: [Int] -> Int
minimLista [] = error "lista vida"
minimLista [x] = x
minimLista (x:xs) = min x (minimLista xs)

prim_bun x 
	| x == 1 = True
	| x == 2 = True
	| otherwise = not(elem 0 (map f [y | y <- [2 .. (x - 1)], y < x]))
		where
			f = rem x

element_maxim:: [Int] -> Int
element_maxim list = foldl f 0 list
	where
		f = max

remove x list = filter f list
	where
		f = (x /=)

check list list2 = elem (length list2) list

exercitiu::[[Int]] -> [Int] -> [[Int]]
exercitiu l1 l2 = filter f l1
	where
		f = check l2

produs_cartezian list1 list2 = [(x, y) | x <- list1, y <- list2]
flux = map (\x -> 2*x) [0 ..]

check_lista list = 
	if rem (head list) 2 == 0 then 
		False 
	else 
		True

exercitiu1::[[Int]] -> [[Int]]
exercitiu1 lista = filter check_lista lista

exercitiu2::Int -> [Int] -> [Int]
exercitiu2 x lista = filter f lista
	where
		f = (x <) 

media_aritmetica::[Int] -> Float
media_aritmetica lista = 
	if lista == [] then
		error "lista vida"
	else
		fromInt(nr1) / fromInt(nr2)
		where
			nr1 = foldl (+) 0 lista
			nr2 = length lista