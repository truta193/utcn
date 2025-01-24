module Model.PostsConfig exposing (Change(..), PostsConfig, SortBy(..), applyChanges, defaultConfig, filterPosts, sortFromString, sortOptions, sortToCompareFn, sortToString)

import Model.Post exposing (Post)
import Time


type SortBy
    = Score
    | Title
    | Posted
    | None


sortOptions : List SortBy
sortOptions =
    [ Score, Title, Posted, None ]


sortToString : SortBy -> String
sortToString sort =
    case sort of
        Score ->
            "Score"

        Title ->
            "Title"

        Posted ->
            "Posted"

        None ->
            "None"


sortFromString : String -> Maybe SortBy
sortFromString str =
    case str of
        "Score" ->
            Just Score

        "Title" ->
            Just Title

        "Posted" ->
            Just Posted

        "None" ->
            Just None

        _ ->
            Nothing


sortToCompareFn : SortBy -> (Post -> Post -> Order)
sortToCompareFn sort =
    case sort of
        Score ->
            \postA postB -> compare postB.score postA.score

        Title ->
            \postA postB -> compare postA.title postB.title

        Posted ->
            \postA postB -> compare (Time.posixToMillis postB.time) (Time.posixToMillis postA.time)

        None ->
            \_ _ -> EQ


type alias PostsConfig =
    { postsToFetch : Int
    , postsToShow : Int
    , sortBy : SortBy
    , showJobs : Bool
    , showTextOnly : Bool
    }


defaultConfig : PostsConfig
defaultConfig =
    PostsConfig 50 10 None False True


{-| A type that describes what option changed and how
-}
type Change
    = ChangePostsToShow Int
    | ChangeSortBy SortBy
    | ToggleShowJobs
    | ToggleShowTextOnly


{-| Given a change and the current configuration, return a new configuration with the changes applied
-}
applyChanges : Change -> PostsConfig -> PostsConfig
applyChanges change config =
    case change of
        ChangePostsToShow newPostsToShow ->
            { config | postsToShow = newPostsToShow }

        ChangeSortBy newSortBy ->
            { config | sortBy = newSortBy }

        ToggleShowJobs ->
            { config | showJobs = not config.showJobs }

        ToggleShowTextOnly ->
            { config | showTextOnly = not config.showTextOnly }


{-| Given the configuration and a list of posts, return the relevant subset of posts according to the configuration
-}
filterPosts : PostsConfig -> List Post -> List Post
filterPosts config posts =
    let
        filterByTextOnly lst =
            if config.showTextOnly then
                lst

            else
                List.filter (\post -> post.url /= Nothing) lst

        filterByJobs lst =
            if config.showJobs then
                lst

            else
                List.filter (\post -> post.type_ /= "job") lst

        sortPosts lst =
            if config.sortBy == None then
                lst

            else
                List.sortWith (sortToCompareFn config.sortBy) lst

        limitPosts lst =
            List.take config.postsToShow lst
    in
    posts
        |> sortPosts
        |> filterByTextOnly
        |> filterByJobs
        |> limitPosts
