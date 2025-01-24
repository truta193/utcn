module Ex5 exposing (..)

fibonacci n =
    let
        fibHelper a b count =
            if count == 0 then
                a
            else
                fibHelper b (a + b) (count - 1)
    in
    fibHelper 0 1 n

fibs start end =
    let
        generateFib a b =
            if a > (fibonacci end) then
                []
            else if a >= (fibonacci start) then
                a :: generateFib b (a + b)
            else
                generateFib b (a + b)
    in
    generateFib 0 1