class Board:
    def __init__(self, size):
        self.size = size
        self.board = [[0 for row in range(size)] for col in range(size)]
        self.moved = [[False for row in range(size)] for col in range(size)]

    def get_sum(self, row, col):
        ans = 0
        ans += self.board[row - 1][col - 1] if row > 0 and col > 0 else 0
        ans += self.board[row - 1][col] if row > 0 else 0
        ans += self.board[row - 1][col + 1] if row > 0 and col < self.size - 1 else 0
        ans += self.board[row][col - 1] if col > 0 else 0
        ans += self.board[row][col]
        ans += self.board[row][col + 1] if col < self.size - 1 else 0
        ans += self.board[row + 1][col - 1] if row < self.size - 1 and col > 0 else 0
        ans += self.board[row + 1][col] if row < self.size - 1 else 0
        ans += self.board[row + 1][col + 1] if row < self.size - 1 and col < self.size - 1 else 0

        return ans


    def validate_move(self, row, col):
        return (not self.moved[row][col]) and (self.board[row][col] == 0)

    def check_board(self):
        for row in range(self.size):
            for col in range(self.size):
                if self.get_sum(row, col) > 15:
                    self.board[row][col] = 0
                    self.moved[row][col] = True

    """
    function that take the action put a card into the board.
    return:
        True: action is legal
        False: action is illegal
    """
    def put_card(self, row, col, val):

        if not self.validate_move(row, col):
            return False

        self.board[row][col] = val
        self.moved[row][col] = True

        self.check_board()
        return True

    def __str__(self):
        ans = 'Board:\n'
        for row in range(self.size):
            ans += '['
            for col in range(self.size - 1):
                ans += str(self.board[row][col]) + ', '
            ans += str(self.board[row][self.size - 1])
            ans += ']\n'

        return ans

class Player:
    def __init__(self, is_human, size):
        self.is_human = is_human
        if size == 4:
            self.card = [2, 3, 5, 8, 13]
        else:
            self.card = [2, 2, 3, 3, 5, 5, 8, 8, 8, 13, 13]

    def move(self):
        if self.is_human:
            inp = [int(val) for val in input().split(' ')]
            return (inp[0], inp[1], inp[2])
        else:
            inp = [int(val) for val in input().split(' ')]
            return (inp[0], inp[1], inp[2])

    def __str__(self):
        res = ''
        res += '[User chess pieces]: ' if self.is_human else '[  AI chess pieces]: '
        res += str(self.card)

        return res

class Game:
    def __init__(self):
        pass

    def end_game(self):
        return len(self.player01.card) == 0 and len(self.player02.card) == 0

    def check_player(self, val):
        for i in range(len(self.player.card)):  # self.player.self.card ???
            if val == self.player.card[i]:
                del self.player.card[i]
                return True

        return False

    def play(self):

        print('User first? (0/1): ', end='')
        self.user_first = int(input())

        print('Board size? (4 or 6): ', end='')
        self.board_size = int(input())

        self.board = Board(self.board_size)
        self.player01 = Player(self.user_first, self.board_size)
        self.player02 = Player(not self.user_first, self.board_size)
        self.log = []
        self.turn = 0

        print(self.board)
        print(self.player01)
        print(self.player02)

        while not self.end_game():

            self.turn += 1
            self.player = self.player01 if self.turn % 2 == 1 else self.player02

            while True: 
                print('\nInput (row, col, weight): ', end='')
                row, col, val = self.player.move()
                print('[%s]: (%s, %s, %s)' % ('User' if self.player.is_human else 'AI', row, col, val))

                if (not self.check_player(val)) or (not self.board.put_card(row, col, val)):
                    print('Illegal move at (%s, %s) by card (%s)' % (row, col, val))
                    continue

                break

            self.log.append((row, col, val))
            print(self.board)
            print(self.player01)
            print(self.player02)


    def load(self):
        pass

if __name__ == '__main__':

    game = Game()
    game.play()



