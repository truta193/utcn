module Ex01Tests exposing (..)
import Expect exposing (equal)
import Test exposing (..)

import Ex01 exposing (..)

suite : Test
suite =
    describe "countVowels"
        [ test "counts vowels in a simple string" <|
            \_ ->
                equal 3 (countVowels "Hello World")
        
        , test "counts vowels in a phrase" <|
            \_ ->
                equal 7 (countVowels "Functional Programming")

        , test "counts vowels in a sentence" <|
            \_ ->
                equal 1 (countVowels "Bye")
        ]