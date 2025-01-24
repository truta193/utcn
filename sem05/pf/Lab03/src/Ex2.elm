module Ex2 exposing (..)

len : List a -> Int
len list =
    case list of
        [] ->
            0

        _ :: tail ->
            1 + len tail

lenTail : List a -> number
lenTail list =
    let
        helper acc lst =
            case lst of
                [] -> acc
                _::tail -> helper (acc + 1) tail
    in
    helper 0 list