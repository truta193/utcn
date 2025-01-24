module Ex03 exposing (..)
import Ex01 exposing (..)
import Ex02 exposing (..)

luckyRoll (DicePair side1 side2) =
    case (side1, side2) of
        (Face6, Face6) -> "Very lucky"
        (Face6, _) -> "Lucky"
        (_, Face6) -> "Lucky"
        _ -> "Meh"

dice1 = Face1
dice2 = Face6
pair = DicePair dice1 dice2