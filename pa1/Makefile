all: pptoken

# build pptoken application
#pptoken: pptoken.cpp IPPTokenStream.h DebugPPTokenStream.h
#	g++ -g -std=gnu++11 -Wall -o pptoken pptoken.cpp

pptoken:
	g++ -g -std=gnu++11 -Wall -o pptoken pptoken.cpp \
                                             Utf8.cpp \
                                             Utf8Transform.cpp \
                                             TransformResult.cpp \
                                             TrigraphTransform.cpp \
                                             UniversalCharTransform.cpp

unit-test:
	g++ -g -std=gnu++11 -Wall -I../gtest/include -o pptoken-tests TrigraphTransformTests.cpp -L../gtest/lib -lgtest -lgtest_main -lpthread

#HEADER=IPPTokenStream.h \
#       DebugPPTokenStream.h \
#       Utf8.h

#SOURCE=pptoken.cpp \
#       Utf8.cpp

#pptoken:
#	g++ -g -std=gnu++11 -Wall -o pptoken $(SOURCE)

# test pptoken application
test: all
	scripts/run_all_tests.pl pptoken my
	scripts/compare_results.pl ref my

# regenerate reference test output
ref-test:
	scripts/run_all_tests.pl pptoken-ref ref

