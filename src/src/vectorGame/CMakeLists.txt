### SETUP LIBRARY ###
SET(LIB_NAME vectorGame)
SET(HEADER_PATH ${Vector_SOURCE_DIR}/include/${LIB_NAME})
SET(TARGET_H
    ${HEADER_PATH}/vectorgame.h
)
SET(TARGET_SRC
    vectorgame.c
)

### REGISTER ###
ADD_LIBRARY(${LIB_NAME} ${TARGET_SRC} ${TARGET_H})
