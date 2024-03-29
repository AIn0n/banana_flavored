from argparse import ArgumentParser

BRAIN_FU_CK_OPS = "+-<>.,[]"


def main(in_dir):
    with open(in_dir, "rt") as f:
        minified = "".join(c for c in f.read() if c in BRAIN_FU_CK_OPS)

    *base, filename = in_dir.split("/")
    out_dir = "/".join(base + ["minified_" + filename])

    with open(out_dir, "wt") as f:
        print("generated with minify_brainf_ck py", file=f)
        print(minified, file=f)


if __name__ == "__main__":
    parser = ArgumentParser(
        prog="Brainf_ck minifier",
        description="Minify given input program - removes comments and whitespaces.",
        epilog="Output is saved as minified_<filename> in the same dir.",
    )
    parser.add_argument("-f", "--filename", help="input filename")
    args = parser.parse_args()
    main(args.filename)
