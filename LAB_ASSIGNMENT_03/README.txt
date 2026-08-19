
CS509 - Assignment 3 - Buddy Task (Gradient Descent + Maxflow-Mincut)


SCOPE:
    This covers both buddy-task algorithms from the Assignment 3
    specification: Gradient Descent and Maxflow-Mincut. The individual
    MST task (Kruskal/Prim) is a separate submission and is not included
    here.

PROJECT FILES

Driver.cpp              - Single common driver/wrapper for BOTH
                           algorithms. Menu-based, or terminal
                           arguments: `driver gd <in> <out>` or
                           `driver maxflow <in> <out>`.
GradientDescent.h/.cpp  - Generic polynomial evaluation, derivative,
                           and the Gradient Descent update. One
                           implementation works for every required
                           degree (2, 4, 6, 8, 10) - nothing is
                           hard-coded per test case.
Graph.h/Graph.cpp       - Directed capacitated graph struct, file
                           reader, and validator for Maxflow-Mincut.
CSR.h/CSR.cpp           - Adjacency-list -> CSR converter for
                           Maxflow-Mincut (preprocessing only, never
                           timed). NOTE: the spec says to reuse your
                           own Assignment-2 CSR helper instead of
                           duplicating it; this project ships its own
                           copy only so it is self-contained. Swap in
                           your real CSR.h/CSR.cpp if you have one.
MaxFlow.h/MaxFlow.cpp   - Dinic's max-flow / min-cut algorithm.
                           Builds the residual network from CSR and
                           extracts the min cut, both inside the
                           timed call, per the spec.
input/                   - Required test input files:
                           gd_01.txt .. gd_05.txt
                           maxflow_10.txt, maxflow_100.txt,
                           maxflow_1000.txt, maxflow_10000.txt,
                           maxflow_50000.txt, maxflow_100000.txt (optional)
output/                  - Generated result files, one per input file.

HOW TO COMPILE

    g++ -std=c++17 *.cpp -o driver

Compiles cleanly with -Wall -Wextra -Wpedantic, no warnings.

HOW TO RUN

Interactive menu:
    ./driver
    -> 1 = Gradient Descent, 2 = Maxflow-Mincut, 3 = Exit
    -> then enter the input file path and output file path

Terminal-argument mode (skips the menu):
    ./driver gd <input_file> <output_file>
    ./driver maxflow <input_file> <output_file>
    Examples:
    ./driver gd input/gd_01.txt output/gd_01.txt
    ./driver maxflow input/maxflow_10.txt output/maxflow_10.txt

TIMING METHODOLOGY

Gradient Descent: only the gradientDescent() call is timed. Reading
and validating the input file, and printing/writing the result, are
outside the timer.

Maxflow-Mincut: file reading, validation, and adjacency-list -> CSR
conversion happen once, before any timer starts. Only the
maxFlowMinCut() call is timed - this includes building the residual
network from the CSR and extracting the min cut, both of which the
spec explicitly says belong inside the timed algorithm call.

INPUT VALIDATION

Gradient Descent driver rejects, with a clear error and no crash:
  - missing/unreadable input file, malformed keyword lines
  - negative degree
  - COEFFICIENTS count != degree + 1
  - non-positive LEARNING_RATE, TOLERANCE, or MAX_ITERATIONS

Maxflow-Mincut driver rejects, with a clear error and no crash:
  - missing/unreadable input file, malformed lines
  - vertex ids out of range
  - invalid source/sink vertices, or source == sink
  - negative capacities

9.2 GRADIENT DESCENT RESULTS TABLE

File        Degree  x0  Rate    Tol    Max Iter  Exp x*  Actual x       Iter  Time (ms)  Status
gd_01.txt   2       0   0.10    1e-6   5,000     3       2.9999995063   70    0.195      Pass
gd_02.txt   4       2   0.02    1e-6   10,000    0       0.0000002379   180   0.022      Pass
gd_03.txt   6       2   0.02    1e-6   20,000    0       0.0000004835   349   0.048      Pass
gd_04.txt   8       2   0.01    1e-8   50,000    0       0.0000000050   948   0.147      Pass
gd_05.txt   10      2   0.005   1e-10  100,000   0       0.0000000000   2364  0.486      Pass

9.3 MAXFLOW-MINCUT RESULTS TABLE

File                 V        E        Source  Sink     Flow   Cut Cap  Time (ms)   Status
maxflow_10.txt       10       17       0       9        131    131      0.023       Pass
maxflow_100.txt      100      300      0       99       253    253      0.191       Pass
maxflow_1000.txt     1,000    3,000    0       999      1023   1023     10.408      Pass
maxflow_10000.txt    10,000   30,000   0       9999     2353   2353     61.112      Pass
maxflow_50000.txt    50,000   150,000  0       49999    5666   5666     513.998     Pass
maxflow_100000.txt   100,000  300,000  0       99999    7473   7473     1316.430    Pass (optional test)

