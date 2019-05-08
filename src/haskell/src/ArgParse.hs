module ArgParse
    ( getFilename,
      getFileExtension,
      getFileContents,
    ) where

import System.Environment
import System.IO
import Data.List.Split
import Data.String.Utils

getFilename :: IO String
getFilename = parseArgs <$> getArgs

getFileExtension :: IO String
getFileExtension = filenameToExtension <$> getFilename

parseArgs :: [String] -> String
parseArgs []     = error "Not enough args"
parseArgs [arg1] = arg1
parseArgs _      = error "Too many args"

filenameToExtension :: String -> String
filenameToExtension = last . splitOn extSep 

filenameToName :: String -> String
filenameToName = join extSep . init . splitOn extSep

extSep = "."

getFileContents :: IO String
getFileContents = readFile <*> getFilename
{-getFileContents = do
  filename <- getFilename
  readFile filename-}
