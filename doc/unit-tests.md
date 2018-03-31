Compiling/running unit tests
------------------------------------

Unit tests will be automatically compiled if dependencies were met in configure
and tests weren't explicitly disabled.

After configuring, they can be run with 'make check'.

To run the exvod tests manually, launch src/test/test_exvo .

To add more exvod tests, add `BOOST_AUTO_TEST_CASE` functions to the existing
.cpp files in the test/ directory or add new .cpp files that
implement new BOOST_AUTO_TEST_SUITE sections.

To run the exvo-qt tests manually, launch src/qt/test/exvo-qt_test

To add more exvo-qt tests, add them to the `src/qt/test/` directory and
the `src/qt/test/test_main.cpp` file.
