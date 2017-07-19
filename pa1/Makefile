CFLAGS=-g -std=gnu++11 -Wall

all: pptoken

# build pptoken application

SOURCES=Utf8.cpp \
        Utf8Transform.cpp \
        TransformResult.cpp \
        TrigraphTransform.cpp \
        UniversalCharTransform.cpp

pptoken:
	g++ $(CFLAGS) -o pptoken pptoken.cpp $(SOURCES)

# build & execute unit tests

TEST-SOURCES=TrigraphTransformTests.cpp \
             UniversalCharTransformTests.cpp \
             Utf8TransformTests.cpp

TEST-INCLUDE=-I../gtest/include

TEST-LIBS=-L../gtest/lib -lgtest -lgtest_main -lpthread

unit-test:
	g++ $(CFLAGS) $(TEST-INCLUDE) -o pptoken-tests $(TEST-SOURCES) $(SOURCES) $(TEST-LIBS)
	./pptoken-tests

# test pptoken application
test: all
	scripts/run_all_tests.pl pptoken my
	scripts/compare_results.pl ref my

# regenerate reference test output
ref-test:
	scripts/run_all_tests.pl pptoken-ref ref

