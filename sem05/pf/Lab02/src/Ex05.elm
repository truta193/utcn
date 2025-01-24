module Ex05 exposing (..)

type alias Point = { x: Float, y: Float }
type Shape2D
    = Circle { center: Point, radius: Float }
    | Rectangle { topLeftCorner: Point, bottomRightCorner: Point }
    | Triangle { pointA: Point, pointB: Point, pointC: Point }

distance : Point -> Point -> Float
distance p1 p2 =
    let
        dx = p2.x - p1.x
        dy = p2.y - p1.y
    in
    sqrt (dx * dx + dy * dy)

heron a b c =
    let
        s = (a + b + c) / 2
    in
    sqrt (s * (s - a) * (s - b) * (s - c))

pointInShape : Point -> Shape2D -> Bool
pointInShape point shape =
    case shape of
        Circle { center, radius } ->
            distance point center <= radius

        Rectangle { topLeftCorner, bottomRightCorner } ->
            let
                withinX = point.x >= topLeftCorner.x && point.x <= bottomRightCorner.x
                withinY = point.y >= topLeftCorner.y && point.y <= bottomRightCorner.y
            in
            withinX && withinY

        Triangle { pointA, pointB, pointC } ->
            let
                s1 = pointC.y - pointA.y
                s2 = pointC.x - pointA.x
                s3 = pointB.y - pointA.y
                s4 = point.y - pointA.y

                w1 = (pointA.x * s1 + s4 * s2 - point.x * s1) / (s3 * s2 - (pointB.x - pointA.x) * s1)
                w2 = (s4 - w1 * s3) / s1
            in
            w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1