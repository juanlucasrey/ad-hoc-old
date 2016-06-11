include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB ad-hoc_SRC
    "*.cpp"
)

add_library(ad-hoc ${ad-hoc_SRC})
