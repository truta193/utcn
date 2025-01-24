module Ex03 exposing (..)

type alias UserDetails =
    { firstName : String
    , lastName : String
    , phoneNumber : Maybe String
    }

type alias User =
    { id : String
    , email : String
    , details : UserDetails
    }

usersWithPhoneNumbers : List User -> List String
usersWithPhoneNumbers users =
    users
        |> List.filter (\user -> case user.details.phoneNumber of
                                   Just _ -> True
                                   Nothing -> False)
        |> List.map .email