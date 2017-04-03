include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicBrimusTests
        bar_series_check.cpp strategy_oms_check.cpp global_basket_check.cpp symbol_basket_check.cpp launch_rules_check.cpp pcap_file_server_check.cpp boost_dateclass.cpp)

target_link_libraries(runBasicBrimusTests gtest gtest_main)
target_link_libraries(runBasicBrimusTests Brimus)