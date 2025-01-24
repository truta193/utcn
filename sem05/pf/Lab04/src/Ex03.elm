module Ex03 exposing (..)
import List exposing (..)
import String exposing (toList)

countVowels : String -> Int
countVowels s =
    length (filter (\x -> String.contains (String.fromChar x) "aeiouAEIOU") (toList s))
