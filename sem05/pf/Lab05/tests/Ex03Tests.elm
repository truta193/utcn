module Ex03Tests exposing (..)

import Test exposing (..)
import Ex03 exposing (..)

tests : Test
tests =
    describe "User Tests"
        [ test "Users with phone numbers" <|
            \_ ->
                let
                    user1 = { id = "1", email = "user1@example.com", details = { firstName = "John", lastName = "Doe", phoneNumber = Just "123-456-7890" } }
                    user2 = { id = "2", email = "user2@example.com", details = { firstName = "Jane", lastName = "Smith", phoneNumber = Nothing } }
                    user3 = { id = "3", email = "user3@example.com", details = { firstName = "Alice", lastName = "Johnson", phoneNumber = Just "987-654-3210" } }
                    users = [ user1, user2, user3 ]
                    expected = [ "user1@example.com", "user3@example.com" ]
                    result =
                        users
                            |> usersWithPhoneNumbers
                in
                result == expected
        ]