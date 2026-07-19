{-# LANGUAGE LambdaCase #-}

module Main (main) where

import qualified Paths_HCompile as CabalPaths
import System.FilePath          (takeDirectory, (</>))
import Control.Monad            (forM_)
import Data.Char                (toUpper)
import HCompile

_getRootDir :: IO FilePath
_getRootDir = (takeDirectory . takeDirectory) <$> CabalPaths.getDataDir

_myChunksOf :: Int -> [a] -> [[a]]
_myChunksOf _ [] = []
_myChunksOf n xs = take n xs : _myChunksOf n (drop n xs)

main :: IO ()
main =
    _getRootDir >>= \rootDir ->
    runHCompile (do
        delFile

        fileName <- getFileName
        send2File (
            "#ifndef " ++ map cleanName fileName ++ "\n"   ++
            "#define " ++ map cleanName fileName ++ "\n\n" ++
            
            "#include <stdint.h>\n"                        ++
            "#include <generated/vesa_consts.h>\n\n"
            )

        let imagePath  = rootDir </> "textures" </> "tetris_textures4x4.bmp"

        imageWidth   <- getBmpWidth     imagePath
        imageHeight  <- getBmpHeight    imagePath
        imagePixels  <- getBmpPixelsNum imagePath

        genConst "#define " "IMAGE_WIDHT "  imageWidth
        genConst "#define " "IMAGE_HEIGHT " imageHeight
        genConst "#define " "IMAGE_PIXELS " imagePixels
        send2File "\n"

        image <- getBmpImage imagePath
        let tileDims = 4

        genConst "#define " "TILE_DIMENSIONS " tileDims
        genConst "#define " "TILE_PIXELS "     (tileDims ^ 2)
        genConst "#define " "TILES_NUM "       (length image `div` tileDims ^ 2)
        send2File "\n"

        let tiles      = take 4 (_myChunksOf (tileDims ^ 2) image)
        let nums       = drop 4 (_myChunksOf (tileDims ^ 2) image)
        let myNames    = ["brick", "green", "blue", "yellow", "nums"]
        let numNames   = map (\f -> "num" ++ show f) [0 :: Int .. 9]
        let myPalettes = [
                         ["BLACK", "RED"   ],
                         ["BLACK", "GREEN" ],
                         ["BLACK", "BLUE"  ],
                         ["BLACK", "YELLOW"],
                         ["BLACK", "WHITE" ]
                         ]

        send2File ("// * -------------------------------------------------------------------------------\n" ++
                  "// * TILE PALETTES\n"                                                           ++
                  "// * -------------------------------------------------------------------------------\n\n"
                  )

        forM_ (zip3 [0 :: Int ..] myNames myPalettes) $ \(x, name, palette) ->
            genTypeRaw (padName 25 ("enum TILE_" ++ map toUpper name ++ "_PALETTE "))
                       (map (\(i, f) -> padName 17 ("COLOR" ++ show x ++ "_" ++ show i ++ " = " ++ f))
                       (zip [0 :: Int ..] palette))
                       (", ", ", ")
                       ("{ ", " };\n")
                       1
        send2File "\n"

        send2File ("// * -------------------------------------------------------------------------------\n" ++
                  "// * RGBY TILES\n"                                                           ++
                  "// * -------------------------------------------------------------------------------\n\n"
                  )

        forM_ (zip3 [0 :: Int ..] (init myNames) tiles) $ \(x, name, tile) ->
            genTypeRaw ("static const uint8_t tile_" ++ name ++ "[] = ")
                       (map (\f -> "COLOR" ++ show x ++ "_" ++ show f) tile)
                       (",\n\t", ", ")
                       ("{\n\t", "\n};\n\n")
                       4

        send2File ("// * -------------------------------------------------------------------------------\n" ++
                  "// * NUM TILES\n"                                                           ++
                  "// * -------------------------------------------------------------------------------\n\n"
                  )

        forM_ (zip3 (repeat 4) numNames nums) $ \(x, name, num) ->
            genTypeRaw ("static const uint8_t tile_" ++ name ++ "[] = ")
                       (map (\f -> "COLOR" ++ show x ++ "_" ++ show f) num)
                       (",\n\t", ", ")
                       ("{\n\t", "\n};\n\n")
                       4

        send2File ("\n#endif // " ++ map cleanName fileName)

    ) HCompileConf {
        filePath     = rootDir </> "src" </> "generated" </> "textures.h",
        constWidth   = 20
    }