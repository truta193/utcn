module Ex02Tests exposing (..)
import Expect exposing (equal)
import Test exposing (..)
import Ex02 exposing (..)

testAccounts : List AccountConfiguration
testAccounts =
    [ { preferredTheme = "Light", subscribedToNewsletter = True, twoFactorAuthOn = False }
    , { preferredTheme = "Blue", subscribedToNewsletter = False, twoFactorAuthOn = True }
    ]

suite : Test
suite =
    describe "changePreferenceToDarkTheme"
        [ test "changes all accounts to Dark theme" <|
            \_ ->
                let
                    updatedAccounts = changePreferenceToDarkTheme testAccounts
                in
                equal "Dark" (List.head updatedAccounts |> Maybe.map .preferredTheme |> Maybe.withDefault "") 
        ]