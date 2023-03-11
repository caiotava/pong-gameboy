SET(GENERATED_PATH  ${PROJECT_SOURCE_DIR}/src/generated)

execute_process(
        COMMAND png2asset ${PROJECT_SOURCE_DIR}/assets/ball.png -c ${GENERATED_PATH}/ball.c -sw 16 -sh 8 -spr8x8 -noflip
        COMMAND png2asset ${PROJECT_SOURCE_DIR}/assets/paddle.png -c ${GENERATED_PATH}/paddle.c -sw 8 -sh 8 -spr8x8 -noflip

        ## Background images
        COMMAND png2asset ${PROJECT_SOURCE_DIR}/assets/logo.png -c ${GENERATED_PATH}/logo.c -map -noflip
        COMMAND png2asset ${PROJECT_SOURCE_DIR}/assets/game-over.png -c ${GENERATED_PATH}/game-over.c -map -noflip
        COMMAND png2asset ${PROJECT_SOURCE_DIR}/assets/font.png -c ${GENERATED_PATH}/font.c -map -noflip
        COMMAND png2asset ${PROJECT_SOURCE_DIR}/assets/scores-font.png -c ${GENERATED_PATH}/scores-font.c -map -spr8x16 -noflip
        COMMAND png2asset ${PROJECT_SOURCE_DIR}/assets/scores-background.png -c ${GENERATED_PATH}/scores-background.c -map -spr8x16 -noflip
        COMMAND png2asset ${PROJECT_SOURCE_DIR}/assets/background.png -c ${GENERATED_PATH}/background.c -map -spr8x16 -noflip
)

SET(GENERATED_INCLUDE ${GENERATED_PATH})
FILE(GLOB GENERATE_SRC ${GENERATED_PATH}/*.c)