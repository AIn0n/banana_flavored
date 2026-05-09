"""
Transpile brainf_ck to C language code.

Simple trainspler, didn't care about memory allocation using statically allocated
array.
"""

import argparse

INSTRUCTION_TO_C: dict[str, str] = {
    "<": "p--;\n",
    ">": "p++;\n",
    "+": "t[p]++;\n",
    "-": "t[p]--;\n",
    ",": "t[p] = getchar();\n",
    ".": "putchar(t[p]);\n",
    "[": "while (t[p] != 0) {\n",
    "]": "}\n",
}


def transpile_to_c(input_path: str, output_path: str | None) -> None:
    c_code = (
        "#include <stdio.h>\n"
        "#include <stdint.h>\n\n"
        "int main(void)\n"
        "{\n"
        "  uint32_t t[2048] = {0};\n"
        "  uint32_t p = 0;\n"
    )
    with open(input_path, mode="r", encoding="utf-8") as input_file:
        indent = 1
        for char in input_file.read():
            if char == "]":
                indent -= 1
            if char in INSTRUCTION_TO_C.keys():
                c_code += "  " * indent
                c_code += INSTRUCTION_TO_C[char]
            if char == "[":
                indent += 1
        c_code += "  return 0;\n"
        c_code += "}\n"

    if output_path is None:
        output_path = "bf.c"

    with open(output_path, mode="a", encoding="utf-8") as output_file:
        print(c_code, file=output_file)


if __name__ == "__main__":
    arg_parser = argparse.ArgumentParser(description="brainf_ck to C transpiler")
    arg_parser.add_argument(
        "-i", "--input", type=str, help="input path to .bf file", required=True
    )
    arg_parser.add_argument(
        "-o", "--output", type=str, default=None, help="output path"
    )
    args = arg_parser.parse_args()
    transpile_to_c(args.input, args.output)
