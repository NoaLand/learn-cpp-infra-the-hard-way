# Perf Blackbox Labs

This directory contains blackbox performance investigation exercises.

The goal is not to inspect the implementation first.

Each `blackboxXX.sh` script generates an executable with an intentionally hidden
performance characteristic. Treat the executable as if it were an unknown
production binary.

## Rules

For each exercise:

1. Run only the corresponding generator script.

   ```bash
   ./blackbox01.sh

2. Do not inspect, decode, modify, or otherwise recover the implementation before
completing the investigation.
3. Analyze the generated executable using runtime evidence.
4. Write down:
  - observations
  - hypotheses
  - evidence
  - eliminated possibilities
  - final diagnosis
  - possible optimization direction
5. Only inspect the implementation after reaching a conclusion.

## Command line tool set for now
1. `perf stat`
2. `perf stat -e`
3. `perf record`
4. `perf report`
5. `strace -c`
6. `strace -f -c`
