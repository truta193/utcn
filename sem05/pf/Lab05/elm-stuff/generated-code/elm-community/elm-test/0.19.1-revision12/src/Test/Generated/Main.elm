module Test.Generated.Main exposing (main)

import ExerciseTests

import Test.Reporter.Reporter exposing (Report(..))
import Console.Text exposing (UseColor(..))
import Test.Runner.Node
import Test

main : Test.Runner.Node.TestProgram
main =
    Test.Runner.Node.run
        { runs = 100
        , report = ConsoleReport UseColor
        , seed = 62446625248032
        , processes = 12
        , globs =
            [ "tests/ExerciseTests.elm"
            ]
        , paths =
            [ "C:\\Users\\Andrei\\Documents\\2024-2025\\PF\\Lab05\\tests\\ExerciseTests.elm"
            ]
        }
        [ ( "ExerciseTests"
          , [ Test.Runner.Node.check ExerciseTests.suite
            ]
          )
        ]