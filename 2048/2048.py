from tkinter import *
import random

color = {2:'#F8EFBA', 4:'#fad390', 8:'#f8c291', 16:'#FEA47F', 32:'#F97F51',
         64:'#e15f41', 128:'#f7d794', 256:'#f5cd79', 512:'#f6b93b',
         1024:'#82ccdd', 2048:'#38ada9'}


class Game(Frame):
    def __init__(self):
        Frame.__init__(self)
        self.grid()
        self.master.title('2048')
        self.main_grid = Frame(self, bg='lightgray', bd=3, width=400, height=400)
        self.main_grid.grid()
        self.gameboard()
        self.start_game()
        self.master.bind("<Left>",self.left)
        self.master.bind("<Right>",self.right)
        self.master.bind("<Up>",self.up)
        self.master.bind("<Down>",self.down)
        self.mainloop()


    def start_game(self):
        self.board = [[0 for i in range(4)] for j in range(4)]
        row_num1 = random.randint(0,3)
        col_num1 = random.randint(0,3)

        self.board[row_num1][col_num1] = 2
        row_num2 = random.randint(0,3)
        col_num2 = random.randint(0,3)
        while col_num2 !=col_num1 and row_num2 != row_num1:
            row_num1 = random.randint(0,4)
            col_num1 = random.randint(0,4)

        self.board[row_num2][col_num2] = 2
        self.updateGame()
        


    def gameboard(self):
        self.tiles = []
        for i in range(4):
            row = []
            for j in range(4):
                tile_frame = Frame(self.main_grid, bg='white', width='50', height='50')
                tile_frame.grid(column=j, row=i, padx=3, pady=3)
                tile_num = Label(self.main_grid, bg='white')
                tile_num.grid(row=i, column=j)
                tile_data = {
                    'frame': tile_frame,
                    'number': tile_num
                }
                row.append(tile_data)
            self.tiles.append(row)

    def moveToLeft(self):
        new_board = [[0 for i in range(4)] for j in range(4)]
        
        for i in range(4):
            cur_col = 0
            for j in range(4):
                if self.board[i][j] != 0:
                    new_board[i][cur_col] = self.board[i][j]
                    cur_col += 1
        self.board = new_board

    def merge(self):
        for i in range(4):
            for j in range(3):
                if self.board[i][j] != 0 and self.board[i][j] == self.board[i][j + 1]:
                    self.board[i][j] *= 2
                    self.board[i][j + 1] = 0

    def reverse(self):
        new_board = [[0 for i in range(4)] for j in range(4)]
        for i in range(4):
            for j in range(4):
                new_board[i][j] = self.board[i][3 - j]

        self.board = new_board

    def transpose(self):
        new_board = [[0 for i in range(4)] for j in range(4)]
        for i in range(4):
            for j in range(4):
                new_board[i][j] = self.board[j][i]
        self.board = new_board

    def pickRandom(self):
        col_num = 0
        row_num = 0
        while self.board[row_num][col_num]!=0:
            col_num = random.randint(0,3)
            row_num = random.randint(0,3)

        a = random.randint(0,5)
        if a == 1:
            self.board[row_num][col_num] = 4
        else:
            self.board[row_num][col_num] = 2

    def updateGame(self):
        for i in range(4):
            for j in range(4):
                tmp = self.board[i][j]
                if tmp!=0:
                    self.tiles[i][j]['frame'].configure(bg=color[tmp])
                    self.tiles[i][j]['number'].configure(bg=color[tmp],fg='white',font='20',text=str(tmp))
                else:
                    self.tiles[i][j]['frame'].configure(bg='white')
                    self.tiles[i][j]['number'].configure(bg='white',text='')
            self.update_idletasks()

    def verticalMove(self):
        for i in range(3):
            for j in range(4):
                if self.board[i][j]==self.board[i+1][j]:
                    return True
        return False
    
    def horizontalMove(self):
        for i in range(4):
            for j in range(3):
                if self.board[i][j] == self.board[i][j+1]:
                    return True
            return False
    def left(self,event):
        self.moveToLeft()
        self.merge()
        self.moveToLeft()
        self.pickRandom()
        self.updateGame()
        self.final_result()

    def right(self,event):
        self.reverse()
        self.moveToLeft()
        self.merge()
        self.moveToLeft()
        self.reverse()
        self.pickRandom()
        self.updateGame()
        self.final_result()

    def up(self,event):
        self.transpose()
        self.moveToLeft()
        self.merge()
        self.moveToLeft()
        self.transpose()
        self.pickRandom()
        self.updateGame()
        self.final_result()

    def down(self,event):
        self.transpose()
        self.reverse()
        self.moveToLeft()
        self.merge()
        self.moveToLeft()
        self.reverse()
        self.transpose()
        self.pickRandom()
        self.updateGame()
        self.final_result()

    def final_result(self):
        if any(2048 in row for row in self.board):
            result_frame = Frame(self.main_grid,borderwidth=2)
            result_frame.place(relx=0.5,rely=0.5,anchor='center')
            Label(result_frame,text='You win',fg='white',bg='green',font='20').pack()
        elif not any(0 in row for row in self.board) and not self.verticalMove() and not self.horizontalMove():
            result_frame = Frame(self.main_grid,borderwidth=2)
            result_frame.place(relx=0.5,rely=0.5,anchor='center')
            Label(result_frame,text='Game Over',fg='white',bg='red',font='20').pack()

def main():
    Game()
if __name__ == "__main__":
    main()

