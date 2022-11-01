if __name__=="__main__":
    N = int(input())
    blank = input()
    for n in range(N):
        phrases = []
        text = input()
        while text != "":
            phrases.append(text)
            try:
                text = input()
            except EOFError:
                break
        
        map_anagrams = {}
        for t in phrases:
            sorted_text = "".join(sorted(t.replace(" ", "")))
            if sorted_text not in map_anagrams:
                map_anagrams[sorted_text] = []
            map_anagrams[sorted_text].append(t)
        for k in map_anagrams:
            map_anagrams[k] = sorted(map_anagrams[k])
        
        pairs = []
        for k in map_anagrams:
            for i in range(len(map_anagrams[k])):
                for j in range(i+1, len(map_anagrams[k])):
                    pairs.append((map_anagrams[k][i], map_anagrams[k][j]))
        
        pairs = sorted(pairs)
        for p in pairs:
            print("{} = {}".format(p[0], p[1]))
        if n < N-1:
            print("")