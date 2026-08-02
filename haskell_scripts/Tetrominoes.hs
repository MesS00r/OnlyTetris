module Main (main) where

import qualified Paths_HCompile as CabalPaths
import System.FilePath          (takeDirectory, (</>))
import Data.Bits                (shiftL, (.|.))
import Data.Word                (Word8, Word16)
import Numeric                  (showHex)
import Data.Char                (toUpper)
import HCompile

_getRootDir :: IO FilePath
_getRootDir = (takeDirectory . takeDirectory) <$> CabalPaths.getDataDir

_bits2Bytes :: [Word8] -> Word16
_bits2Bytes = foldl' (\acc byte -> (acc `shiftL` 1) .|. fromIntegral byte) 0

_myChunksOf :: Int -> [a] -> [[a]]
_myChunksOf _ [] = []
_myChunksOf n xs = take n xs : _myChunksOf n (drop n xs)

_myShowHex :: Word16 -> String
_myShowHex n = "0x" ++ pad (map toUpper (showHex n ""))
    where
        pad s = replicate (4 - length s) '0' ++ s

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
        genTypeRaw "static const uint16_t tetrominoes[] = "
                   (map (_myShowHex . _bits2Bytes . reverse) (_myChunksOf 16 imageBits))
                   (",\n\t", ", ")
                   ("{\n\t", "\n};\n")
                   3

        send2File ("\n#endif // TETROMINOES_H")

    ) HCompileConf {
        filePath     = rootDir </> "src" </> "generated" </> "tetrominoes.h",
        constWidth   = 20
    }