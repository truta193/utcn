module CoinFlip exposing (..)

import Browser
import Html exposing (..)
import Html.Attributes exposing (style)
import Html.Events exposing (..)
import Random


main =
    Browser.element
        { init = init
        , update = update
        , subscriptions = subscriptions
        , view = view
        }


type CoinSide
    = Heads
    | Tails


type alias Model =
    { currentFlip : CoinSide
    , flips : List CoinSide
    , headsCount : Int
    , tailsCount : Int
    }


type Msg
    = Flip Int
    | AddFlips (List CoinSide)


initModel : CoinSide -> Model
initModel initialFlip =
    { currentFlip = initialFlip
    , flips = [ initialFlip ]
    , headsCount = 0
    , tailsCount = 0
    }


init : () -> ( Model, Cmd Msg )
init _ =
    ( initModel Heads, Random.generate AddFlips (Random.list 1 coinFlip) )


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        Flip count ->
            ( model, Random.generate AddFlips (Random.list count coinFlip) )

        AddFlips coins ->
            let
                newFlips =
                    List.reverse coins ++ model.flips

                lastFlip =
                    List.head coins |> Maybe.withDefault model.currentFlip

                headsCount =
                    model.headsCount + List.length (List.filter (\c -> c == Heads) coins)

                tailsCount =
                    model.tailsCount + List.length (List.filter (\c -> c == Tails) coins)
            in
            ( { model | currentFlip = lastFlip, flips = newFlips, headsCount = headsCount, tailsCount = tailsCount }, Cmd.none )


coinFlip : Random.Generator CoinSide
coinFlip =
    Random.uniform Heads
        [ Tails ]


subscriptions : Model -> Sub Msg
subscriptions model =
    Sub.none


view : Model -> Html Msg
view model =
    let
        currentFlip =
            viewCoin model.currentFlip

        flips =
            model.flips
                |> List.map coinToString
                |> List.intersperse " "
                |> List.map text
    in
    div []
        [ button [ onClick (Flip 1) ] [ text "Flip" ]
        , button [ onClick (Flip 10) ] [ text "Flip 10" ]
        , button [ onClick (Flip 100) ] [ text "Flip 100" ]
        , div [] [ currentFlip ]
        , div [] [ text ("Heads: " ++ String.fromInt model.headsCount ++ " | Tails: " ++ String.fromInt model.tailsCount) ]
        , div [] flips
        ]


coinToString : CoinSide -> String
coinToString coin =
    case coin of
        Heads ->
            "h"

        Tails ->
            "t"


viewCoin : CoinSide -> Html Msg
viewCoin coin =
    let
        name =
            coinToString coin
    in
    div [ style "font-size" "4em" ] [ text name ]
