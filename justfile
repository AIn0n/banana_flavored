default:
    just --list

# Generate parser using bison
[group('parser')]
[working-directory('./next_take')]
parser:
    bison bflav.y -v

alias bi := parser
