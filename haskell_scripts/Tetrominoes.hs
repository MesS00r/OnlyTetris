-- {-# LANGUAGE LambdaCase #-}
{-# LANGUAGE ParallelListComp #-}

module Main (main) where

import qualified Paths_HCompile as CabalPaths
import System.FilePath          (takeDirectory, (</>))
import Data.Bits                (shiftL, (.|.), Bits (testBit))
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

_myShowHex :: Integral a => Int -> a -> String
_myShowHex sn n = "0x" ++ pad (map toUpper (showHex n ""))
    where
        pad s = replicate (sn - length s) '0' ++ s

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
_rotateTetromino2 tetrs = [_rotateTetromino i tetrs | i <- [0..3]]

_bmp2Tetrominoes :: [Word8] -> [[Word16]]
_bmp2Tetrominoes img = map ((map _bits2Bytes . myReverse) . _rotateTetromino2) (_myChunksOf 16 img)
    where
        myReverse = concat . reverse . _myChunksOf 2

_gen2DTable4C :: Integral a => Int -> [[a]] -> HCompile ()
_gen2DTable4C spaces fields
    | null fields = return ()
    | otherwise   = do
        forM_ (init fields) $ \field ->
            genTypeRaw ""
                       (map (_myShowHex spaces) field)
                       (", ", ", ")
                       ("{ ", " },\n\t")
                       4

        genTypeRaw ""
                   (map (_myShowHex spaces) (last fields))
                   (", ", ", ")
                   ("{ ", " }")
                   4

_getTetrominoSize :: Word16 -> (Int, Int)
_getTetrominoSize 0    = (0, 0)
_getTetrominoSize tetr = (width, height)
    where
        coords = [ (i `mod` 4, i `div` 4)
                 | i <- [0..15]
                 , testBit tetr i
                 ]

        xs     = map fst coords
        ys     = map snd coords

        width  = maximum xs - minimum xs + 1
        height = maximum ys - minimum ys + 1

_combineBytes :: Int -> Int -> Int
_combineBytes high low = (high `shiftL` 4) .|. low

_genTetrominoHitboxes :: [Word16] -> [Int]
_genTetrominoHitboxes tetrs
    | null tetrs = []
    | otherwise  = sizeLists
    where
        tetrominoSizes = map _getTetrominoSize tetrs
        sizeLists      = map (\(w, h) -> _combineBytes w h) tetrominoSizes

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
                  tetrNum ++ "]["                       ++
                  turnNum ++ "] = {\n\t"
                  )

        _gen2DTable4C 4 fields

        send2File "\n};\n\n"

        send2File ("static const uint8_t tetromino_hitboxes[" ++
                  tetrNum ++ "]["                             ++
                  turnNum ++ "] = {\n\t"
                  )

        _gen2DTable4C 2 $ map _genTetrominoHitboxes fields

        send2File "\n};\n"

        send2File ("\n#endif // TETROMINOES_H")

    ) HCompileConf {
        filePath     = rootDir </> "src" </> "generated" </> "tetrominoes.h",
        constWidth   = 20
    }