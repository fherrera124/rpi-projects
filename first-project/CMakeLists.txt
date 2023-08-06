cmake_minimum_required(VERSION 3.22.1)

project(RPICrossCompilingProject VERSION 1.0.0)

# Source directories
set(executables)

# ############## functions #################
function(add_executable_custom source_file)
    set(source_file "${CMAKE_SOURCE_DIR}/src/${source_file}")
    get_filename_component(file_name "${source_file}" NAME_WE)
    add_executable(${file_name} ${source_file})
    list(APPEND executables ${file_name})
    set(executables ${executables} PARENT_SCOPE)
endfunction()

# Create the executables
add_executable_custom(hello_word.c)
add_executable_custom(network_info.c)
add_executable_custom(tcp_server.c)

# Custom target for Only Building
add_custom_target(build ALL)

set(target $ENV{SSH_TARGET})
set(path $ENV{DEST_PATH})
set(port $ENV{GDBSERVER_PORT})

if(DEFINED ENV{SOURCE_FILE})
    set(SOURCE_FILE $ENV{SOURCE_FILE})

    add_custom_target(debug DEPENDS ${SOURCE_FILE})
    add_custom_command(TARGET debug POST_BUILD
        COMMAND scp ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE} ${target}:${path}
        COMMAND ssh -L 1234:localhost:${port} ${target} 'nohup sh -c "chmod +x ${SOURCE_FILE} && gdbserver :${port} ${SOURCE_FILE} 2>&1 &" '
    )

    add_custom_target(copy DEPENDS ${SOURCE_FILE})
    add_custom_command(TARGET copy POST_BUILD
        COMMAND scp ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE} ${target}:${path}
        COMMAND ssh ${target} 'chmod +x ${SOURCE_FILE}')
else()
    add_custom_target(copy_all DEPENDS ${executables})
    add_custom_command(TARGET copy_all
        POST_BUILD
        COMMAND scp ${executables} ${target}:${path}
    )
endif()

# En linux usaria COMMAND /usr/bin/rsync -avh  .En windows con SCP
install(CODE "execute_process(COMMAND scp -r ${CMAKE_BINARY_DIR} ${target}:${path}/binaries)")
