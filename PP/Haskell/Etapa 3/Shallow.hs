{-# LANGUAGE TupleSections #-}
module Shallow where

import Debug.Trace
import Data.Tuple (swap)
import Data.List (mapAccumL)
import Data.List hiding (union)

import qualified Data.Set as S
import qualified Data.Sequence as Seq

{-
    Punct bidimensional, reprezentat ca pereche de coordonate reale (x, y).
    type introduce un sinonim de tip, similar cu typedef din C.
-}
type Point = (Float, Float)

{-
    Tip de funcție care primește un punct, și este parametrizat în raport
    cu tipul rezultatului.
-}
type Pointed a = Point -> a

{-
    Regiune bidimensională, reprezentată ca o funcție caracteristică
    (Point -> Bool). Pentru un punct care aparține regiunii, se întoarce True;
    altfel, False.
-}
type Region = Pointed Bool

{-
    Transformare bidimensională, reprezentată ca o funcție peste puncte.
-}
type Transformation = Point -> Point


inside :: Point -> Region -> Bool
inside = flip ($)

fromPoints :: [Point] -> Region
fromPoints = flip $ elem

rectangle :: Float -> Float -> Region
rectangle width height = \point -> let
                                      (x, y) = point
                                      half_w = width / 2
                                      half_h = height / 2
                                   in
                                      (-half_w <= x && x <= half_w) && -- x <= |width / 2|
                                      (-half_h <= y && y <= half_h)    -- y <= |height / 2|

circle :: Float -> Region
circle radius = \point -> let
                             (x, y) = point
                             sqr_x = x * x
                             sqr_y = y * y
                             r = radius * radius
                          in
                             sqr_x + sqr_y <= r -- sqrt(x^2 + y^2) <= radius

plot :: Int -> Int -> Region -> String
plot width height region = let
                              ox = [-width .. width]            -- limitez axa OX
                              oy = reverse [-height .. height]  -- limitez axa OY
                           in
                             intercalate "\n"
                                    [concat [ppoint x y | x <- ox] | y <- oy]
                                    where
                                        ppoint x y = let -- caut interiorul
                                                        p_inside = region (fromIntegral x,
                                                                           fromIntegral y)
                                                     in
                                                       if p_inside then "*" else "."

{-
    Utilizați această funcție pentru vizualizarea diagramelor,
    după ce implementați funcția plot.
-}
printPlot :: Int -> Int -> Region -> IO ()
printPlot width height region = putStrLn $ plot width height region

promoteUnary :: (a -> b) -> Pointed a -> Pointed b
promoteUnary = \f1 f2 -> f1 . f2

promoteBinary :: (a -> b -> c) -> Pointed a -> Pointed b -> Pointed c
promoteBinary f p1 p2 point = f (p1 point) (p2 point)

complement :: Region -> Region
complement = promoteUnary not   -- practic vreau exteriorul, nu interiorul

union :: Region -> Region -> Region
union = promoteBinary (||)      -- adunarea in matematica e "sau" logic

intersection :: Region -> Region -> Region
intersection = promoteBinary (&&)  -- partea comuna e "si" logic

translation :: Float -> Float -> Transformation
translation tx ty = \point -> let
                                 (x, y) = point
                              in
                                (x - tx, y - ty)

scaling :: Float -> Transformation
scaling factor = \point -> let
                              (x, y) = point
                           in
                             if factor /= 0                 -- verific cazul in care factor e 0 pentru o alta etapa
                             then (x / factor, y / factor)  -- factor != 0
                             else undefined                 -- undefined in cazul in care am nevoie pt debug

applyTransformation :: Transformation -> Region -> Region
applyTransformation = flip (.)


combineTransformations :: [Transformation] -> Transformation
combineTransformations = foldr (\f1 f2 -> f2 . f1) id

{-
    *** TODO ***

    Funcția circles de mai jos generează o regiune formată din n cercuri de rază
    2, translatate succesiv cu 6 unități pe orizontală.

    Explicați la prezentare utilitatea evaluării leneșe pentru determinarea
    eficientă a apartenenței unui punct la regiunea construită prin reuniune.

    Hint: utilizați trace (vezi laboratorul 7) în funcția circle pentru afișarea
    punctului primit ca parametru și evaluați expresiile de mai jos:
    > inside (0, 0) $ circles 3
    > inside (6, 0) $ circles 3
    > inside (12, 0) $ circles 3
    > inside (18, 0) $ circles 3

    Exemple:

    > printPlot 15 3 $ circles 3
    ...............................
    ...............*.....*.....*...
    ..............***...***...***..
    .............*****.*****.*****.
    ..............***...***...***..
    ...............*.....*.....*...
    ...............................

    Răspuns: ...............
-}
circles :: Int -> Region
circles n
    | n <= 0    = const False
    | otherwise = union (circle 2)
                        (applyTransformation (translation 6 0)
                                             (circles (n - 1)))

{-
    *** TODO ***

    Explicați la prezentare cum se comportă reuniunea infinită de mai jos
    când se verifică apartenența unui punct care NU aparține regiunii.

    Răspuns: ...............
-}
infiniteCircles :: Region
infiniteCircles = union (circle 2)
                        (applyTransformation (translation 6 0)
                                             infiniteCircles)

bfs :: (Ord a) => a -> (a -> [a]) -> [(a, Int)]
bfs start expand =
    let -- initializare coada noduri + elemente vizitate
       empty_queue = (pure (start, 0))
       is_visited = S.empty

       -- functia bfs pe bune
       bfs_aux q vis = if Seq.EmptyL == Seq.viewl q
                       then []
                       else
                            let  -- vad cum este urmatorul nod
                               (idx, dist) Seq.:< qs = Seq.viewl q
                            in
                              if idx `S.member` vis  -- daca il am deja, nu ma intereseaza
                              then bfs_aux qs vis    -- altfel caut urmatorii vecini
                              else (idx, dist) : bfs_aux new_q (S.insert idx vis)  -- nod pe distanta minima
                                    where
                                         (idx, dist) Seq.:< qs = Seq.viewl q    -- ca sa fie vazut in scope
                                         neigh = [(id, dist + 1) | id <- expand idx]  -- vecinii
                                         new_q = (qs Seq.>< (Seq.fromList neigh))     -- ii pun in rezultat
    in
      bfs_aux empty_queue is_visited

regionAvoidingBfs :: Point -> Region -> [(Point, Int)]
regionAvoidingBfs start region =
  let
    next :: Point -> [Point]
    next point =
        let
            (x, y) = point
            reg = [(x + 1, y), (x, y + 1),  -- daca intr-un patrat 2x2 nu exista,
                   (x - 1, y), (x, y - 1)]  -- atunci trebuie adaugat ca sa nu se extinda
        in
          filter (\p -> not $ region p) reg
  in
    bfs start next