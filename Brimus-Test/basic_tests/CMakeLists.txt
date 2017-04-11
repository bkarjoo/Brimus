include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runBasicBrimusTests
        bar_series_check.cpp strategy_oms_check.cpp global_basket_check.cpp symbol_basket_check.cpp launch_rules_check.cpp pcap_file_server_check.cpp boost_dateclass.cpp pcap_file_check.cpp.cpp order_collection_check.cpp hydra_message_check.cpp position_check.cpp position_collection_test.cpp execution_collection_check.cpp boost_UUID_check.cpp ms_order_collection_check.cpp market_simulator_check.cpp instrument_check.cpp)

target_link_libraries(runBasicBrimusTests gtest gtest_main)
target_link_libraries(runBasicBrimusTests Brimus)