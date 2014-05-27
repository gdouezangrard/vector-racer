cmake_minimum_required(VERSION 2.6)
project(s6-vector-543)

set(VECTOR_MINOR_VERSION 2)
set(VECTOR_MAJOR_VERSION 0)
OPTION(VECTOR_MAINTAINER "Enable Vector maintainer build methods, such as making svn branches, tags." OFF)
IF (VECTOR_MAINTAINER)
    SET(VECTOR_SVN "trunk")
    SET(VECTOR_BRANCH Vector-${VECTOR_MAJOR_VERSION}.${VECTOR_MINOR_VERSION})

    #
    # Provide target for tagging a release
    #
    SET(SVNCOMMAND svn)
    SET(SVNTRUNKDIR     https://thor.enseirb-matmeca.fr/svn/s6-vector-543/trunk)
    SET(SVNTAGDIR       https://thor.enseirb-matmeca.fr/svn/s6-vector-543/tags)
    SET(SVNBRANCHDIR    https://thor.enseirb-matmeca.fr/svn/s6-vector-543/branches)

    IF   (VECTOR_SVN STREQUAL "trunk")
        SET(SVNSOURCEDIR ${SVNTRUNKDIR})
    ELSE()
        SET(SVNSOURCEDIR ${SVNBRANCHDIR}/${VECTOR_BRANCH})
    ENDIF()

    SET(RELEASE_NAME Vector-${VECTOR_MAJOR_VERSION}.${VECTOR_MINOR_VERSION})

    ADD_CUSTOM_TARGET(tag-test
        COMMAND echo ${SVNCOMMAND} copy ${SVNSOURCEDIR} ${SVNTAGDIR}/${RELEASE_NAME} -m "Release ${RELEASE_NAME}"
    )

    ADD_CUSTOM_TARGET(tag-run
        COMMAND ${SVNCOMMAND} copy ${SVNSOURCEDIR} ${SVNTAGDIR}/${RELEASE_NAME} -m "Release ${RELEASE_NAME}"
    )

    ADD_CUSTOM_TARGET(branch-test
        COMMAND echo ${SVNCOMMAND} copy ${SVNSOURCEDIR} ${SVNBRANCHDIR}/${VECTOR_BRANCH} -m "Branch ${VECTOR_BRANCH}"
    )

    ADD_CUSTOM_TARGET(branch-run
        COMMAND ${SVNCOMMAND} copy ${SVNSOURCEDIR} ${SVNBRANCHDIR}/${VECTOR_BRANCH} -m "Branch ${VECTOR_BRANCH}"
    )
ENDIF(VECTOR_MAINTAINER)

add_subdirectory(trunk)
set(CMAKE_C_FLAGS "-std=c99 -g -Wall")
set(CMAKE_C_COMPILER gcc ${CMAKE_C_FLAGS})
