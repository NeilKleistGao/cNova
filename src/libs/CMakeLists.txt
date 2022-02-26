

# 收集所有头文件源文件，存入 ALL_SOURCE 变量中
file(GLOB_RECURSE ALL_SOURCE_FILES
	"${PROJECT_SOURCE_DIR}/src/libs/*"
)

# 设置为静态库
add_library(${PROJECT_NAME} STATIC ${ALL_SOURCE_FILES})

#设置头文件目录
target_include_directories(${PROJECT_NAME} PUBLIC .) 