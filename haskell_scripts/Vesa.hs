module Main (main) where

import qualified Paths_HCompile as CabalPaths
import System.FilePath          (takeDirectory, (</>))
import Numeric                  (showHex)
import Data.Char                (toUpper)
import HCompile

_getRootDir :: IO FilePath
_getRootDir = (takeDirectory . takeDirectory) <$> CabalPaths.getDataDir

_num2Hex :: Int -> String
_num2Hex num = "0x" ++ map toUpper (showHex num "")

main :: IO ()
main =
    _getRootDir >>= \rootDir ->
    runHCompile (do
        delFile

        fileName <- getFileName
        send2File (
            "#ifndef " ++ map cleanName fileName ++ "\n" ++
            "#define " ++ map cleanName fileName ++ "\n\n"
            )

        genConstRaw "#define " "VESA_ADDR "     (_num2Hex 0x7B00)
        genConst    "#define " "SCREEN_WIDHT "  (640       :: Int)
        genConst    "#define " "SCREEN_HEIGHT " (480       :: Int)
        genConst    "#define " "FULL_SCREEN "   (640 * 480 :: Int)
        send2File "\n"

        let colors = [
                        "BLACK",     "BLUE",          "GREEN",       "CYAN",
                        "RED",       "MAGENTA",       "BROWN",       "LIGHT_GREY",
                        "DARK_GREY", "LIGHT_BLUE",    "LIGHT_GREEN", "LIGHT_CYAN",
                        "LIGHT_RED", "LIGHT_MAGENTA", "YELLOW",      "WHITE"
                     ]
        genTypeRaw "typedef enum __attribute__((packed)) "
                   colors
                   (",\n\t", ", ")
                   ("{\n\t", "\n} VESA_16C;\n")
                   4

        send2File ("\n#endif // " ++ map cleanName fileName)

    ) HCompileConf {
        filePath     = rootDir </> "src" </> "generated" </> "vesa_consts.h",
        constWidth   = 20
    }