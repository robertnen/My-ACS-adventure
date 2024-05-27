{-# OPTIONS_GHC -Wno-missing-methods #-}
module Folds where

import Shallow (Point, Region, Transformation)
import Data.List (intercalate)
import qualified Shallow as S

{-
    Contructor de tip care surprinde regiunile elementare și modalitățile
    generice de construcție a regiunilor complexe (Complement etc.). Spre
    deosebire de etapa 2, în care constructorul de tip RegionAST nu era
    parametrizat, constructorul RegionShape este acum parametrizat cu un tip
    generic de informație, a, care înlocuiește referirile recursive la tipul
    RegionAST. De exemplu, (Complement RegionAST) din etapa 2 devine acum
    (Complement a). Cuvântul „shape” din numele tipului vizează formele generice
    (Complement, Union etc.) pe care le pot lua valorile acestui tip, fără
    a fixa tipul câmpurilor. Așa cum vom vedea în continuare, acest artificiu
    permite atât recuperarea tipului recursiv RegionAST, cât și implementarea
    unui mecanism generic de folding (reducere) al valorilor acestui tip.
-}
data RegionShape a
    = FromPoints [Point]
    | Rectangle Float Float
    | Circle Float
    | Complement a
    | Union a a
    | Intersection a a
    | Transform TransformationAST a
    deriving (Show, Eq)

{-
    Contructor de tip care surprinde transformările elementare și o variantă
    generică de construcție a transformărilor complexe (Combine). Explicațiile
    referitoare la RegionShape sunt valabile și aici.
-}
data TransformationShape a
    = Translation Float Float
    | Scaling Float
    | Combine [a]
    deriving (Show, Eq)

{-
    Tipul recursiv RegionAST din etapa 2 se poate recupera particularizând
    tipul a din definiția constructorului RegionShape la... RegionAST însuși.
    Cu alte cuvinte, RegionAST este un punct fix al constructorului de tip
    RegionShape, adică RegionAST = RegionShape RegionAST (egalul ar trebui citit
    mai degrabă ca „izomorf cu” în loc de „identic cu”, din perspectiva
    limbajului). Vă puteți convinge de relația de mai sus substituind textual
    aparițiile lui a din definiția lui RegionShape cu RegionAST; de exemplu,
    (Complement a) devine (Complement RegionAST).

    newtype este similar cu data, în sensul că definește un tip nou, dar poate
    fi folosit doar când precizăm un unic constructor de date (R de mai jos),
    care posedă un unic câmp (având mai jos tipul (RegionShape RegionAST)).
    Există și alte diferențe subtile pe care nu le vom detalia, dar îl puteți
    folosi în continuare ca pe un data obișnuit.
-}
newtype RegionAST
    = R (RegionShape RegionAST)
    deriving (Eq)

{-
    Similar se poate recupera și tipul TransformationAST din etapa 2.
-}
newtype TransformationAST
    = T (TransformationShape TransformationAST)
    deriving (Eq)

{-
    Funcțiile pe regiuni și transformări au implementări foarte similare celor
    din etapa 2, singura diferență constând în apariția constructorilor de date
    R și T de mai sus, pentru a reflecta noile definiții ale tipurilor RegionAST
    și TransformationAST în termenii constructorilor de tip RegionShape,
    respectiv TransformationShape.
-}
fromPoints :: [Point] -> RegionAST
fromPoints = R . FromPoints

rectangle :: Float -> Float -> RegionAST
rectangle width height = R $ Rectangle width height

circle :: Float -> RegionAST
circle = R . Circle

complement :: RegionAST -> RegionAST
complement = R . Complement

union :: RegionAST -> RegionAST -> RegionAST
union region1 region2 = R $ Union region1 region2

intersection :: RegionAST -> RegionAST -> RegionAST
intersection region1 region2 = R $ Intersection region1 region2

translation :: Float -> Float -> TransformationAST
translation tx ty = T $ Translation tx ty

scaling :: Float -> TransformationAST
scaling = T . Scaling

{-
    Smart constructor: dacă lista de transformări este singleton, înlocuiește
    lista cu unica transformare din listă; altfel, utilizează constructorul
    de date Combine.
-}
combineTransformations :: [TransformationAST] -> TransformationAST
combineTransformations [transformation] = transformation
combineTransformations transformations = T $ Combine transformations

{-
    Smart constructor: dacă se dorește aplicarea unei liste vide de transformări
    asupra unei regiuni, întoarce regiunea ca atare; altfel, utilizează
    constructorul de date Transform.
-}
applyTransformation :: TransformationAST -> RegionAST -> RegionAST
applyTransformation (T (Combine [])) region = region
applyTransformation transformation region = R $ Transform transformation region


{-
    * o translație cu parametrii tx și ty devine "+(tx,ty)"
    * o scalare cu factorul f devine "*<f>"
    * o transformare compusă este reprezentată ca lista Haskell
      a transformărilor constitutive.
-}
instance Show TransformationAST where
    show (T (Translation x y)) = "+(" ++ show x ++ "," ++ show y ++ ")"
    show (T (Scaling factor)) = "*<" ++ show factor ++ ">"
    show (T (Combine ts)) = "[" ++ intercalate "," (map show ts) ++ "]"


{-
    * fiecare nod din AST apare pe propriul rând
    * un nod copil este indentat cu două spații față de părintele său
    * un nod frunză FromPoints, Rectangle sau Circle este afișat ca în etapa 2
    * un nod Transform este reprezentat prin transformarea aferentă
    * un nod Complement este reprezentat prin caracterul '~'
    * un nod Union este reprezentat prin caracterul '+'
    * un nod Intersection este reprezentat prin caracterul '*'.
    ? asta e din enunt
-}

{-
  ? cum inteleg eu (- reprezinta tabul)
  * FromPoints [(x1, y1) (x2, y2) ...] -> -FromPoints [(x1, y1) (x2, y2) ...]\n
  * Rectangle width height             -> -Rectangle width height\n
  * Circle radius                      -> -Circle radius\n
  * Complement region                  -> -~\n ++ region
  * Union region1 region2              -> -+\n ++ region1 ++ region2
  * Intersection region1 region2       -> -*\n ++ region1 ++ region2
  * Transform transformation region    -> -transformation ++ \n ++ region
  ! tab = replicate (height * 2) ' '
  ? height pentru mine reprezinta cat de mult "cobor" in lista de elemente
-}


instance Show RegionAST where
    show (R reg) = init (printReg reg 0)


printReg :: RegionShape RegionAST -> Int -> String
printReg reg h = case reg of
  FromPoints points                -> lvlTab ++ "FromPoints " ++ show points ++ "\n"
  Rectangle wid hgt                -> lvlTab ++ "Rectangle " ++ show wid ++ " " ++ show hgt ++ "\n"
  Circle radius                    -> lvlTab ++ "Circle " ++ show radius ++ "\n"
  Complement (R reg)               -> lvlTab ++ "~\n" ++ printReg reg nextH
  Union (R reg1) (R reg2)          -> lvlTab ++ "+\n" ++ printReg reg1 nextH ++ printReg reg2 nextH
  Intersection (R reg1) (R reg2)   -> lvlTab ++ "*\n" ++ printReg reg1 nextH ++ printReg reg2 nextH
  Transform transformation (R reg) -> lvlTab ++ show transformation ++ "\n" ++ printReg reg nextH
  where
      lvlTab = replicate (h * 2) ' '
      nextH = h + 1


{-
    * interpretarea unui întreg n este regiunea care include doar punctul (n, n)
    * negația (minus unar) unei regiuni corespunde complementului
    * suma a două regiuni corespunde reuniunii
    * produsul a două regiuni corespunde intersecției.

    ! Constrângeri:

    * negate, (+) și (*) trebui definite point-free
    * (-) trebuie implementat exclusiv prin alți operatori aritmetici pe regiuni.
-}
instance Num RegionAST where
    fromInteger n = fromPoints [(fromInteger n, fromInteger n)]

    negate = complement

    (+) = union

    (*) = intersection

    -- * A \ B = A - A ∩ B
    region1 - region2 = region1 `intersection` negate region2


{-
    * fmap func Translation -> Translation
    * fmap func Scaling     -> Scaling
    * fmap func Combine     -> Combine fmap func
-}
instance Functor TransformationShape where
    fmap _ (Translation x y) = Translation x y
    fmap _ (Scaling factor) = Scaling factor
    fmap func (Combine ls) = Combine (fmap func ls)


{-
    * fmap func FromPoints   -> FromPoints
    * fmap func Rectangle    -> Rectangle
    * fmap func Circle       -> Circle
    * fmap func Complement   -> Complement func
    * fmap func Union        -> Union func
    * fmap func Intersection -> Intersection func
    * fmap func Transform    -> Transform func
-}
instance Functor RegionShape where
    fmap _ (FromPoints points) = FromPoints points
    fmap _ (Rectangle wid hgt) = Rectangle wid hgt
    fmap _ (Circle radius) = Circle radius
    fmap func (Complement reg) = Complement . func $ reg
    fmap func (Union reg1 reg2) = Union (func reg1) (func reg2)
    fmap func (Intersection reg1 reg2) = Intersection (func reg1) (func reg2)
    fmap func (Transform trans reg) = Transform trans (func reg)


{-
    Tipul (TransformationCombiner a) include funcții care pot combina câmpurile
    de tipul a din interiorul unei valori de tipul (TransformationShape a) la o
    singură valoare de tipul a.

    Tipul (RegionCombiner a) include funcții care pot combina câmpurile de tipul
    a din interiorul unei valori de tipul (RegionShape a) la o singură valoare
    de tipul a.

    În continuare, ne vom referi la aceste funcții prin „combiner-e”.
-}
type TransformationCombiner a = TransformationShape a -> a
type RegionCombiner a = RegionShape a -> a


{-
    Pentru definirea unei funcționale fold...AST, se urmează doi pași:

    1. Se reduc mai întâi subarborii folosind recursiv funcționala fold...AST,
       pentru a înlocui subarborii de tipul ...AST cu acumulatori de tipul a.
    2. Se aplică combiner-ul pe rezultat, pentru a combina acumulatorii interni
       de tipul a într-o singură valoare de tipul a.

    ! Constrângere: folosiți fmap.

    Exemple:

    labelCombiner :: TransformationCombiner String
    labelCombiner (Translation _ _) = "t"
    labelCombiner (Scaling _) = "s"
    labelCombiner (Combine labels) = concat labels

    > foldTransformationAST labelCombiner $
        combineTransformations [ translation 1 2
                               , scaling 3
                               , combineTransformations [ scaling 4
                                                        , translation 5 6
                                                        ]
                               ]
    "tsst"
-}
foldTransformationAST :: TransformationCombiner a -> TransformationAST -> a
foldTransformationAST f (T transformation) = f (fmap (foldTransformationAST f) transformation)


foldRegionAST :: RegionCombiner a -> RegionAST -> a
foldRegionAST f (R region) = f (fmap (foldRegionAST f) region)


{-
    * combiner Translation -> S.translation
    * combiner Scaling     -> S.scaling
    * combiner Combine     -> S.combineTransformations
-}
toTransformation :: TransformationAST -> Transformation
toTransformation = foldTransformationAST combiner
  where
    combiner :: TransformationCombiner Transformation
    combiner (Translation x y) = S.translation x y
    combiner (Scaling factor)  = S.scaling factor
    combiner (Combine ts)      = S.combineTransformations ts


{-
    * Translation -> 1
    * Scaling     -> 1
    * Combine     -> sum
-}
basicTransformationCount :: TransformationAST -> Int
basicTransformationCount = foldTransformationAST combiner
  where
    combiner :: TransformationCombiner Int
    combiner (Translation _ _) = 1
    combiner (Scaling _) = 1
    combiner (Combine ls) = sum ls


{-
    ! Constrângeri: evitați duplicarea codului.

    ? Cum ajută evaluarea leneșă dacă dorim să accesăm doar o componentă a perechii?

    * combiner FromPoints                                   -> (1, 0)
    * combiner Rectangle                                    -> (1, 0)
    * combiner Circle                                       -> (1, 0)
    * combiner Transformer (regs, trans)                    -> (regs, trans + 1)
    * combiner Complement (regs, trans)                     -> (regs, trans)
    * combiner Union (regs1, trans1) (regs2, trans2)        -> (regs1 + regs2, trans1 + trans2)
    * combiner Intersection (regs1, trans1) (regs2, trans2) -> (regs1 + regs2, trans1 + trans2)
    ? regs  - numarator de regiuni      (in functie pun reg)
    ? trans - numarator de transformari (in functie pun tran)
-}
basicEntityCount :: RegionAST -> (Int, Int)
basicEntityCount = foldRegionAST combiner
  where
    combiner :: RegionCombiner (Int, Int)
    combiner (Transform t (reg, tran)) = (reg, tran + basicTransformationCount t)
    combiner (Complement (reg, tran)) = (reg, tran)
    combiner (Union (reg1, tran1) (reg2, tran2)) = (reg1 + reg2, tran1 + tran2)
    combiner (Intersection (reg1, tran1) (reg2, tran2)) = (reg1 + reg2, tran1 + tran2)
    combiner _ = (1, 0)


showFoldFlag :: Bool
showFoldFlag = True
