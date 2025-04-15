import tkinter as tk
from tkinter import messagebox, simpledialog

class FourX_O_Board:
    def __init__(self):
        self.rows = 4
        self.columns = 4
        self.board = [[None for _ in range(self.columns)] for _ in range(self.rows)]

       
        self.board[0] = ['O', 'X', 'O', 'X']  
        self.board[self.rows - 1] = ['X', 'O', 'X', 'O']  

    def is_win(self):
       
        for i in range(self.rows):
            for j in range(self.columns - 2):
                if (self.board[i][j] and
                        self.board[i][j] == self.board[i][j + 1] == self.board[i][j + 2]):
                    return True

        
        for j in range(self.columns):
            for i in range(self.rows - 2):
                if (self.board[i][j] and
                        self.board[i][j] == self.board[i + 1][j] == self.board[i + 2][j]):
                    return True

       
        for i in range(self.rows - 2):
            for j in range(self.columns - 2):
                if (self.board[i][j] and
                        self.board[i][j] == self.board[i + 1][j + 1] == self.board[i + 2][j + 2]):
                    return True
                if (self.board[i][j + 2] and
                        self.board[i][j + 2] == self.board[i + 1][j + 1] == self.board[i + 2][j]):
                    return True

        return False

    def is_draw(self):
        return all(self.board[i][j] is not None for i in range(self.rows) for j in range(self.columns)) and not self.is_win()


class FourX_O_GUI:
    def __init__(self):
        self.root = tk.Tk()
        self.root.geometry("500x500")
        self.root.title("FourX-O Game")
        self.root.protocol("WM_DELETE_WINDOW", self.on_close)
        self.board = FourX_O_Board()
        self.current_player = 'X'

        self.buttons = [[None for _ in range(self.board.columns)] for _ in range(self.board.rows)]
        self.create_board()

        self.turn_label = tk.Label(self.root, text="Player X's turn", font=("Helvetica", 14))
        self.turn_label.pack(side=tk.BOTTOM)

        self.root.mainloop()
    def on_close(self):
        self.root.destroy()
        menuGui()

    def create_board(self):
        frame = tk.Frame(self.root)
        frame.pack(expand=True, fill=tk.BOTH)

        for i in range(self.board.rows):
            frame.rowconfigure(i,weight=1)
            for j in range(self.board.columns):
                frame.columnconfigure(j, weight=1)
                button = tk.Button(frame, text=self.board.board[i][j], font=("Helvetica", 16), width=4, height=2,
                                   command=lambda x=i, y=j: self.make_move(x, y))
                button.grid(row=i, column=j,sticky="nsew")
                self.buttons[i][j] = button

    def make_move(self, x, y):
        if self.board.board[x][y] != self.current_player:
            messagebox.showwarning("Invalid Move", "This token does not belong to the current player.")
            return

        move_type = simpledialog.askstring("Move Type", "Do you want to move horizontally or vertically? (h/v)")

        if move_type.lower() not in ('h', 'v'):
            messagebox.showwarning("Invalid Choice", "Please choose 'h' for horizontal or 'v' for vertical.")
            return

        direction = ""

        if move_type.lower() == 'h':
            direction = simpledialog.askstring("Direction", "Do you want to move right or left? (right/left)")
            if direction.lower() == "right":
                good=self.move_horizontally(x, y, 1)
                if not good:
                    messagebox.showwarning("Invalid Direction", "space occupied")
                    return
            elif direction.lower() == "left":
                good=self.move_horizontally(x, y, -1)
                if not good:
                    messagebox.showwarning("Invalid Direction", "space occupied")
                    return
            else:
                messagebox.showwarning("Invalid Direction", "Please choose 'right' or 'left'.")
                return

        elif move_type.lower() == 'v':
            direction = simpledialog.askstring("Direction", "Do you want to move up or down? (up/down)")
            if direction.lower() == "down":
                good=self.move_vertically(x, y, 1)
            elif direction.lower() == "up":
                good=self.move_vertically(x, y, -1)
                if not good:
                    messagebox.showwarning("Invalid Direction", "space occupied")
                    return
                if not good:
                    messagebox.showwarning("Invalid Direction", "space occupied")
                    return
            else:
                messagebox.showwarning("Invalid Direction", "Please choose 'up' or 'down'.")
                return

        if self.board.is_win():
            messagebox.showinfo("Game Over", f"Player {self.current_player} wins!")
            self.reset_board()  # Reset the board after a win
            return

        elif self.board.is_draw():
            messagebox.showinfo("Game Over", "It's a draw!")
            self.reset_board()  # Reset the board after a draw
            return

        
        self.current_player = 'O' if self.current_player == 'X' else 'X'
        self.turn_label.config(text=f"Player {self.current_player}'s turn")

    def move_horizontally(self, x, y, direction):
        new_y = y + direction
        if 0 <= new_y < 4 and self.board.board[x][new_y] is None:
            self.update_board(x, new_y, x, y)
            return True
        else:
            return False

    def move_vertically(self, x, y, direction):
        new_x = x + direction
        if 0 <= new_x < 4 and self.board.board[new_x][y] is None:
            self.update_board(new_x, y, x, y)
            return True
        else:
            return False
    def update_board(self, new_x, new_y, old_x, old_y):
        self.buttons[new_x][new_y].config(text=self.current_player)
        self.board.board[new_x][new_y] = self.current_player

        self.buttons[old_x][old_y].config(text="")
        self.board.board[old_x][old_y] = None

    def reset_board(self):
        
        for i in range(4):
            for j in range(4):
                self.board.board[i][j] = None
                self.buttons[i][j].config(text="")

        # Refill the board with the desired rows
        self.board.board[0] = ['O', 'X', 'O', 'X']
        self.board.board[3] = ['X', 'O', 'X', 'O']


        for i in range(4):
            for j in range(4):
                self.buttons[i][j].config(text=self.board.board[i][j])


        self.current_player = 'X'
        self.turn_label.config(text="Player X's turn")


