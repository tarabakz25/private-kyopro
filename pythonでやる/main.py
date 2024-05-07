import numpy as np
import json
import os

teikei_nukigata = {"t1": [[1]],}
os.system("clear")

sizes = [2, 4, 8, 16, 32, 64, 128, 256]
for size in sizes:
    teikei_nukigata[f"t{size}_I"] = [[1] * size for _ in range(size)]
    teikei_nukigata[f"t{size}_II"] = [[1 if i % 2 == 0 else 0 for _ in range(size)] for i in range(size)]
    teikei_nukigata[f"t{size}_III"] = [[1 if j % 2 == 0 else 0 for j in range(size)] for _ in range(size)]

def load_board_data():
    """指定されたJSONファイルからボードの初期状態と目標状態を読み込む"""
    with open("sample.json", 'r') as f:
        data = json.load(f)

    start_board = [[int(char) for char in item] for item in data["board"]["start"]]
    goal_board = [[int(char) for char in item] for item in data["board"]["goal"]]
    
    return start_board, goal_board

startBoard, goalBoard = load_board_data()

#ボードの表示
def format_board(board, goal_board=None):
    """ボードの状態を文字列にフォーマットします。goal_boardが指定された場合、一致する数字を緑色で表示します。"""
    board_str = ""
    count_matches = 0
    total_elements = 0
    for y in range(len(board)):
        for x in range(len(board[y])):
            if goal_board and board[y][x] == goal_board[y][x]:
                board_str += f"\033[32m{board[y][x]}\033[0m "
                count_matches += 1
            else:
                board_str += f"{board[y][x]} "
            total_elements += 1
        board_str += "\n"
    macth_rate = count_matches / total_elements * 100
    return board_str, macth_rate

def PrintBoard():
    start_board_formatted, match_rate = format_board(startBoard, goalBoard)
    goal_board_formatted, _ = format_board(goalBoard)

    print("startBoard:")
    print(start_board_formatted)
    print("goalBoard:")
    print(goal_board_formatted)
    print(f"一致率:\033[31m{match_rate:.2f}%\033[0m")
    return match_rate



def sortBoard():
 try:
    score = []
    for y in range(len(startBoard)):
        for x in range(len(startBoard[y])):
            
            # 0 is up, 1 is down, 2 is left, 3 is right
            for action in range(4):
                tempBoard = startBoard.copy()
                if action == 0 and y > 0:
                    i = 0
                    while(i < y-1):
                        tempBoard[x][i] = tempBoard[x][i+1]
                        i += 1
                elif action == 1 and y < len(startBoard)-1:
                    i = y
                    while(i < len(startBoard)):
                        tempBoard[x][i] = tempBoard[x][i+1]
                        i += 1
                elif action == 2 and x > 0:
                    i = 0
                    while(i < x-1):
                        tempBoard[i][y] = tempBoard[i+1][y]
                        i += 1
                elif action == 3 and x < len(startBoard[y])-1:
                    i = x
                    while(i < len(startBoard[y])):
                        tempBoard[i][y] = tempBoard[i+1][y]
                        i += 1
                score.append([x, y, action, PrintBoard])
    print(score)
 except IndexError:
    pass

    

PrintBoard()
sortBoard()