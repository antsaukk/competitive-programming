#!/usr/bin/env python3

import datetime
import json
import textwrap
import urllib.parse

print('Hi, trying to parse your JSON file...')
with open('scores.json') as f:
    scores = json.load(f)

print("Got it, let's see what is in there.")
print()

name = scores['name']
assert isinstance(name, str)
studentnum = scores['studentnum']
assert isinstance(studentnum, str)
email = scores['email']
assert isinstance(email, str)
assert email.endswith('@aalto.fi')
contests = scores['contests']
assert isinstance(contests, list)

total = 0
for record in contests:
    when = datetime.date.fromisoformat(record['date'])
    assert 2021 <= when.year <= 2022
    url = record['url']
    assert urllib.parse.urlparse(url).scheme in ['http', 'https']
    account = record['account']
    assert isinstance(account, str)
    assert account != ''
    solved = record['solved']
    assert isinstance(solved, int)
    points = record['points']
    assert isinstance(points, int)
    assert solved >= 0
    assert points >= 0
    remark = record.get('remark', None)

    print(f'On {when:%A}, {when:%B} {when.day}, {when.year} you took part in')
    print(f'the contest at {url} and')
    print(f'and your results are listed in the scoreboard')
    print(f'with the user or team name "{account}".')
    print(f'You solved correctly {solved} problems,')
    print(f'and this will give you {points} points.')
    if remark is not None:
        print('Remark:')
        for l in textwrap.wrap(remark):
            print(f'  {l}')

    print()

    total += points

if total >= 36:
    credits = 5
elif total >= 30:
    credits = 4
elif total >= 24:
    credits = 3
elif total >= 18:
    credits = 2
else:
    credits = 0

print(f'Your name is {name}.')
print(f'Your Aalto student number is {studentnum}.')
print(f'Your Aalto email address is {email}.')
print(f'Your total score is {total}.')
print(f'Therefore you will get {credits} study credits.')
print()
