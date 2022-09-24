# TODO

text = input("TEXT:  ")

cl = 0
for i in text:
    ordi = ord(i)
    if (ordi >= ord('a') and ordi <= ord('z')) or (ordi >= ord('A') and ordi <= ord('Z')):
        cl += 1
cw = text.count(" ") + 1
cs = text.count(".") + text.count("!") + text.count("?")

L = 1.0 * cl / cw * 100
S = 1.0 * cs / cw * 100
index = 0.0588 * L - 0.296 * S - 15.8
score = round(index)

if (score < 1):
    print("Before Grade 1")
elif (score < 16):
    print("Grade", str(score))
else:
    print("Grade 16+")