# Adding Multi-Threaded Support to Single-Threaded Sudoku Solver

This project contains a multi-threaded Sudoku solver implemented in C using POSIX threads (pthreads).

## Build and run:
   - build the project:
     ```bash
     make
     ```
   - Run the multi-threaded version (replace `<input_file>` with a file from the `input` directory):
     ```bash
     ./sudoku_single <input_file>
     ```
     Example:
     ```bash
     ./sudoku_single input/sample_input.txt
     ```

## Notes

- The single-threaded version is lightweight and suitable for smaller puzzles.
- The multi-threaded version may improve performance for large or complex Sudoku puzzles by parallelizing validation tasks.
- Ensure your system supports threading for the multi-threaded version.
