module Ex04 exposing (..)
import Shapes exposing (..)

areaRec : ShapeRec -> Float
areaRec shape =
    case shape of
        CircleRec { radius } ->
            pi * radius * radius

        RectangleRec { width, height } ->
            width * height

        TriangleRec { sideA, sideB, sideC } ->
            heron sideA sideB sideC