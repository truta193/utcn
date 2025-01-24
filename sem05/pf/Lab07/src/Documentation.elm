module Documentation exposing (..)

{-| Returns all the ends (tails) of a list

    tails [ 1, 2, 3 ] --> [[1, 2, 3], [2, 3], [3], []]

-}


tails : List a -> List (List a)
tails l =
    case l of
        [] ->
            [ [] ]

        x :: xs ->
            (x :: xs) :: tails xs


{-| Returns all combinations for given list of elements.
Combinations are **not** returned in lexicographic order.

```
    combinations [1, 2] --> [[1, 2], [1], [2], []]
    combinations [1, 2, 3] --> [[1,2,3],[1,2],[1,3],[1],[2,3],[2],[3],[]]
```

-}
combinations : List a -> List (List a)
combinations l =
    case l of
        [] ->
            [ [] ]

        x :: xs ->
            let
                withoutX =
                    combinations xs

                withX =
                    List.map (\combo -> x :: combo) withoutX
            in
            withX ++ withoutX
