# version
cmake_minimum_required(VERSION 3.10)

# project
project (pktreorg)

# add src
aux_source_directory(. DIR_SRCS)

# generate
add_executable(pktreorg ${DIR_SRCS})

# library
target_link_libraries(pktreorg pthread)
