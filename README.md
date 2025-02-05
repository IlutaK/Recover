Program accepts exactly one command-line argument, the name of a forensic image from which to recover JPEGs.

If program is not executed with exactly one command-line argument, it reminds the user of correct usage, and main returns 1.

If the forensic image cannot be opened for reading, program informs the user as much, and main returns 1.

Generated files are each named ###.jpg, where ### is a three-digit decimal number, starting with 000 for the first image and counting up.
