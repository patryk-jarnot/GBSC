# GBSC - Graph Based Sequence Clustering

This method identifies short tandem repeats in a fasta database and clusters them by patterns representing repetitions.

## Dependencies

GBSC has the following build dependencies:

* make (v4.4.1 or later)
* g++ (v14.2.0 or later)

## Build release version

[Download the latest release version](https://github.com/patryk-jarnot/gbsc/releases/download/v1.0.0/gbsc-1.0.0.tar.gz)

Extract the archive, enter the directory and execute the following commands:

```[bash]
./configure
make
make install
```

## Build development version

First, clone the project and then execute the following commands:

```[bash]
autoreconf -i
./configure
make
make install
```

## Usage

To identify and cluster sequences, use the following syntax:

```[bash]
gbsc cluster -i [database_file] --clusters-dir [output_directory]
```

## Example

First, download proteins from UniProtKB by executing the following command:

```[bash]
wget -O sequences.fasta https://rest.uniprot.org/uniprotkb/stream?format=fasta&query=%28%28%28*%29+AND+%28reviewed%3Atrue%29%29+AND+%28taxonomy_id%3A554915%29%29
```

Then create output directory and cluster STRs by similarity using the following command:

```[bash]
mkdir output_dir
gbsc cluster -i sequences.fasta --clusters-dir output_dir
```

You will find clusters in the 'output_dir' directory.

## Help

To get help, execute the following command:

```[bash]
gbsc --help
```

## Links
* [Patryk Jarnot Web Page](https://pjarnot.com)
* [LCR Lab Web Page](https://lcr-lab.org)
* [Bioinformatics Research Laboratory @ UCY](https://vprobon.github.io/BRL-UCY/)
