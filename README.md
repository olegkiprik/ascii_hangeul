# ASCII Han-geul

A portable toolkit for custom reversible romanization of Han-geul written in [Dependable C](https://dependablec.org).

Revised Romanization is ambiguous. Here are some notes on updated rules to make the transliteration reversible to original.

Possible pairs:

  yweaouibdgksptjmnhlrc

y ..xxxx...............
w ..xxx.x..............
e ..x.xx.llllllllllll.l
a ..x....llllllllllll.l
o ..x.x..llllllllllll.l
u ......tllllllllllll.l
i .......llllllllllll.l
b xxxxxxx....f.........
d xxxxxxx..............
g xxxxxxx....f.........
k xxxxxxx...u..........
s xxxxxxx....u.....i...
p xxxxxxx.....i........
t xxxxxxx......i.......
j xxxxxxx.......i......
m xxxxxxx..............
n xxxxxxx..f....f..f...
h xxxxxxx..............
l x.xxxxxf.f.fff.f.f...
r xxxxxxx..............
c .................u...

x can be joined
t triple only
l scan further to decide
i initial only
f final only
u both initial and final
. cannot be joined

Possible triple non-consonant sequences: yeo yae weo wae woe eui

Consonants are either single or paired.

## Input

- [ ] \r, \n, \t, whitespaces
- [ ] !"#$%&'()*+,-./0123456789:;<=>?@[\]^_`|~
- [ ] Lowercase letters: abcdeghijklmnoprstuwy
- [ ] Any ASCII symbols that are surrounded by braces

'\' is an escape symbol used inside braces. See Examples.
'-' is a separator to avoid ambiguity. Braces are NOT separators.
Put any symbol from the first two categories before '{' to prevent permutation in text.

## Assumptions

- [ ] Consonant-only geuljas are separated from other symbols by '-'.
- [ ] Sequences "bshi", "lshi", "gshi", "sshi", "kkkk", "lkkk", "bsss", "lsss", "gsss", "ssss", "bssh", "lssh", "gssh" without separators do not occur outside braces.
- [ ] Braces are not in the middle of geuljas.
- [ ] The first symbol is not '{'. To bypass this, put whitespace at the beginning.

No errors are emitted if the input does not follow the rules.

## Examples

C strings are used. A macro DRHR_FINAL_CONSONANTS_PRECEDENCE is defined.

Input: "  annyeonghaseyo "
Output: "\n  an-nyeong-ha-se-yo "

Input: " anh-a-{ }yo"
Output: "\n anh-a{ }-yo"

Input: " {{\\\\\\}} "
Output: "\n {{\\\\\\}} "
