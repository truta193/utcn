module Ex1 exposing (..)

safeDiv: Int -> Int -> Maybe Int
safeDiv a b = if b == 0 then Nothing else Just (a // b)

safeDiv2: Int -> Int -> Maybe Int
safeDiv2 a b = 
    case b of
        0 -> Nothing
        _ -> Just (a//b)