#-------------------------------------





class ULT_X_O_Board:
    def __init__(self):
        # Initialize the 9 sub-boards, each being a 3x3 board.
        self.ult = [[['' for _ in range(3)] for _ in range(3)] for _ in range(9)]  # 9 boards of 3x3
        self.board = [['' for _ in range(3)] for _ in range(3)]  # Main board to keep track of winners
        self.current_player = 'X'
        self.subboard_winners = [None for _ in range(9)]  # Track sub-board winners (None, 'X', 'O')

    def make_move(self, ux, uy, bx, by):
        """Update the sub-board and main board."""
        if self.ult[ux * 3 + uy][bx][by] == '' and self.subboard_winners[ux * 3 + uy] is None:
            self.ult[ux * 3 + uy][bx][by] = self.current_player
            # Check if the sub-board is won
            if self.check_subboard_winner(ux * 3 + uy):
                self.subboard_winners[ux * 3 + uy] = self.current_player
                self.board[ux][uy] = self.current_player
            return True
        return False

    def is_subboard_full(self, subboard_index):
        """Check if a sub-board is full."""
        board = self.ult[subboard_index]
        for row in board:
            for cell in row:
                if cell == '':
                    return False  # Sub-board is not full
        return True  # Sub-board is full

    def check_subboard_winner(self, subboard_index):
        """Check if a sub-board has a winner."""
        board = self.ult[subboard_index]
        # Check rows, columns, and diagonals for a winner
        for i in range(3):
            if board[i][0] == board[i][1] == board[i][2] and board[i][0] != '':
                return True
            if board[0][i] == board[1][i] == board[2][i] and board[0][i] != '':
                return True
        if board[0][0] == board[1][1] == board[2][2] and board[0][0] != '':
            return True
        if board[0][2] == board[1][1] == board[2][0] and board[0][2] != '':
            return True
        return False

    def is_winner(self):
        """Check if there's a winner in the main board."""
        for i in range(3):
            if self.board[i][0] == self.board[i][1] == self.board[i][2] and self.board[i][0] != '':
                return True
            if self.board[0][i] == self.board[1][i] == self.board[2][i] and self.board[0][i] != '':
                return True
        if self.board[0][0] == self.board[1][1] == self.board[2][2] and self.board[0][0] != '':
            return True
        if self.board[0][2] == self.board[1][1] == self.board[2][0] and self.board[0][2] != '':
            return True
        return False

    def is_draw(self):
        """Check if the game ended in a draw."""
        for row in self.board:
            for cell in row:
                if cell == '':
                    return False
        return True

    def switch_player(self):
        """Switch turns between players."""
        self.current_player = 'O' if self.current_player == 'X' else 'X'


