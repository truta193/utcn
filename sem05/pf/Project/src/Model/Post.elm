module Model.Post exposing (..)

import Json.Decode as De
import Time


type alias Post =
    { by : String, id : Int, score : Int, title : String, url : Maybe String, time : Time.Posix, type_ : String }


{-| Decode a `Post`

See: <https://github.com/HackerNews/API#items>

The post is expected to have fields:

  - by: The username of the item's author.
  - id: The item's unique id.
  - score: The story's score.
  - title: The title of the story.
  - url: The URL of the story. **Optional**
  - time: Creation date of the item, in Unix Time.
  - type: The type of item.

_Note_: The `time` field contains the **seconds** since the unix epoch. Take this into consideration when using `Time.millisToPosix`.

-}
decode : De.Decoder Post
decode =
    De.map7 Post
        (De.field "by" De.string)
        (De.field "id" De.int)
        (De.field "score" De.int)
        (De.field "title" De.string)
        (De.field "url" (De.maybe De.string))
        (De.field "time" (De.map Time.millisToPosix (De.int |> De.map (\seconds -> seconds * 1000))))
        (De.field "type" De.string)
