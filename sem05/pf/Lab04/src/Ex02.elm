module Ex02 exposing (..)

repeat : Int -> a -> List a
repeat n elem = 
    if n <= 0 then
        []
    else
        elem :: repeat (n - 1) elem
    
    