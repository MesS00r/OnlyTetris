-- {-# LANGUAGE LambdaCase #-}

module Main (main) where

import qualified Paths_HCompile as CabalPaths
import System.FilePath          (takeDirectory, (</>))
import Data.Bits                (shiftL, (.|.))
import Data.Word                (Word8, Word16)
import Numeric                  (showHex)
import Data.Char                (toUpper)
import Data.List                (transpose)
import Control.Monad            (forM_)
import HCompile

_getRootDir :: IO FilePath
_getRootDir = (takeDirectory . takeDirectory) <$> CabalPaths.getDataDir

_bits2Bytes :: [Word8] -> Word16
_bits2Bytes = foldl' (\acc byte -> (acc `shiftL` 1) .|. fromIntegral byte) 0

_myChunksOf :: Int -> [a] -> [[a]]
_myChunksOf _ [] = []
_myChunksOf n xs = take n xs : _myChunksOf n (drop n xs)

_myShowHex :: Integral a => a -> String
_myShowHex n = "0x" ++ pad (map toUpper (showHex n ""))
    where
        pad s = replicate (4 - length s) '0' ++ s

_rotateTetromino :: Int -> [a] -> [a]
_rotateTetromino angle tetr = concat $
    case angle of
        1 -> map reverse (transpose matrix)
        2 -> map reverse (reverse   matrix)
        3 -> reverse     (transpose matrix)
        _ -> matrix
    where
        matrix = _myChunksOf 4 tetr

_rotateTetromino2 :: [a] -> [[a]]
_rotateTetromino2 tetr = [_rotateTetromino i tetr | i <- [0..3]]

_bmp2Tetrominoes :: [Word8] -> [[Word16]]
_bmp2Tetrominoes img = map ((map _bits2Bytes . myReverse) . _rotateTetromino2) (_myChunksOf 16 img)
    where
        myReverse = concat . reverse . _myChunksOf 2

_gen2DTable4C :: Integral a => [[a]] -> HCompile ()
_gen2DTable4C fields
    | null fields = return ()
    | otherwise   = do
        forM_ (init fields) $ \field ->
            genTypeRaw ""
                       (map _myShowHex field)
                       (", ", ", ")
                       ("{ ", " },\n\t")
                       4

        genTypeRaw ""
                   (map _myShowHex (last fields))
                   (", ", ", ")
                   ("{ ", " }")
                   4

main :: IO ()
main =
    _getRootDir >>= \rootDir ->
    runHCompile (do
        delFile

        fileName <- getFileName
        send2File (
            "#ifndef TETROMINOES_H\n"   ++
            "#define TETROMINOES_H\n\n" ++
            
            "#include <stdint.h>\n\n"
            )

        imageBits <- getBmpImage $ rootDir </> "haskell_scripts" </> "tetrominoes.bmp"
        let
            tetrNum = show 7
            turnNum = show 4

            fields   = _bmp2Tetrominoes imageBits

        genConstRaw "#define " "TETROMINO_NUM " tetrNum
        genConstRaw "#define " "TURN_NUM "      turnNum
        send2File "\n"

        send2File ("static const uint16_t tetrominoes[" ++
                  tetrNum ++ "]["                      ++
                  turnNum ++ "] = {\n\t"
                  )

        _gen2DTable4C fields

        send2File "\n};\n"

        send2File ("\n#endif // TETROMINOES_H")

    ) HCompileConf {
        filePath     = rootDir </> "src" </> "generated" </> "tetrominoes.h",
        constWidth   = 20
    }