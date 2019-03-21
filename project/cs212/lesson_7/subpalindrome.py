#!/usr/bin/env python
# -*- coding=utf8 -*-


#  My code, works but about 40 lines
def longest_subpalindrome_slice(text):
    "Return (i, j) such that text[i:j] is the longest palindrome in text."
    # Your code here
    if (len(text) == 0):
        return (0, 0)
    start = 0
    end = 0
    for i in range(len(text)):
        cur_start = 0
        cur_end = 0
        left = i - 1
        right = i + 1
        while(left >= 0 and right < len(text)):
            if text[left].upper() == text[right].upper():
                cur_start = left
                cur_end = right
                left = left - 1
                right = right + 1
            else:
                break;
        if (cur_end - cur_start) > (end - start):
            start = cur_start
            end = cur_end

        cur_start = 0
        cur_end = 0
        left = i
        right = i + 1
        while(left >= 0 and right < len(text)):
            if text[left].upper() == text[right].upper():
                cur_start = left
                cur_end = right
                left = left - 1
                right = right + 1
            else:
                break;
        if (cur_end - cur_start) > (end - start):
            start = cur_start
            end = cur_end

    return (start, end + 1)

#  lesson's code, so amazing
def longest_subpalindrome_slice2(text):
    if(len(text) == 0): return (0, 0)
    def length(slice): a, b = slice; return b - a;
    candidates = [grow(text, start, end)
            for start in range(len(text))
            for end in (start, start+1)]
    return max(candidates, key=length)

def grow(text, start, end):
    while (start > 0 and end < len(text)
            and text[start-1].upper() == text[end].upper()):
        start -= 1
        end += 1
    return (start, end)
    
def test():
    L = longest_subpalindrome_slice2
    assert L('racecar') == (0, 7)
    assert L('raccar') == (0, 6)
    assert L('Racecar') == (0, 7)
    assert L('RacecarX') == (0, 7)
    assert L('Race carr') == (7, 9)
    assert L('') == (0, 0)
    assert L('something rac e car going') == (8,21)
    assert L('xxxxx') == (0, 5)
    assert L('Mad am I ma dam.') == (0, 15)
    return 'tests pass'

print(test())
