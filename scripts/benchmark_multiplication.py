import pandas as pd

import argparse
import random
import subprocess
import itertools
import time

NUM_CAP_MAX = 4096
NUM_CAP_MIN = 1


def benchmark_c_converted_multiplication(
    execs_paths: list[str], csv_output_path: str | None, samples: int
) -> None:
    firsts = []
    seconds = []
    outputs = []
    times = []
    for _ in range(samples):
        first = random.randint(NUM_CAP_MIN, NUM_CAP_MAX)
        second = random.randint(NUM_CAP_MIN, NUM_CAP_MAX)
        for el in execs_paths:
            start = time.perf_counter()
            out = subprocess.run([el, str(first), str(second)], capture_output=True)
            duration = time.perf_counter() - start
            firsts.append(first)
            seconds.append(second)
            outputs.append(int(out.stdout))
            times.append(duration)

    df = pd.DataFrame(
        {
            "first": firsts,
            "second": seconds,
            "result": outputs,
            "time": times,
            "name": [
                *itertools.chain.from_iterable(itertools.repeat(execs_paths, samples))
            ],
        }
    )

    df["expected"] = df["first"] * df["second"]
    df["valid"] = df["expected"] == df["result"]

    if csv_output_path is None:
        csv_output_path = "out.csv"

    df.to_csv(csv_output_path)


if __name__ == "__main__":
    arg_parser = argparse.ArgumentParser(
        description="generate benchmarks for multiplying two numbers"
    )
    arg_parser.add_argument(
        "--input", "--i", nargs="+", help="C executables to test", required=True
    )
    arg_parser.add_argument(
        "--samples", "-s", help="how many tests to run", type=int, default=100
    )
    arg_parser.add_argument(
        "--output", "-o", help="output CSV path", type=str, default=None
    )

    args = arg_parser.parse_args()
    benchmark_c_converted_multiplication(args.input, args.output, args.samples)
