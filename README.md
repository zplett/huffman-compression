### README

Huffman Compression in C: Can be used to encode files and decode files using Huffman Trees

### FILES

`encode.c`: The executable that can be used for encoding files
`decode.c`: The executable that can be used for decoding files
`list.c`: Used for list and tree construction and their associated methods, acts as a library for encoding and decoding
`encode.h`: Header file for encode.c
`decode.h`: Header file for decode.c
`list.h`: Header file for list.h
`Makefile`: Used for compilation and linking into executables
`encode.1`: Manual page for encode.c, run using `nroff -man encode.1 | less -is`
'decode.1': Manual page for decode.c, run using `nroff -man decode.1 | less -is`

### USAGE

Run `make` to compile and then the encode and decode executables will be linked. To encode run `./encode file_to_encode optional_output_file`, if no output file is specified then the output will redirect
to stdout. To display the encoding in hex run `./encode ... | xxd` and to display the encoding in binary run `./encode ... | xxd -b`. To decode run `./decode encoded_file optional_output_file`, if no output file is specified then the output will redirect to stdout.

