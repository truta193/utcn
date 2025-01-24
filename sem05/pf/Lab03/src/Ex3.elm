module Ex3 exposing (..)

last: List number -> number
last list = 
    let
        helper acc lst =
            case lst of
                [] -> acc
                x::tail -> helper x tail
    in
        helper 0 list
    