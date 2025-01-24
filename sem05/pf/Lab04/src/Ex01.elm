module Ex01 exposing (..)
import List exposing (..)

enumerate : List a -> List (Int, a)
enumerate l = 
    let
        helper idx lst =
            case lst of
                [] -> []
                x::xs -> (idx, x) :: helper (idx + 1) xs
    in
        helper 0 l