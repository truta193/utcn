module Ex02 exposing (..)

type alias ThemeConfig = String
type alias AccountConfiguration =
    { preferredTheme : ThemeConfig
    , subscribedToNewsletter : Bool
    , twoFactorAuthOn : Bool
    }

changePreferenceToDarkTheme : List AccountConfiguration -> List AccountConfiguration
changePreferenceToDarkTheme accounts =
    accounts |> List.map (\account -> { account | preferredTheme = "Dark" })
    