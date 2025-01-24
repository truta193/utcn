module Model.PostIds exposing (..)

import Cursor exposing (Cursor)
import Json.Decode as De


type HackerNewsItem
    = Top
    | New
    | Show
    | Ask
    | Jobs


itemName : HackerNewsItem -> String
itemName item =
    case item of
        Top ->
            "top"

        New ->
            "new"

        Show ->
            "show"

        Ask ->
            "ask"

        Jobs ->
            "job"


type PostIds
    = PostIds (Cursor Int)


{-| Returns the first post id
-}
first : PostIds -> Int
first (PostIds ids) =
    Cursor.current ids


{-| Moves the `Cursor` forward and returns the current post id
-}
advance : PostIds -> Maybe ( Int, PostIds )
advance (PostIds cursor) =
    Cursor.forward cursor
        |> Maybe.map (\newCursor -> ( Cursor.current newCursor, PostIds newCursor ))


{-| Returns the first post id
-}
fromList : List Int -> Maybe PostIds
fromList ids =
    Cursor.fromList ids
        |> Maybe.map PostIds


{-| Decode a list of post ids.
-}
decode : De.Decoder (Maybe PostIds)
decode =
    De.list De.int
        |> De.map
            (\ids ->
                case ids of
                    [] ->
                        Nothing

                    head :: tail ->
                        Just (PostIds (Cursor.nonEmpty head tail))
            )
