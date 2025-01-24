module Test.Generated.Main exposing (main)

import VerifyExamples.Documentation.Combinations0
import VerifyExamples.Documentation.Combinations1
import VerifyExamples.Documentation.Tails0

import Test.Reporter.Reporter exposing (Report(..))
import Console.Text exposing (UseColor(..))
import Test.Runner.Node
import Test

main : Test.Runner.Node.TestProgram
main =
    Test.Runner.Node.run
        { runs = 100
        , report = ConsoleReport UseColor
        , seed = 168902233986910
        , processes = 12
        , globs =
            []
        , paths =
            [ "C:\\Users\\Andrei\\Documents\\2024-2025\\PF\\Lab07\\tests\\VerifyExamples\\Documentation\\Combinations0.elm"
            , "C:\\Users\\Andrei\\Documents\\2024-2025\\PF\\Lab07\\tests\\VerifyExamples\\Documentation\\Combinations1.elm"
            , "C:\\Users\\Andrei\\Documents\\2024-2025\\PF\\Lab07\\tests\\VerifyExamples\\Documentation\\Tails0.elm"
            ]
        }
        [ ( "VerifyExamples.Documentation.Combinations0"
          , [ Test.Runner.Node.check VerifyExamples.Documentation.Combinations0.spec0
            ]
          )
        , ( "VerifyExamples.Documentation.Combinations1"
          , [ Test.Runner.Node.check VerifyExamples.Documentation.Combinations1.spec1
            ]
          )
        , ( "VerifyExamples.Documentation.Tails0"
          , [ Test.Runner.Node.check VerifyExamples.Documentation.Tails0.spec0
            ]
          )
        ]