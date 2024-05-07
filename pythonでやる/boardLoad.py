import json

def load_board_data(filepath):
    """指定されたJSONファイルからボードの初期状態と目標状態を読み込む"""
    with open(filepath, 'r') as f:
        data = json.load(f)

    start_board = [[int(char) for char in item] for item in data["board"]["start"]]
    goal_board = [[int(char) for char in item] for item in data["board"]["goal"]]
    
    return start_board, goal_board
