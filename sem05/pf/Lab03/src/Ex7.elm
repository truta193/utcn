module Ex7 exposing (..)
import Shape exposing (..)

type Ordering
    = LT  -- less than
    | EQ  -- equal
    | GT  -- greater than

cmpShapes : Shape -> Shape -> Result String Ordering
cmpShapes shape1 shape2 =
    case (safeArea shape1, safeArea shape2) of
        (Ok area1, Ok area2) ->
            if area1 < area2 then
                Ok LT
            else if area1 > area2 then
                Ok GT
            else
                Ok EQ

        (Err errMsg, _) ->
            Err errMsg

        (_, Err errMsg) ->
            Err errMsg

s1 = Triangle 1 2 3
s2 = Triangle 5 6 7
s3 = Rectangle 3 4
s4 = Rectangle -4 5