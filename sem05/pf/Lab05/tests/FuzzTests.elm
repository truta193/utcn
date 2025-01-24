module FuzzTests exposing (..)

import Test exposing (..)
import Fuzz exposing (..)

-- Assuming partition is defined elsewhere
partition : comparable -> List comparable -> (List comparable, List comparable)
partition pivot list =
    -- Placeholder implementation
    (List.filter (\x -> x < pivot) list, List.filter (\x -> x >= pivot) list)

-- 1. Test that the total number of elements in the output lists equals the input list.
testNumberOfElements : Fuzz (comparable, List comparable) -> Test
testNumberOfElements =
    fuzz (comparable, list comparable) <|
        \pivot inputList ->
            let
                (lessThanPivot, greaterOrEqualPivot) = partition pivot inputList
            in
            List.length lessThanPivot + List.length greaterOrEqualPivot == List.length inputList


-- 2. Test that all elements in the output lists are from the input list.
testElementsInOutput : Fuzz (comparable, List comparable) -> Test
testElementsInOutput =
    fuzz (comparable, list comparable) <|
        \pivot inputList ->
            let
                (lessThanPivot, greaterOrEqualPivot) = partition pivot inputList
                allOutputs = lessThanPivot ++ greaterOrEqualPivot
            in
            List.all (\x -> List.member x inputList) allOutputs


-- 3. Test that the elements in the first output list are less than the pivot
--    and the elements in the second output list are greater than or equal to the pivot.
testElementsOrder : Fuzz (comparable, List comparable) -> Test
testElementsOrder =
    fuzz (comparable, list comparable) <|
        \pivot inputList ->
            let
                (lessThanPivot, greaterOrEqualPivot) = partition pivot inputList
            in
            List.all (\x -> x < pivot) lessThanPivot &&
            List.all (\x -> x >= pivot) greaterOrEqualPivot


-- The main test suite
tests : Test
tests =
    describe "Partition Tests"
        [ test "Number of elements test" <| testNumberOfElements,
          test "Elements in output test" <| testElementsInOutput,
          test "Elements order test" <| testElementsOrder
        ]
