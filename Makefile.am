#AM_CXXFLAGS = -pedantic -Wall -std=c++11 -Iinclude -Isrc -DNDEBUG -O2 -pthread
AM_CXXFLAGS = -g -pedantic -Wall -std=c++11 -Iinclude -Isrc -pthread
AM_LDFLAGS =

all: libgbsc.a gbsc testfasta testthreadpool testgbsc testidentification testsearch testpostprocess testkmer testmodel testalphabet testcluster teststringutils test

lib_LIBRARIES = libgbsc.a
libgbsc_a_SOURCES = include/gbsc.h src/gbsc.cpp \
					src/libgbsc.cpp \
					include/fasta.h src/fasta.cpp \
					include/sequence.h src/sequence.cpp \
					include/graph.h src/graph.cpp \
					include/similaritysearch.h src/similaritysearch.cpp \
					include/identify.h src/identify.cpp \
					include/cluster.h src/cluster.cpp \
					include/output.h src/output.cpp \
					include/threadpool.h src/threadpool.cpp \
					include/postprocess.h src/postprocess.cpp \
					include/kmer.h src/kmer.cpp \
					include/model.h src/model.cpp \
					include/stringutils.h src/stringutils.cpp \
					include/alphabet.h src/alphabet.cpp \
					include/file.h src/file.cpp \
					include/debug.h \
					include/options.h
#libgbsc_adir = ./
dist_pkgdata_DATA = src/tests/data/example.fasta src/tests/data/reading_writing.fasta src/tests/data/sprot_samples.fasta src/tests/output/adjacent_clusters/.keep

bin_PROGRAMS = gbsc testthreadpool testfasta testgbsc testidentification testsearch testpostprocess testkmer testmodel testalphabet testcluster teststringutils
gbsc_SOURCES = $(libgbsc_a_SOURCES) src/main.cpp src/options.cpp
testthreadpool_SOURCES = $(libgbsc_a_SOURCES) src/tests/testthreadpool.cpp
testfasta_SOURCES = $(libgbsc_a_SOURCES) src/tests/testfasta.cpp
testgbsc_SOURCES = $(libgbsc_a_SOURCES) src/tests/testgbsc.cpp
testidentification_SOURCES = $(libgbsc_a_SOURCES) src/tests/testidentification.cpp
testsearch_SOURCES = $(libgbsc_a_SOURCES) src/tests/testsearch.cpp
testpostprocess_SOURCES = $(libgbsc_a_SOURCES) src/tests/testpostprocess.cpp
testkmer_SOURCES = $(libgbsc_a_SOURCES) src/tests/testkmer.cpp
testmodel_SOURCES = $(libgbsc_a_SOURCES) src/tests/testmodel.cpp
testalphabet_SOURCES = $(libgbsc_a_SOURCES) src/tests/testalphabet.cpp
testcluster_SOURCES = $(libgbsc_a_SOURCES) src/tests/testcluster.cpp
teststringutils_SOURCES = $(libgbsc_a_SOURCES) src/tests/teststringutils.cpp

ACLOCAL_AMFLAGS = -I m4 --install
EXTRA_DIST = m4/NOTES

test: testgbsc testfasta testsearch testidentification testthreadpool testpostprocess testkmer testmodel testalphabet testcluster teststringutils
	./testthreadpool $(top_srcdir)
	./testfasta $(top_srcdir)
	./testgbsc $(top_srcdir)
	./testidentification $(top_srcdir)
	./testsearch $(top_srcdir)
	./testpostprocess $(top_srcdir)
	./testkmer $(top_srcdir)
	./testmodel $(top_srcdir)
	./testalphabet $(top_srcdir)
	./testcluster $(top_srcdir)
	./teststringutils $(top_srcdir)


