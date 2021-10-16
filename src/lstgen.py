import sys, struct, csv

tsvpath = "symbols.tsv"
if len(sys.argv) > 1:
    tsvpath = sys.argv[1]

outpath = ""
if len(sys.argv) > 2:
    outpath = sys.argv[2]
   
col = 0
if len(sys.argv) > 3:
    col = int(sys.argv[3])

f = open(tsvpath)

lst = ""

syms = csv.reader(f, delimiter="\t")
next(syms)
for sym in syms:
    lst += sym[col] + ":" + sym[4] + "\n"
   
f.close()

f = open(outpath, "w")
f.write(lst)
f.close()