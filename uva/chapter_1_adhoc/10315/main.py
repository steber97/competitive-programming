import math


def parseCards(cards):
    numbers = [int(x[0].replace("T", "10").replace("J", "11").replace("Q", "12").replace("K", "13").replace("A", "14")) for x in cards]
    suits = [x[1] for x in cards]

    if (len(set(numbers)) == len(numbers)):
        # All numbers are distinct
        if len(set(suits)) > 1:
            # No Flush
            numbers_sorted = sorted([x if x != 14 else 1 for x in numbers])
            if numbers_sorted[0] + 4 == numbers_sorted[4]:
                return 4, sorted(numbers, reverse=True) #Straight
            else:
                return 8, sorted(numbers, reverse=True) #High Card
        else:
            numbers_sorted = sorted([x if x != 14 else 1 for x in numbers])
            if numbers_sorted[0] + 4 == numbers_sorted[4]:
                return 0, sorted(numbers, reverse=True) #Straight flush
            return 3, sorted(numbers, reverse=True) #Flush
    else:
        if len(set(numbers)) == 4:
            count = set()
            for x in numbers:
                if x not in count:
                    count.add(x)
                else: 
                    return 7, [x] + sorted(numbers, reverse=True) # Pair
        elif len(set(numbers)) == 3:
            count = set()
            for x in numbers:
                if x not in count:
                    count.add(x)
                else:
                    return 5, [x] + sorted(numbers, reverse=True) # Three of a kind
        else:
            # Pocker or full house
            numbers_sorted = sorted(numbers)
            if numbers_sorted[0] == numbers_sorted[1] == numbers_sorted[2] == numbers_sorted[3] or \
                    numbers_sorted[4] == numbers_sorted[1] == numbers_sorted[2] == numbers_sorted[3]:
                return 1, [numbers_sorted[1]] #Four of a kind
            else:
                #Full House
                return 2, [numbers_sorted[2]]



if __name__ == "__main__":

    while True:
        try:
            text = input()
            cards = text.split()
            if len(cards) != 10:
                break
            black = cards[:5]
            white = cards[5:]
            valb, orderb = parseCards(black)
            valw, orderw = parseCards(white)
            
            if valb < valw:
                print("Black wins.")
            elif valb > valw:
                print("White wins.")
            else:
                finish = False
                for x,y in zip(orderb, orderw):
                    if x > y:
                        print("Black wins.")
                        finish = True
                        break
                    elif x < y:
                        print("White wins.")
                        finish = True
                        break
                if not finish:
                    print("Tie.")
        except EOFError:
            break
    exit(0)
