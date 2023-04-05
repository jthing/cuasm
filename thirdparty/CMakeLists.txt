cmake_minimum_required(VERSION 3.22)

project(cuasm-compiler C)
set(CMAKE_C_STANDARD 11)

include_directories(include/unp)
set(CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_library(unp STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/connect_nonb.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/error.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/if_indextoname.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/mcast_get_ttl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/my_addrs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/rtt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/sock_cmp_addr.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/sock_set_addr.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/tcp_listen.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/wrappthread.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/writen.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/connect_timeo.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/family_to_level.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/if_nameindex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/mcast_join.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/pselect.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/signal.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/sock_cmp_port.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/sock_set_port.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/tv_sub.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/wrapsock.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/daemon_inetd.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/get_ifi_info.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/if_nametoindex.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/mcast_leave.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/readable_timeo.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/signal_intr.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/sockfd_to_family.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/sock_set_wild.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/udp_client.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/wrapstdio.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/daemon_init.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/gf_time.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/in6addr_any.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/mcast_set_if.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/read_fd.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/snprintf.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/sock_get_port.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/str_cli.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/udp_connect.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/wrapunix.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/dg_cli.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/host_serv.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/mcast_get_if.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/mcast_set_loop.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/readline.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/sockatmark.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/sock_ntop.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/str_echo.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/udp_server.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/writable_timeo.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/dg_echo.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/hstrerror.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/mcast_get_loop.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/mcast_set_ttl.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/readn.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/sock_bind_wild.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/sock_ntop_host.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/tcp_connect.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/wraplib.c
        ${CMAKE_CURRENT_SOURCE_DIR}/unp/write_fd.c
        ${CMAKE_INCLUDE_PATH}
        )