class ULTX_O_GUI:
    def __init__(self):
        self.root = tk.Tk()
        self.root.geometry("600x600")
        self.root.title("Ultimate X-O Game")
        self.root.protocol("WM_DELETE_WINDOW", self.on_close)

        self.board = ULT_X_O_Board()
        self.frames = []
        self.buttons = []
        self.create_board()

        self.turn_label = tk.Label(self.root, text="Player X's turn", font=("Helvetica", 14))
        self.turn_label.grid(row=3, column=0, columnspan=3)

        self.root.mainloop()

    def on_close(self):
        """Handle window close event."""
        self.root.destroy()
        menuGui()

    def create_board(self):
        """Create the 9 sub-boards (3x3 grid of frames)."""
        for i in range(3):
            row_frames = []
            row_buttons = []
            for j in range(3):
                frame = tk.Frame(self.root, width=100, height=100, bg="lightblue", relief="solid", bd=2)
                frame.grid(row=i, column=j, padx=5, pady=5, sticky="nsew")

                buttons_in_frame = []
                for x in range(3):
                    frame.rowconfigure(x, weight=1)
                    buttons_in_frame_row = []
                    for y in range(3):
                        frame.columnconfigure(y, weight=1)
                        button = tk.Button(frame, text="", font=("Helvetica", 16), width=4, height=2,
                                           command=lambda ux=i, uy=j, bx=x, by=y: self.make_move(ux, uy, bx, by))
                        button.grid(row=x, column=y, sticky="nsew")
                        buttons_in_frame_row.append(button)
                    buttons_in_frame.append(buttons_in_frame_row)

                row_frames.append(frame)
                row_buttons.append(buttons_in_frame)

            self.frames.append(row_frames)
            self.buttons.append(row_buttons)

        # Configure the rows and columns to expand with the window
        for i in range(3):
            self.root.grid_rowconfigure(i, weight=1)
            self.root.grid_columnconfigure(i, weight=1)

    def make_move(self, ux, uy, bx, by):
        """Handle a move by the current player."""
        if self.board.make_move(ux, uy, bx, by):
            self.buttons[ux][uy][bx][by].config(text=self.board.current_player)
            if self.board.is_winner():
                self.end_game(f"Player {self.board.current_player} wins!")

            elif self.board.is_draw():
                self.end_game("It's a draw!")

            else:
                self.board.switch_player()
                self.turn_label.config(text=f"Player {self.board.current_player}'s turn")
            self.check_subboard_winner(ux, uy)

    def check_subboard_winner(self, ux, uy):
        """Disable the buttons in a won sub-board."""
        winner = self.board.subboard_winners[ux * 3 + uy]

        if self.board.subboard_winners[ux * 3 + uy] is not None:
            # Disable all buttons in the won sub-board
            for x in range(3):
                for y in range(3):
                    self.buttons[ux][uy][x][y].destroy()
                    
            winner_label = tk.Label(self.root, text=winner, font=("Helvetica", 48), bg="white")    
            winner_label.grid(row=ux, column=uy, padx=5, pady=5, sticky="nsew")

    def end_game(self, message):
        """Display the end game message and disable all buttons."""
        messagebox.showinfo("Game Over", message)
        self.root.destroy()
        menuGui()

class menuGui:
    def __init__(self):
        self.root = tk.Tk()
        self.root.geometry("500x500")
        self.root.title("Menu")
        self.btn1=tk.Button(self.root, text="FOUR", width="20", height="3" ,command=self.openfour)
        self.btn1.pack(pady=(100,0), padx=10)
        self.btn2=tk.Button(self.root, text="ULTIMATE", width="20", height="3",command=self.openult)
        self.btn2.pack(pady=(50,0), padx=10)
        self.root.mainloop()
    def openfour(self):
        self.root.destroy()
        FourX_O_GUI()

    def openult(self):
        self.root.destroy()
        ULTX_O_GUI()

if __name__ == "__main__":
    menuGui()