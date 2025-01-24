module View.Posts exposing (..)

import Html exposing (Html, a, div, input, label, option, select, table, tbody, td, text, th, thead, tr)
import Html.Attributes exposing (checked, class, for, href, id, selected, style, target, type_, value)
import Html.Events exposing (onCheck, onInput)
import Model exposing (Msg(..))
import Model.Post exposing (Post)
import Model.PostsConfig as PostsConfig exposing (Change(..), PostsConfig, SortBy(..), defaultConfig, filterPosts, sortFromString, sortToString)
import Time
import Util.Time


{-| Show posts as a HTML [table]
-}
postTable : PostsConfig -> Time.Posix -> List Post -> Html Msg
postTable config currentTime posts =
    let
        filteredPosts =
            filterPosts config posts

        postRow : Post -> Html Msg
        postRow post =
            let
                duration =
                    case Util.Time.durationBetween post.time currentTime of
                        Just dur ->
                            Util.Time.formatDuration dur

                        Nothing ->
                            "Invalid duration"
            in
            tr []
                [ td [ class "post-score", style "padding" "8px" ] [ text (String.fromInt post.score) ]
                , td [ class "post-title", style "padding" "8px" ] [ text post.title ]
                , td [ class "post-type", style "padding" "8px" ] [ text post.type_ ]
                , td [ class "post-time", style "padding" "8px" ]
                    [ text (Util.Time.formatTime Time.utc post.time)
                    , text (" (" ++ duration ++ " ago)")
                    ]
                , td [ class "post-url" ]
                    [ case post.url of
                        Just url ->
                            a [ href url, target "_blank" ] [ text "Link" ]

                        Nothing ->
                            text "No link"
                    ]
                ]

        headerRow =
            tr []
                [ th [] [ text "Score" ]
                , th [] [ text "Title" ]
                , th [] [ text "Type" ]
                , th [] [ text "Posted Date" ]
                , th [] [ text "Link" ]
                ]
    in
    table
        [ class "posts-table"
        , style "border-collapse" "collapse"
        , style "width" "100%"
        , style "margin-top" "20px"
        ]
        [ thead [] [ headerRow ]
        , tbody [] (List.map postRow filteredPosts)
        ]


{-| Show the configuration options for the posts table
-}
postsConfigView : PostsConfig -> Html Msg
postsConfigView config =
    let
        defaultSelectedSortBy =
            config.sortBy

        defaultPerPage =
            config.postsToShow

        handleSortChange : String -> Msg
        handleSortChange sortStr =
            case sortFromString sortStr of
                Just sortBy ->
                    ConfigChanged (PostsConfig.ChangeSortBy sortBy)

                Nothing ->
                    ConfigChanged (PostsConfig.ChangeSortBy defaultConfig.sortBy)

        handlePerPageChange : String -> Msg
        handlePerPageChange perPageStr =
            case String.toInt perPageStr of
                Just value ->
                    ConfigChanged (PostsConfig.ChangePostsToShow value)

                Nothing ->
                    ConfigChanged (PostsConfig.ChangePostsToShow defaultConfig.postsToShow)

        handleShowJobPosts : Bool -> Msg
        handleShowJobPosts _ =
            ConfigChanged PostsConfig.ToggleShowJobs

        handleShowTextPosts : Bool -> Msg
        handleShowTextPosts _ =
            ConfigChanged PostsConfig.ToggleShowTextOnly
    in
    div []
        [ label [ for "select-posts-per-page" ] [ text "Posts per page: " ]
        , select [ id "select-posts-per-page", onInput handlePerPageChange ]
            [ option [ value "10", selected (defaultPerPage == 10) ] [ text "10" ]
            , option [ value "25", selected (defaultPerPage == 25) ] [ text "25" ]
            , option [ value "50", selected (defaultPerPage == 50) ] [ text "50" ]
            ]
        , label [ for "select-sort-by" ] [ text "Sort by: " ]
        , select [ id "select-sort-by", onInput handleSortChange ]
            [ option [ value (sortToString None), selected (defaultSelectedSortBy == None) ] [ text (sortToString None) ]
            , option [ value (sortToString Score), selected (defaultSelectedSortBy == Score) ] [ text (sortToString Score) ]
            , option [ value (sortToString Title), selected (defaultSelectedSortBy == Title) ] [ text (sortToString Title) ]
            , option [ value (sortToString Posted), selected (defaultSelectedSortBy == Posted) ] [ text (sortToString Posted) ]
            ]
        , div []
            [ input [ id "checkbox-show-job-posts", type_ "checkbox", checked config.showJobs, onCheck handleShowJobPosts ] []
            , text "Show job posts"
            ]
        , div []
            [ input [ id "checkbox-show-text-only-posts", type_ "checkbox", checked config.showTextOnly, onCheck handleShowTextPosts ] []
            , text "Show text posts"
            ]
        ]
