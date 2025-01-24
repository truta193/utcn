module Ex01 exposing (..)

countVowels : String -> Int
countVowels s = s
    |> String.toList
    |> List.filter (\c -> List.member (Char.toLower c) ['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'])
    |> List.length



