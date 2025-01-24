module Ex8 exposing (..)
import Shape exposing (..)

totalArea : List Shape -> Result (Int, InvalidShapeError) Float
totalArea shapes =
    let
        helper index acc remainingShapes =
            case remainingShapes of
                [] ->
                    Ok acc

                shape :: rest ->
                    case safeAreaEnum shape of
                        Ok area ->
                            helper (index + 1) (acc + area) rest

                        Err error ->
                            Err (index, error)
    in
    helper 0 0 shapes