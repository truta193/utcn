module Ex4 exposing (..)

indexList : number -> List a -> Maybe a
indexList i l =
    let
        helper w lst =
            case lst of
                [] -> Nothing
                x::tail -> if w > 0 then helper (w - 1) tail else Just x
    in
        helper i l