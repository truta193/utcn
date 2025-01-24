module Ex6 exposing (..)

fibonacci n =
    let
        fibHelper a b count =
            if count == 0 then
                a
            else
                fibHelper b (a + b) (count - 1)
    in
    fibHelper 0 1 n

fibsWithIndex start end =
    let
        generateFib a b index =
            if a > (fibonacci end) then
                []
            else if index >= start then
                (index, a) :: generateFib b (a + b) (index + 1)
            else
                generateFib b (a + b) (index + 1)
    in
    generateFib 0 1 0