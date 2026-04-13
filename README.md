# ASCII Han-geul

A portable toolkit for custom reversible romanization of Han-geul written in [Dependable C](https://dependablec.org).

Revised Romanization is ambiguous. Here are some notes on updated rules to make the transliteration reversible to original.

Possible pairs:

<kbd>  yweaouibdgksptjmnhlrc</kbd>  
<kbd>y ..xxxx...............</kbd>  
<kbd>w ..xxx.x..............</kbd>  
<kbd>e ..x.xx.llllllllllll.l</kbd>  
<kbd>a ..x....llllllllllll.l</kbd>  
<kbd>o ..x.x..llllllllllll.l</kbd>  
<kbd>u ......tllllllllllll.l</kbd>  
<kbd>i .......llllllllllll.l</kbd>  
<kbd>b xxxxxxx....f.........</kbd>  
<kbd>d xxxxxxx..............</kbd>  
<kbd>g xxxxxxx....f.........</kbd>  
<kbd>k xxxxxxx...u..........</kbd>  
<kbd>s xxxxxxx....u.....i...</kbd>  
<kbd>p xxxxxxx.....i........</kbd>  
<kbd>t xxxxxxx......i.......</kbd>  
<kbd>j xxxxxxx.......i......</kbd>  
<kbd>m xxxxxxx..............</kbd>  
<kbd>n xxxxxxx..f....f..f...</kbd>  
<kbd>h xxxxxxx..............</kbd>  
<kbd>l x.xxxxxf.f.fff.f.f...</kbd>  
<kbd>r xxxxxxx..............</kbd>  
<kbd>c .................u...</kbd>  

- [ ] x can be joined
- [ ] t triple only
- [ ] l scan further to decide
- [ ] i initial only
- [ ] f final only
- [ ] u both initial and final
- [ ] . cannot be joined

Possible triple non-consonant sequences: yeo yae weo wae woe eui

Consonants are either single or paired.

## Input

- [ ] \\r, \\n, \\t, whitespaces
- [ ] !"#$%&'()*+,-./0123456789:;<=>?@[\\]^_`|~
- [ ] Lowercase letters: abcdeghijklmnoprstuwy
- [ ] Any ASCII symbols that are surrounded by braces

'\\' is an escape symbol used inside braces. See Examples.  
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
Output: "\\n  an-nyeong-ha-se-yo "  

Input: " anh-a-{ }yo"  
Output: "\\n anh-a{ }-yo"  

Input: " {{\\\\\\\\\\\\}} "  
Output: "\\n {{\\\\\\\\\\\\}} "  
