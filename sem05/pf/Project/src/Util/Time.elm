module Util.Time exposing (..)

import Time


type Date
    = Date { year : Int, month : Time.Month, day : Int }


monthToString : Time.Month -> String
monthToString month =
    case month of
        Time.Jan ->
            "Jan"

        Time.Feb ->
            "Feb"

        Time.Mar ->
            "Mar"

        Time.Apr ->
            "Apr"

        Time.May ->
            "May"

        Time.Jun ->
            "Jun"

        Time.Jul ->
            "Jul"

        Time.Aug ->
            "Aug"

        Time.Sep ->
            "Sep"

        Time.Oct ->
            "Oct"

        Time.Nov ->
            "Nov"

        Time.Dec ->
            "Dec"


posixToDate : Time.Zone -> Time.Posix -> Date
posixToDate tz time =
    let
        year =
            Time.toYear tz time

        month =
            Time.toMonth tz time

        day =
            Time.toDay tz time
    in
    Date { year = year, month = month, day = day }


{-| Formats a `Date` instance.
-}
formatDate : Date -> String
formatDate (Date date) =
    let
        year =
            String.fromInt date.year

        month =
            monthToString date.month

        day =
            String.fromInt date.day |> String.padLeft 2 '0'
    in
    year ++ " " ++ month ++ " " ++ day


formatTime : Time.Zone -> Time.Posix -> String
formatTime tz time =
    let
        date =
            posixToDate tz time

        hour =
            Time.toHour tz time |> String.fromInt |> String.padLeft 2 '0'

        minute =
            Time.toMinute tz time |> String.fromInt |> String.padLeft 2 '0'
    in
    formatDate date ++ " " ++ hour ++ ":" ++ minute


type alias Duration =
    { seconds : Int
    , minutes : Int
    , hours : Int
    , days : Int
    }


{-| Calculates the amount of time that passed between two dates.
The first date (t1) must be **before** the second date (t2), if this not the case, the function should return `Nothing`.
-}
durationBetween : Time.Posix -> Time.Posix -> Maybe Duration
durationBetween t1 t2 =
    let
        millis1 =
            Time.posixToMillis t1

        millis2 =
            Time.posixToMillis t2

        diffMillis =
            millis2 - millis1
    in
    if diffMillis < 0 then
        Nothing

    else
        let
            seconds =
                diffMillis // 1000

            minutes =
                seconds // 60

            hours =
                minutes // 60

            days =
                hours // 24

            remainingSeconds =
                modBy 60 seconds

            remainingMinutes =
                modBy 60 minutes

            remainingHours =
                modBy 24 hours
        in
        Just { seconds = remainingSeconds, minutes = remainingMinutes, hours = remainingHours, days = days }


{-| Format a `Duration` as a human readable string
-}
formatDuration : Duration -> String
formatDuration duration =
    let
        formatUnit value singular =
            String.fromInt value
                ++ " "
                ++ singular
                ++ (if value == 1 then
                        ""

                    else
                        "s"
                   )

        units =
            [ ( duration.days, "day" )
            , ( duration.hours, "hour" )
            , ( duration.minutes, "minute" )
            , ( duration.seconds, "second" )
            ]
                |> List.filter (\( value, _ ) -> value > 0)

        formattedUnits =
            case units of
                [] ->
                    "0 seconds"

                [ ( value1, label1 ) ] ->
                    formatUnit value1 label1

                ( value1, label1 ) :: ( value2, label2 ) :: _ ->
                    formatUnit value1 label1 ++ " " ++ formatUnit value2 label2
    in
    formattedUnits
