module Ex05 exposing (..)
import List exposing (..)

countriesWithCapital : List (String, String) -> (String -> Bool) -> List String
countriesWithCapital countries pred = 
    map (\(a,b) -> a) (filter (\(x,y) -> pred y) countries)