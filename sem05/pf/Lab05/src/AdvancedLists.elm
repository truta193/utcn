module AdvancedLists exposing (..)

import Lists exposing (foldl, map, filter)


sumOfOddLastDigits : List Int -> Int
sumOfOddLastDigits l =
  foldl (+) 0 (map (modBy 10) (filter (\x -> modBy 2 x == 1) l))



sumOfOddLastDigitsPipe : List Int -> Int
sumOfOddLastDigitsPipe l =
  l 
    |> filter (\x -> modBy 2 x == 1)
    |> map (modBy 10)
    |> foldl (+) 0

