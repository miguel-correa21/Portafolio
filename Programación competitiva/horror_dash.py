test_cases = int(input())
for i in range(test_cases):
    cases = list(map(int, input().strip().split(' ')))
    print("Case {0}: {1}".format(i+1, max(cases[1:])))
