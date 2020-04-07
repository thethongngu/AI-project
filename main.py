class Board:
	def __init__(self, size):
		self.size = size
		self.board = [[0 for row in range(size)] for col in range(size)]
		self.moved = [[False for row in range(size)] for col in range(size)]

	def get_sum(row, col):
		ans = 0
		ans += board[row - 1][col - 1] if row > 0 and col > 0 else 0
		ans += board[row - 1][col] if row > 0 else 0
		ans += board[row - 1][col + 1] if row > 0 and col < self.size - 1 else 0
		ans += board[row][col - 1] if col > 0 else 0
		ans += board[row][col]
		ans += board[row][col + 1] if col < self.size - 1 else 0
		ans += board[row + 1][col - 1] if row < self.size - 1 and col > 0 else 0
		ans += board[row + 1][col] if row < self.size - 1 else 0
		ans += board[row + 1][col + 1] if row < self.size and col < self.size else 0

		return ans


	def validate_move(self, row, col):
		return (not moved[row][col]) and (board[row][col] == 0)

	def check_board(self):
		for row in range(self.size):
			for col in range(self.size):
				if get_sum(row, col) > 15:
					self.board[row][col] = 0
					self.move[row][col] = True

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

if __name__ == '__main__':
	board = Board(4)
	print(board)



