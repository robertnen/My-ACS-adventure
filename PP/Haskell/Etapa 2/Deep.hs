module Deep where

import Shallow (Point, Region, Transformation)
import qualified Shallow as S

{-
    Deep embeddings pentru regiuni și transformări. Fiecare regiune
    și transformare este reprezentată sub forma unui arbore sintactic
    (abstract syntax tree, AST) ce descrie secvența de operații care contribuie
    la construcția acelei regiuni sau transformări. De exemplu, expresia
    (circles 2), unde circles a fost definită în etapa 1, ar produce acum
    un rezultat similar cu

    Union (Circle 2.0) (Transform (Translation 6.0 0.0) (Circle 2.0)).

    Pentru a obține acest efect, toate funcțiile din etapa 1 sunt reimplementate
    astfel încât să utilizeze direct constructorul de date potrivit al unui
    tip de date. De exemplu, funcția fromPoints *este* acum constructorul
    FromPoints.

    Primul avantaj major al reprezentării bazate pe AST-uri este posibilitatea
    interpretării acesteia în diverse moduri pentru a reconstitui semnificații
    concrete variate ale regiunilor și transformărilor, e.g. regiuni ca funcții
    caracteristice, și transformări ca funcții pe puncte, ca în etapa 1.
    Vom vedea și alte semnificații concrete în etapa 3.

    Al doilea mare avantaj îl constituie posibilitatea simplificării AST-ului
    înaintea interpretării lui într-o manieră specifică. Observați deja cum
    funcțiile combineTransformations și applyTransformation de mai jos, văzute
    ca smart constructors, recunosc anumite cazuri particulare și simplifică
    AST-ul încă de la construcție.
-}
data RegionAST
    = FromPoints [Point]
    | Rectangle Float Float
    | Circle Float
    | Complement RegionAST
    | Union RegionAST RegionAST
    | Intersection RegionAST RegionAST
    | Transform TransformationAST RegionAST
    deriving (Show, Eq)

data TransformationAST
    = Translation Float Float
    | Scaling Float
    | Combine [TransformationAST]
    deriving (Show, Eq)

fromPoints :: [Point] -> RegionAST
fromPoints = FromPoints

rectangle :: Float -> Float -> RegionAST
rectangle = Rectangle

circle :: Float -> RegionAST
circle = Circle

complement :: RegionAST -> RegionAST
complement = Complement

union :: RegionAST -> RegionAST -> RegionAST
union = Union

intersection :: RegionAST -> RegionAST -> RegionAST
intersection = Intersection

translation :: Float -> Float -> TransformationAST
translation = Translation

scaling :: Float -> TransformationAST
scaling = Scaling


combineTransformations :: [TransformationAST] -> TransformationAST
combineTransformations [transformation] = transformation
combineTransformations transformations = Combine transformations


applyTransformation :: TransformationAST -> RegionAST -> RegionAST
applyTransformation (Combine []) region = region
applyTransformation transformation region = Transform transformation region


toTransformation :: TransformationAST -> Transformation
toTransformation (Translation x y) = S.translation x y
toTransformation (Scaling factor) = S.scaling factor
toTransformation (Combine transformations) = S.combineTransformations (map toTransformation transformations)


toRegion :: RegionAST -> Region
toRegion (FromPoints points) = S.fromPoints points
toRegion (Rectangle width height) = S.rectangle width height
toRegion (Circle r) = S.circle r
toRegion (Complement reg) = S.complement (toRegion reg)
toRegion (Union a b) = S.union (toRegion a) (toRegion b)
toRegion (Intersection a b) = S.intersection (toRegion a) (toRegion b)
toRegion (Transform trans reg) = S.applyTransformation (toTransformation trans) (toRegion reg)


inside :: Point -> RegionAST -> Bool
inside = flip toRegion


decomposeTransformation :: TransformationAST -> [TransformationAST]
decomposeTransformation (Translation x y) = [Translation x y]
decomposeTransformation (Scaling factor) = [Scaling factor]
decomposeTransformation (Combine trans) = concatMap decomposeTransformation trans


fuseTransformations :: [TransformationAST] -> [TransformationAST]
fuseTransformations [] = []
fuseTransformations [t] = [t]
fuseTransformations (t1@(Translation x1 y1) : t2@(Translation x2 y2) : ts) =
        fuseTransformations (Translation (x1 + x2) (y1 + y2) : ts)

fuseTransformations (t1@(Scaling factor1) : t2@(Scaling factor2) : ts) =
        fuseTransformations (Scaling (factor1 * factor2) : ts)

