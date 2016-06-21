add_definitions (-DBOOST_TEST_DYN_LINK)

add_executable (tests test_all.cc)

include_directories(${Boost_INCLUDE_DIRS})

#target_link_libraries(test_algos ${Boost_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${Boost_SYSTEM_LIBRARY})

add_test (tests tests)
