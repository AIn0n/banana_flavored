from argparse import ArgumentParser

BRAIN_FU_CK_OPS = "+-<>.,[]"


def minify(in_dir: str) -> None:
    with open(in_dir, "rt") as f:
        minified = "".join(c for c in f.read() if c in BRAIN_FU_CK_OPS)

    *base, filename = in_dir.split("/")
    out_dir = "/".join(base + ["minified_" + filename])

    with open(out_dir, "wt") as f:
        print("minified using minify_brainf_ck py", file=f)
        print(minified, file=f)


if __name__ == "__main__":
    parser = ArgumentParser(
        prog="Brainf_ck minifier",
        description="Minify given input program - removes comments and whitespaces.",
        epilog="Output is saved as minified_<filename> in the same dir.",
    )
    parser.add_argument("-f", "--filename", help="input path", type=str, required=True)
    args = parser.parse_args()
    minify(args.filename)