fuseTransformations (t : ts) = t : fuseTransformations ts


-- verific daca pot combina doua translatari sau mariri
canOptimize (Translation x1 y1) (Translation x2 y2) = x1 - x2 == 0 && y1 - y2 == 0
canOptimize (Scaling factor1) (Scaling factor2) = factor1 == factor2
canOptimize _ _ = False


-- verific daca am doua liste si in functie de conditie de optimizare le impart
getCommon ls1 ls2 _
    | null ls1 || null ls2 = []

getCommon (e1 : ls1) (e2 : ls2) False = getCommon ls1 ls2 False
getCommon (e1 : ls1) (e2 : ls2) True
    | canOptimize e1 e2 = e1 : getCommon ls1 ls2 True
    | otherwise = getCommon ls1 ls2 False


-- in functie de operatii le imbin pentru a avea mai putine apelari de functii
unify (Transform (Scaling factor) r1) (Transform (Scaling aux_s) r2) = (Transform (Scaling $ factor * aux_s) r2)
unify (Transform (Translation x1 y1) r1) (Transform (Translation x2 y2) r2) = (Transform (Translation (x1 + x2) (y1 + y2)) r2)
unify (Transform e@(Combine elems) r1) (Transform op r2) = (Transform (fused (Combine $ elems ++ [op])) r2)
    where
        fused t@(Combine l) = Combine $ fuseTransformations . decomposeTransformation $ t
        fused x = x

unify (Transform op r1) (Transform (Combine elems) r2) = (Transform (fused (Combine $ [op] ++ elems)) r2)
    where
        fused t@(Combine l) = Combine $ fuseTransformations . decomposeTransformation $ t
        fused x = x

unify (Transform f1 r1) (Transform f2 r2) = (Transform f1 r2)


-- verific daca mai am elemente de unit
unifyCombine elem@(Transform (Combine l) reg) = case length l of
    1 -> Transform (head l) reg
    0 -> reg
    _ -> elem


-- daca am doua transformari le pot uni
fuseTrans reg1@(Transform t reg2@(Transform _ r)) = unify reg1 reg2
fuseTrans trans@_ = trans


-- pentru optimizare, pun transformarile la incepu sa sa fie unite mai tarziu
revOpt (Complement (Transform t reg)) = Transform t (Complement reg)
revOpt (Complement reg) = Complement $ reg


-- optimizeaza arborele apeland functiile auxiliare de mai sus
treeOPT :: RegionAST -> RegionAST
treeOPT region = case (fuseTrans region) of
    (Complement reg) -> revOpt $ Complement $ treeOPT $ reg
    (Union st dr) -> prefix $ (Union (treeOPT st) (treeOPT dr))
    tra@(Transform t reg) -> fuseTrans $ unifyCombine $ operation tra
    (Intersection st dr) -> prefix $ (Intersection (treeOPT st) (treeOPT dr))
    _ -> region

    where
        operation transform@(Transform t reg) = case tr_func == toOpt of
            True -> Transform toOpt (treeOPT reg)
            _ -> treeOPT $ Transform tr_func r

            where
                toOpt = Combine $ fuseTransformations . decomposeTransformation $ t
                Transform tr_func r = fuseTrans $ Transform toOpt reg


        -- caut partea comuna pentru operatia de intersectie
        prefix i@(Intersection f1@(Transform t1 r1) f2@(Transform t2 r2)) =
                unifyCombine (Transform cop (Intersection reg1 reg2))
            where
                decT1 = decomposeTransformation t1
                decT2 = decomposeTransformation t2
                common = getCommon decT1 decT2 True
                reg1 = unifyCombine (Transform (Combine $ drop (length common) decT1) r1)
                reg2 = unifyCombine (Transform (Combine $ drop (length common) decT2) r2)
                cop = Combine $ common


        -- caut partea comuna pentru operatia de uniune
        prefix u@(Union f1@(Transform t1 r1) f2@(Transform t2 r2)) =
                unifyCombine (Transform cop (Union reg1 reg2))
            where
                decT1 = decomposeTransformation t1
                decT2 = decomposeTransformation t2
                common = getCommon decT1 decT2 True
                reg1 = unifyCombine $ operation (Transform (Combine $ drop (length common) decT1) r1)
                reg2 = unifyCombine $ operation (Transform (Combine $ drop (length common) decT2) r2)
                cop = Combine $ common

        prefix e@_ = e


-- functie optimize asteptata
optimizeTransformations :: RegionAST -> RegionAST
optimizeTransformations region = treeOPT region
