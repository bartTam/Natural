module Main where

import Lib
import ArgParse
import Parser

main :: IO ()
main = do
  contents <- getFileContents
  putStrLn contents
