"""
Early concept on how multiplication by one constant can be optimized using code generation.

This method copies N (constant) times value of dynamic argument, and next sums them.
Probably, this could have some potential to works well with both dynamic arguments.
"""

import argparse

from minify_brainf_ck import minify


def main(num: int, output_path: str | None, minified: bool) -> None:
    if output_path is None:
        output_path = f"const_multiplication_by_{num}.bf"

    with open(output_path, mode="w", encoding="utf-8") as f:
        print("generated with generate_multiplication py", file=f)
        print("Stores argument at top of the stack", file=f)
        print("return argument one above the stack", file=f)
        print(f"first step: generate {num} copies of dynamic first arg", file=f)
        print("[", file=f)
        print("  -", file=f)
        print("  >+\n" * num, file=f)
        print("  " + "<" * num, file=f)
        print("]", file=f)
        print("sum all the copied values", file=f)
        print(f"move to the {num - 1} copy", file=f)
        print(">" * (num - 1), file=f)
        print("move pointer to the left as long as the number is not zero", file=f)
        print("[", file=f)
        print("  >", file=f)
        print("  move current cell value into the left neighbor", file=f)
        print("  [-<+>]", file=f)
        print("  <<", file=f)
        print("]", file=f)

    if minified:
        minify(output_path)


if __name__ == "__main__":
    arg_parser = argparse.ArgumentParser(
        description="Generate multiplication of number by any N, should be faster than normal multiplication",
        epilog="by default, it saves the results in const_multiplication_by_N.bf file",
    )
    arg_parser.add_argument(
        "-n",
        "--number",
        type=int,
        help="(required) constant element of multiplication",
        required=True,
    )
    arg_parser.add_argument(
        "-o",
        "--output",
        type=str,
        default=None,
        help="full output path, with filename, preferably .bf extension",
    )
    arg_parser.add_argument(
        "-m",
        "--minify",
        action="store_true",
        help="Minify the output, using the minify brainf_ck script",
    )
    args = arg_parser.parse_args()
    main(args.number, args.output, args.minify)
